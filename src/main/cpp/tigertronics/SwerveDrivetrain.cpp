/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tigertronics/SwerveDrivetrain.h"
#include <frc/smartdashboard/SmartDashboard.h>

SwerveDrivetrain::SwerveDrivetrain() {
    //m_imu.ZeroYaw();
    m_frontLeft.InvertDrive(true);
    m_frontRight.InvertDrive(false);
    m_backLeft.InvertDrive(true);
    m_backRight.InvertDrive(false);
    m_frontLeft.InvertRot(false);
    m_frontRight.InvertRot(false);
    m_backLeft.InvertRot(false);
    m_backRight.InvertRot(false);
}

//+x is forward
//+y is left
//+rot is CCW
void SwerveDrivetrain::Drive(units::meters_per_second_t xSpeed,
                       units::meters_per_second_t ySpeed,
                       units::radians_per_second_t rot, bool fieldRelative) {   
  std::array<frc_new::SwerveModuleState, 4> states = m_kinematics.ToSwerveModuleStates(
      fieldRelative ? frc_new::ChassisSpeeds::FromFieldRelativeSpeeds(
                          xSpeed, ySpeed, rot, GetAngle())
                    : frc_new::ChassisSpeeds{xSpeed, ySpeed, rot});

  m_kinematics.NormalizeWheelSpeeds(&states, kMaxSpeed);

  frc_new::SwerveModuleState fl = states.at(0);
  frc_new::SwerveModuleState fr = states.at(1);
  frc_new::SwerveModuleState bl = states.at(2);
  frc_new::SwerveModuleState br = states.at(3);

  frc_new::ChassisSpeeds speeds = m_kinematics.ToChassisSpeeds(fl, fr, bl, br);


  m_chassisSpeeds.dx = units::meter_t(speeds.vx.value());
  m_chassisSpeeds.dy = units::meter_t(speeds.vy.value());
  m_chassisSpeeds.dtheta = units::radian_t(speeds.omega.value());

  m_frontLeft.SetDesiredState(fl);
  m_frontRight.SetDesiredState(fr);
  m_backLeft.SetDesiredState(bl);
  m_backRight.SetDesiredState(br);
}

const frc_new::Pose2d& SwerveDrivetrain::UpdateOdometry() {
  return m_odometry.Update(GetAngle(), m_frontLeft.GetState(), m_frontRight.GetState(),
                    m_backLeft.GetState(), m_backRight.GetState());
}

const frc_new::Twist2d& SwerveDrivetrain::GetDrivetrainSpeedsWorld() {
    return m_chassisSpeeds;
}

const std::vector<double>& SwerveDrivetrain::GetIMUData() {
    m_imuData.clear();
    /*m_imuData.push_back(m_imu.GetRoll());
    m_imuData.push_back(m_imu.GetPitch());
    m_imuData.push_back(m_imu.GetYaw());
    m_imuData.push_back(m_imu.GetVelocityX());
    m_imuData.push_back(m_imu.GetVelocityY());
    m_imuData.push_back(m_imu.GetVelocityZ());
    m_imuData.push_back(m_imu.GetWorldLinearAccelX());
    m_imuData.push_back(m_imu.GetWorldLinearAccelY());
    m_imuData.push_back(m_imu.GetWorldLinearAccelZ());*/
    m_imuData.push_back(0);
    m_imuData.push_back(1);
    m_imuData.push_back(2);
    m_imuData.push_back(3);
    m_imuData.push_back(4);
    m_imuData.push_back(5);
    m_imuData.push_back(6);
    m_imuData.push_back(7);
    m_imuData.push_back(8);

    return m_imuData;
}

void SwerveDrivetrain::LogModulesToDashboard() {
    frc::SmartDashboard::PutData(&m_frontLeft);
    frc::SmartDashboard::PutData(&m_frontRight);
    frc::SmartDashboard::PutData(&m_backLeft);
    frc::SmartDashboard::PutData(&m_backRight);
}
