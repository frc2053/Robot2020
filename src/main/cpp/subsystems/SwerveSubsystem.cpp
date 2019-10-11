/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveSubsystem.h"
#include "commands/DriveCommand.h"
#include "Robot.h"
#include "frc/smartdashboard/SmartDashboard.h"

SwerveSubsystem::SwerveSubsystem() : frc::Subsystem("SwerveSubsystem") {}

void SwerveSubsystem::InitDefaultCommand() {
    SetDefaultCommand(new DriveCommand());
}

void SwerveSubsystem::DriveWithJoystick(bool fieldRelative) {
    double xAxis = Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kLeftHand);
    double yAxis = Robot::oi->GetDriverJoystick().GetY(frc::GenericHID::JoystickHand::kLeftHand);
    double rotAxis = Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kRightHand);

    if(xAxis > -.2 && xAxis < .2) {
        xAxis = 0;
    }
    else {
        xAxis = xAxis * fabs(xAxis);
    }
    if(yAxis > -.2 && yAxis < .2) {
        yAxis = 0;
    }
    else {
        yAxis = yAxis * fabs(yAxis);
    }
    if(rotAxis > -.2 && rotAxis < .2) {
        rotAxis = 0;
    }
    else {
        rotAxis = rotAxis * fabs(rotAxis);
    }
    SmartDashboard::PutNumber("X Joystick", xAxis);
    SmartDashboard::PutNumber("Y Joystick", yAxis);
    SmartDashboard::PutNumber("Rot Joystick", rotAxis);
    const auto xSpeed = xAxis * m_swerve.kMaxSpeed;
    const auto ySpeed = -yAxis * m_swerve.kMaxSpeed;
    const auto rotSpeed = -rotAxis * m_swerve.kMaxAngularSpeed;
    m_swerve.Drive(ySpeed, xSpeed, rotSpeed, fieldRelative);
}

void SwerveSubsystem::Periodic() {
    frc_new::Pose2d pose = m_swerve.UpdateOdometry();
    frc::SmartDashboard::PutNumber("X Pose: ", pose.Translation().X().value());
    frc::SmartDashboard::PutNumber("Y Pose: ", pose.Translation().Y().value());
    frc::SmartDashboard::PutNumber("Yaw Pose: ", pose.Rotation().Degrees().value());
}