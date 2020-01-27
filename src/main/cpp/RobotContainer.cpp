#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/Joystick.h"
#include "commands/drive/ROSDrive.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/drive/WheelTest.h"
#include "commands/ChangeJetsonIP.h"

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

  frc2::Button rosButton([&] {return driverController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand); });
  rosButton.WhileHeld(ROSDrive(&m_drivetrain));

  /*frc2::Button manualCPWheel([&] {return operatorController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand); });
  manualCPWheel.WhileHeld(ManualWheelRotation(&m_controlpanel, [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));

  frc2::Button rotControl([&] { return driverController.GetAButton(); });
  rotControl.WhileActiveOnce(RotationControl(&m_controlpanel));
  
  frc2::Button posControl([&] { return driverController.GetBButton(); });
  posControl.WhileActiveOnce(PositionControl(&m_controlpanel));
  
  frc2::Button manualShooter([&] {return operatorController.GetBumper(frc::GenericHID::JoystickHand::kRightHand); });
  manualShooter.WhileHeld(ManualShoot(&m_shooter, 
    [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kLeftHand);} , 
    [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));
  
  frc2::Button intakeButton([&] { return operatorController.GetAButton(); });
  intakeButton.WhileHeld(AutoIntake(&m_intake));

  frc2::Button feederButton([&] { return operatorController.GetBButton(); });
  feederButton.whileHeld(AutoFeed(&m_intake));

  frc2::Button autoShooter([&] {return operatorController.GetXButton(); });
  autoShooter.WhenHeld(AutoShoot.(&m_shooter));
  */
}
