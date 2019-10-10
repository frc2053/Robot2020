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
#include <tigertronics/ROSReceiver.h>
#include <tigertronics/ROSTypes.h>

SwerveSubsystem::SwerveSubsystem() : frc::Subsystem("SwerveSubsystem") {}

void SwerveSubsystem::InitDefaultCommand() {
    SetDefaultCommand(new DriveCommand());
}

void SwerveSubsystem::DriveWithJoystick(bool fieldRelative) {
    //need to negative strafe because if you push right on the joystick it returns a + value
    //however, the kinematics expects that left is positive for the y axis
    //similar for rot axis because if you push right on the stick, it returns a positive value
    //however, the kinematics expects a "positive" rotation to be CCW
    double strafeAxis = -Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kLeftHand);
    double fowAxis = Robot::oi->GetDriverJoystick().GetY(frc::GenericHID::JoystickHand::kLeftHand);
    double rotAxis = -Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kRightHand);

    if(strafeAxis > -.2 && strafeAxis < .2) {
        strafeAxis = 0;
    }
    else {
        strafeAxis = strafeAxis * fabs(strafeAxis);
    }
    if(fowAxis > -.2 && fowAxis < .2) {
        fowAxis = 0;
    }
    else {
        fowAxis = fowAxis * fabs(fowAxis);
    }
    if(rotAxis > -.2 && rotAxis < .2) {
        rotAxis = 0;
    }
    else {
        rotAxis = rotAxis * fabs(rotAxis);
    }
    SmartDashboard::PutNumber("X Joystick", strafeAxis);
    SmartDashboard::PutNumber("Y Joystick", fowAxis);
    SmartDashboard::PutNumber("Rot Joystick", rotAxis);
    //x + is forward
    //y + is left
    //rot + is CCW
    const auto xSpeed = fowAxis * m_swerve.kMaxSpeed;
    const auto ySpeed = strafeAxis * m_swerve.kMaxSpeed;
    const auto rotSpeed = rotAxis * m_swerve.kMaxAngularSpeed;
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, fieldRelative);

    rostypes::Twist cmd_vel = ROSReceiver::GetTwist("cmd_vel");
    std::cout << "cmd_vel linear [" << cmd_vel.linear.x << "," << cmd_vel.linear.y << "," << cmd_vel.linear.z << "]\n";
    std::cout << "cmd_vel angular [" << cmd_vel.angular.x << "," << cmd_vel.angular.y << "," << cmd_vel.angular.z << "]\n";
}

void SwerveSubsystem::Periodic() {
    frc_new::Pose2d pose = m_swerve.UpdateOdometry();
    frc::SmartDashboard::PutNumber("X Pose: ", pose.Translation().X().value());
    frc::SmartDashboard::PutNumber("Y Pose: ", pose.Translation().Y().value());
    frc::SmartDashboard::PutNumber("Yaw Pose: ", pose.Rotation().Degrees().value());
}