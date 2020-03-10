#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "commands/drive/WheelTest.h"
#include "commands/drive/TurnToAngle.h"
#include <commands/shooter/SetHoodToAngle.h>
#include "commands/drive/TeleopDrive.h"
#include "commands/controlpanel/ManualWheelRotation.h"
#include "commands/controlpanel/RotationControl.h"
#include "commands/controlpanel/PositionControl.h"
#include "commands/shooter/SetShooterToVelocity.h"
#include "commands/intake/SetLoaderWheelSpeed.h"
#include "commands/intake/SetFunnelWheelSpeed.h"
#include "frc2/command/ParallelRaceGroup.h"
#include "commands/intake/TeleopIntakeDown.h"
#include "commands/intake/TeleopIntakeUp.h"
#include "commands/climber/ClimbElevatorUp.h"
#include "commands/climber/ClimbElevatorDown.h"
#include "commands/drive/ZeroYaw.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/shooter/SetShooterToVelocity.h"
#include "commands/drive/TurnToGoal.h"
#include "commands/conveyor/SetConveyorSpeed.h"
#include "commands/shooter/SetShooterToGoal.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include "commands/conveyor/IndexConveyor.h"

RobotContainer::RobotContainer() : m_drivetrain(){

  m_drivetrain.SetDefaultCommand(TeleopDrive(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kRightHand); },
    &m_drivetrain
  ));

  m_conveyor.SetDefaultCommand(std::move(IndexConveyor(
    &m_conveyor
  )));

  m_controlpanel.SetDefaultCommand(std::move(ManualWheelRotation(
    &m_controlpanel,
    [this] { return operatorController.GetX(frc::GenericHID::JoystickHand::kLeftHand); }
  )));

  m_chooser.SetDefaultOption("Follow Path Auto", &m_followPathAuto);
  m_chooser.AddOption("Ten Cell Auto", &m_tenCellAuto);
  m_chooser.AddOption("Shoot Balls Auto", &m_shootBallsAuto);

  m_controlChooser.SetDefaultOption("Manual", &m_wheelControl);
  m_controlChooser.AddOption("Position Control", &m_posControl);
  m_controlChooser.AddOption("Rotation Control", &m_rotControl);

  frc::Shuffleboard::GetTab("Auto").Add(m_chooser);
  frc::Shuffleboard::GetTab("ControlPanel").Add(m_controlChooser);

  ConfigureButtonBindings();

  //frc::SmartDashboard::PutNumber("Shooter Velocity", 0);
  //frc::SmartDashboard::PutNumber("Shooter Angle", 0);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Zero Yaw", new ZeroYaw(&m_drivetrain));
  frc::SmartDashboard::PutData("Wheel Test", new WheelTest(&m_drivetrain));
  frc::SmartDashboard::PutData("Set Shooter Goal", new SetShooterToGoal(&m_shooter));


  //frc::SmartDashboard::PutData("Set Wheel To RPM", new SetShooterToVelocity(&m_shooter, [this] { return units::revolutions_per_minute_t(frc::SmartDashboard::GetNumber("Shooter Velocity", 0)); }));
  //frc::SmartDashboard::PutData("Set Hood To Angle", new SetHoodToAngle(&m_shooter, [this] { return units::degree_t(frc::SmartDashboard::GetNumber("Shooter Angle", 0)); }));

  frc2::JoystickButton rotateToZeroButton(&driverController, (int)frc::XboxController::Button::kY);
  rotateToZeroButton.WhenHeld(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      [](){return 0; },
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return val > .2 || val < -.2; 
      }
    )
  );

  frc2::JoystickButton rotateToGenerator112Button(&driverController, (int)frc::XboxController::Button::kX);
  rotateToGenerator112Button.WhenHeld(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      [](){return 112.5; },
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return val > .2 || val < -.2; 
      }
    )
  );

  frc2::JoystickButton rotateToGenerator67Button(&driverController, (int)frc::XboxController::Button::kB);
  rotateToGenerator67Button.WhenHeld(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      [](){return -67.5; },
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return val > .2 || val < -.2; 
      }
    )
  );

  frc2::JoystickButton rotateTo180Button(&driverController, (int)frc::XboxController::Button::kA);
  rotateTo180Button.WhenHeld(
    TurnToAngle(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      [](){return 180; },
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return val > .2 || val < -.2; 
      }
    )
  );

  frc2::JoystickButton rotateToGoal(&driverController, (int)frc::XboxController::Button::kBumperRight);
  rotateToGoal.WhenHeld(
    TurnToGoal(
      [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
      [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
      &m_shooter,
      &m_drivetrain,
      [this] {
        double val = driverController.GetX(frc::XboxController::JoystickHand::kRightHand);
        return val > .2 || val < -.2; 
      }
    )
  );

  frc2::JoystickButton intakeButton(&operatorController, (int)frc::XboxController::Button::kA);
  intakeButton.WhileHeld(frc2::SequentialCommandGroup{TeleopIntakeDown(&m_intake), SetFunnelWheelSpeed(&m_intake, 1)});
  intakeButton.WhenReleased(frc2::SequentialCommandGroup{TeleopIntakeUp(&m_intake), SetFunnelWheelSpeed(&m_intake, 0)});

  frc2::JoystickButton conveyorButton(&operatorController, (int)frc::XboxController::Button::kB);
  conveyorButton.WhileHeld(frc2::SequentialCommandGroup{SetConveyorSpeed(&m_conveyor, .5), SetFunnelWheelSpeed(&m_intake, 1)});
  conveyorButton.WhenReleased(frc2::SequentialCommandGroup{SetConveyorSpeed(&m_conveyor, 0), SetFunnelWheelSpeed(&m_intake, 0)});

  frc2::JoystickButton feederButton(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  feederButton.WhileHeld(frc2::SequentialCommandGroup{SetLoaderWheelSpeed(&m_intake, 1), SetConveyorSpeed(&m_conveyor, 1)});
  feederButton.WhenReleased(frc2::SequentialCommandGroup{SetLoaderWheelSpeed(&m_intake, 0), SetConveyorSpeed(&m_conveyor, 0)});

  frc2::JoystickButton climberButtonUp(&operatorController, (int)frc::XboxController::Button::kStart);
  climberButtonUp.WhenPressed(ClimbElevatorUp(&m_climber));

  frc2::JoystickButton climberButtonDown(&operatorController, (int)frc::XboxController::Button::kBack);
  climberButtonDown.WhenPressed(ClimbElevatorDown(&m_climber));

  frc2::JoystickButton controlPanelThing(&operatorController, (int)frc::XboxController::Button::kY);
  controlPanelThing.WhenPressed(m_controlChooser.GetSelected());

  frc2::JoystickButton shootButton(&operatorController, (int)frc::XboxController::Button::kBumperRight);
  shootButton.WhileHeld(frc2::SequentialCommandGroup {
    frc2::InstantCommand(
      [this]() {
          m_shooter.moveRequested = true;
      }
    ),
    SetFunnelWheelSpeed(&m_intake, 1),
    SetHoodToAngle(&m_shooter, [this](){return m_shooter.GetAngleToGoTo();}), 
    SetShooterToVelocity(&m_shooter, [this](){return m_shooter.GetRPMToGoTo();})
  });
  shootButton.WhenReleased(frc2::SequentialCommandGroup {
    frc2::InstantCommand(
      [this]() {
          m_shooter.moveRequested = false;
      }
    ),
    SetFunnelWheelSpeed(&m_intake, 0),
    SetHoodToAngle(&m_shooter, [](){return 0_deg;}), 
    SetShooterToVelocity(&m_shooter, [](){return 0_rpm;})
  });
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  return m_chooser.GetSelected();
}
