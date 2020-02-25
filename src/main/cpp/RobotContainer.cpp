#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/Joystick.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/drive/WheelTest.h"
#include "commands/drive/TurnToAngle.h"
#include <commands/shooter/SetHoodToAngle.h>
#include "commands/drive/TeleopDrive.h"
#include "commands/controlpanel/ManualWheelRotation.h"
#include "commands/controlpanel/RotationControl.h"
#include "commands/controlpanel/PositionControl.h"
#include "commands/shooter/SetShooterToVelocity.h"
#include "commands/intake/AutoFeed.h"
#include "commands/intake/AutoIntake.h"
#include "commands/intake/SetLoaderWheelSpeed.h"
#include "frc2/command/ParallelRaceGroup.h"
#include "commands/intake/TeleopIntakeDown.h"
#include "commands/intake/TeleopIntakeUp.h"
#include "commands/climber/ClimbElevatorUp.h"
#include "commands/climber/ClimbElevatorDown.h"
#include "commands/drive/ZeroYaw.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/shooter/SetShooterToVelocity.h"

RobotContainer::RobotContainer() : m_drivetrain(){

  m_drivetrain.SetDefaultCommand(TeleopDrive(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kRightHand); },
    &m_drivetrain
  ));

  m_chooser.SetDefaultOption("Follow Path Auto", &m_followPathAuto);
  m_chooser.AddOption("Ten Cell Auto", &m_tenCellAuto);

  ConfigureButtonBindings();

  //frc::SmartDashboard::PutNumber("Shooter Velocity", 0);
  //frc::SmartDashboard::PutNumber("Shooter Angle", 0);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Zero Yaw", new ZeroYaw(&m_drivetrain));
  frc::SmartDashboard::PutData("Wheel Test", new WheelTest(&m_drivetrain));

  //frc::SmartDashboard::PutData("Set Wheel To RPM", new SetShooterToVelocity(&m_shooter, [this] { return units::revolutions_per_minute_t(frc::SmartDashboard::GetNumber("Shooter Velocity", 0)); }));
  //frc::SmartDashboard::PutData("Set Hood To Angle", new SetHoodToAngle(&m_shooter, [this] { return units::degree_t(frc::SmartDashboard::GetNumber("Shooter Angle", 0)); }));

  frc2::JoystickButton rotateToZeroButton(&driverController, (int)frc::XboxController::Button::kY);
  rotateToZeroButton.WhenPressed(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      0_deg,
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return std::abs(val - 0) <= 0.0001 * std::abs(val); 
      }
    )
  );

  frc2::JoystickButton rotateToGenerator112Button(&driverController, (int)frc::XboxController::Button::kX);
  rotateToGenerator112Button.WhenPressed(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      112.5_deg,
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return std::abs(val - 0) <= 0.0001 * std::abs(val); 
      }
    )
  );

  frc2::JoystickButton rotateToGenerator67Button(&driverController, (int)frc::XboxController::Button::kB);
  rotateToGenerator67Button.WhenPressed(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      -67.5_deg,
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return std::abs(val - 0) <= 0.0001 * std::abs(val); 
      }
    )
  );

  frc2::JoystickButton rotateTo180Button(&driverController, (int)frc::XboxController::Button::kA);
  rotateTo180Button.WhenPressed(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      180_deg,
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return std::abs(val - 0) <= 0.0001 * std::abs(val); 
      }
    )
  );

  //frc2::JoystickButton manualCPWheel(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  //manualCPWheel.WhileHeld(ManualWheelRotation(&m_controlpanel, [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));

  //frc2::JoystickButton rotControl(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  //rotControl.WhileActiveOnce(RotationControl(&m_controlpanel));
  
  //frc2::JoystickButton posControl(&operatorController, (int)frc::XboxController::Button::kB);
  //posControl.WhileActiveOnce(PositionControl(&m_controlpanel));
    
  frc2::JoystickButton intakeButton(&operatorController, (int)frc::XboxController::Button::kA);
  intakeButton.WhenHeld(TeleopIntakeDown(&m_intake));
  intakeButton.WhenReleased(TeleopIntakeUp(&m_intake));

  frc2::JoystickButton feederButton(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  feederButton.WhileHeld(SetLoaderWheelSpeed(&m_intake, 1));
  feederButton.WhenReleased(SetLoaderWheelSpeed(&m_intake, 0));

  frc2::JoystickButton climberButtonUp(&operatorController, (int)frc::XboxController::Button::kStart);
  climberButtonUp.WhenPressed(ClimbElevatorUp(&m_climber));

  frc2::JoystickButton climberButtonDown(&operatorController, (int)frc::XboxController::Button::kBack);
  climberButtonDown.WhenPressed(ClimbElevatorDown(&m_climber));

  frc2::JoystickButton shootButton(&operatorController, (int)frc::XboxController::Button::kBumperRight);
  shootButton.WhenHeld(frc2::SequentialCommandGroup{SetHoodToAngle(&m_shooter, [](){return 72_deg;}), SetShooterToVelocity(&m_shooter, [](){return 3800_rpm;})});
  shootButton.WhenReleased(frc2::SequentialCommandGroup{SetHoodToAngle(&m_shooter, [](){return 0_deg;}), SetShooterToVelocity(&m_shooter, [](){return 0_rpm;})});

  //frc2::JoystickButton autoShooter(&operatorController, (int)frc::XboxController::Button::kX);
  //autoShooter.WhenHeld(AutoShoot(&m_shooter));
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  return m_chooser.GetSelected();
}
