/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/Joystick.h"
#include "commands/ROSDrive.h"
#include "commands/CalibrateWheels.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/WheelTest.h"
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
  frc::SmartDashboard::PutData("Test Wheels Command", new WheelTest(&m_drivetrain));

  frc2::JoystickButton rosButton(&driverController, (int) frc::XboxController::Button::kBumperLeft);
  rosButton.WhenHeld(ROSDrive(&m_drivetrain));

  frc2::JoystickButton calButton(&driverController, (int) frc::XboxController::Button::kA);
  calButton.WhenPressed(CalibrateWheels(&m_drivetrain));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

frc2::Command* RobotContainer::GetCalibrateWheelsCommand() {
  return &m_calibrateWheelsCommand;
}
