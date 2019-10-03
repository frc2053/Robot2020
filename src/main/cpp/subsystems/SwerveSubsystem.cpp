/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveSubsystem.h"
#include "commands/DriveCommand.h"
#include "Robot.h"

SwerveSubsystem::SwerveSubsystem() : frc::Subsystem("SwerveSubsystem") {}

void SwerveSubsystem::InitDefaultCommand() {
    SetDefaultCommand(new DriveCommand());
}

void SwerveSubsystem::DriveWithJoystick(bool fieldRelative) {
    const auto xSpeed = -Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kLeftHand) * m_swerve.kMaxSpeed;
    const auto ySpeed = -Robot::oi->GetDriverJoystick().GetY(frc::GenericHID::JoystickHand::kLeftHand) * m_swerve.kMaxSpeed;
    const auto rotSpeed = -Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kRightHand) * m_swerve.kMaxAngularSpeed;
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, fieldRelative);
}

void SwerveSubsystem::Periodic() {
    m_swerve.UpdateOdometry();
}