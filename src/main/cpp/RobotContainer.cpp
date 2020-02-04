#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/Joystick.h"
#include "commands/drive/ROSDrive.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/drive/WheelTest.h"
#include "commands/ChangeJetsonIP.h"
#include "commands/drive/TurnToAngle.h"

RobotContainer::RobotContainer() : m_drivetrain(){

  m_drivetrain.SetDefaultCommand(TeleopDrive(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kRightHand); },
    &m_drivetrain
  ));

  ConfigureButtonBindings();
  
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Change Jetson IP", new ChangeJetsonIP([this] { return frc::SmartDashboard::GetString("Jetson IP", "10.20.53.42"); }, &m_drivetrain));
  frc::SmartDashboard::PutData("Wheel Test", new WheelTest(&m_drivetrain));

  frc2::JoystickButton rosButton(&driverController, (int)frc::XboxController::Button::kBumperLeft);
  rosButton.WhileHeld(ROSDrive(&m_drivetrain));

  frc2::JoystickButton rotateToZeroButton(&driverController, (int)frc::XboxController::Button::kY);
  rotateToZeroButton.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    0_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton rotateToGenerator112Button(&driverController, (int)frc::XboxController::Button::kX);
  rotateToGenerator112Button.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    112.5_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton rotateToGenerator67Button(&driverController, (int)frc::XboxController::Button::kB);
  rotateToGenerator67Button.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    -67.5_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton rotateTo180Button(&driverController, (int)frc::XboxController::Button::kA);
  rotateTo180Button.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    180_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton manualCPWheel(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  manualCPWheel.WhileHeld(ManualWheelRotation(&m_controlpanel, [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));

  frc2::JoystickButton rotControl(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  rotControl.WhileActiveOnce(RotationControl(&m_controlpanel));
  
  frc2::JoystickButton posControl(&operatorController, (int)frc::XboxController::Button::kB);
  posControl.WhileActiveOnce(PositionControl(&m_controlpanel));
  
  frc2::JoystickButton manualShooter(&operatorController, (int)frc::XboxController::Button::kBumperRight);
  manualShooter.WhileHeld(ManualShoot(&m_shooter, 
    [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kLeftHand);} , 
    [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));
  
  frc2::JoystickButton intakeButton(&operatorController, (int)frc::XboxController::Button::kA);
  intakeButton.WhileHeld(AutoIntake(&m_intake));

  frc2::JoystickButton feederButton(&operatorController, (int)frc::XboxController::Button::kB);
  feederButton.WhileHeld(AutoFeed(&m_intake));

  frc2::JoystickButton autoShooter(&operatorController, (int)frc::XboxController::Button::kX);
  autoShooter.WhenHeld(AutoShoot(&m_shooter));
  
}
