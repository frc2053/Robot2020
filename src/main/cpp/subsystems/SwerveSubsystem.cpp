/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveSubsystem.h"
#include "commands/DriveCommand.h"
#include "commands/DriveWithROS.h"
#include "Robot.h"
#include "frc/smartdashboard/SmartDashboard.h"

SwerveSubsystem::SwerveSubsystem() : frc::Subsystem("SwerveSubsystem") {}

void SwerveSubsystem::InitDefaultCommand() {
    //SetDefaultCommand(new DriveCommand());
    SetDefaultCommand(new DriveWithROS());
}

void SwerveSubsystem::DriveWithRos(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed) {
    SmartDashboard::PutNumber("X Cmd", xSpeed.value());
    SmartDashboard::PutNumber("Y Cmd", ySpeed.value());
    SmartDashboard::PutNumber("Rot Cmd", rotSpeed.value());
    SmartDashboard::PutString("Drive Mode", "ROS");
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, false);
}

void SwerveSubsystem::DriveWithJoystick(bool fieldRelative) {
    //need to negative strafe because if you push right on the joystick it returns a + value
    //however, the kinematics expects that left is positive for the y axis
    //similar for rot axis because if you push right on the stick, it returns a positive value
    //however, the kinematics expects a "positive" rotation to be CCW
    double strafeAxis = -Robot::oi->GetDriverJoystick().GetX(frc::GenericHID::JoystickHand::kLeftHand);
    double fowAxis = -Robot::oi->GetDriverJoystick().GetY(frc::GenericHID::JoystickHand::kLeftHand);
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
    SmartDashboard::PutString("Drive Mode", "Joystick");
    //x + is forward
    //y + is left
    //rot + is CCW
    const auto xSpeed = fowAxis * m_swerve.kMaxSpeed;
    const auto ySpeed = strafeAxis * m_swerve.kMaxSpeed;
    const auto rotSpeed = rotAxis * m_swerve.kMaxAngularSpeed;
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, fieldRelative);
}

void SwerveSubsystem::Periodic() {
    currentPose = m_swerve.UpdateOdometry();
    currentTwist = m_swerve.GetDrivetrainSpeedsWorld();
    currentIMUData = m_swerve.GetIMUData();
    frc::SmartDashboard::PutNumber("X Pose: ", currentPose.Translation().X().value());
    frc::SmartDashboard::PutNumber("Y Pose: ", currentPose.Translation().Y().value());
    frc::SmartDashboard::PutNumber("Yaw Pose: ", currentPose.Rotation().Degrees().value());
}

const frc_new::Pose2d& SwerveSubsystem::GetCurrentPose() {
    return currentPose;
}

const frc_new::Twist2d& SwerveSubsystem::GetCurrentTwist() {
    return currentTwist;
}

std::vector<double> SwerveSubsystem::GetIMUData() {
    return currentIMUData;
}