/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/Joystick.h"
#include "commands/drive/ROSDrive.h"

RobotContainer::RobotContainer() : m_autonomousCommand(), m_calibrateWheelsCommand(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

  m_drivetrain.SetDefaultCommand(TeleopDrive(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kRightHand); },
    &m_drivetrain
  ));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  frc2::Button rosButton([&] {return driverController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand); });
  rosButton.WhileHeld(ROSDrive(&m_drivetrain));

  frc2::Button manualCPWheel([&] {return operatorController.GetBumper(frc::GenericHID::JoystickHand::kLeftHand); });
  manualCPWheel.WhileHeld(ManualWheelRotation(&m_controlpanel, [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));

  frc2::Button rotControl([&] { return driverController.GetAButton(); });
  rotControl.WhileActiveOnce(RotationControl(&m_controlpanel));
  
  frc2::Button posControl([&] { return driverController.GetBButton(); });
  posControl.WhileActiveOnce(PositionControl(&m_controlpanel));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

frc2::Command* RobotContainer::GetCalibrateWheelsCommand() {
  return &m_calibrateWheelsCommand;
}