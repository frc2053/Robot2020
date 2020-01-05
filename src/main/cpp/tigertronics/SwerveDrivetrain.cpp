/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tigertronics/SwerveDrivetrain.h"
#include <frc/smartdashboard/SmartDashboard.h>

SwerveDrivetrain::SwerveDrivetrain() {
    m_imu.ZeroYaw();
    m_frontLeft.InvertDrive(true);
    m_frontRight.InvertDrive(false);
    m_backLeft.InvertDrive(true);
    m_backRight.InvertDrive(false);
    m_frontLeft.InvertRot(false);
    m_frontRight.InvertRot(false);
    m_backLeft.InvertRot(false);
    m_backRight.InvertRot(false);
}

void SwerveDrivetrain::SetupForCalibration() {
    m_frontLeft.SetupForCalibration();
    m_frontRight.SetupForCalibration();
    m_backLeft.SetupForCalibration();
    m_backRight.SetupForCalibration();
}

void SwerveDrivetrain::SetupForDriving() {
    m_frontLeft.SetupTurningMotor();
    m_frontRight.SetupTurningMotor();
    m_backLeft.SetupTurningMotor();
    m_backRight.SetupTurningMotor();
}

void SwerveDrivetrain::ManualMoveWheel(std::string wheel, int setpoint) {
    if(wheel == "FL") {
        m_frontLeft.SetSetpointAbs(setpoint);
    }
    if(wheel == "FR") {
        m_frontRight.SetSetpointAbs(setpoint);
    }
    if(wheel == "BL") {
        m_backLeft.SetSetpointAbs(setpoint);
    }
    if(wheel == "BR") {
        m_backRight.SetSetpointAbs(setpoint);
    }
}

//+x is forward
//+y is left
//+rot is CCW
void SwerveDrivetrain::Drive(units::meters_per_second_t xSpeed,
                       units::meters_per_second_t ySpeed,
                       units::radians_per_second_t rot, bool fieldRelative) {   
  std::array<frc::SwerveModuleState, 4> states = m_kinematics.ToSwerveModuleStates(
      fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(
                          xSpeed, ySpeed, rot, GetAngle())
                    : frc::ChassisSpeeds{xSpeed, ySpeed, rot});

  m_kinematics.NormalizeWheelSpeeds(&states, kMaxSpeed);

  frc::SwerveModuleState fl = states.at(0);
  frc::SwerveModuleState fr = states.at(1);
  frc::SwerveModuleState bl = states.at(2);
  frc::SwerveModuleState br = states.at(3);

  frc::ChassisSpeeds speeds = m_kinematics.ToChassisSpeeds(fl, fr, bl, br);


  m_chassisSpeeds.dx = units::meter_t(speeds.vx.value());
  m_chassisSpeeds.dy = units::meter_t(speeds.vy.value());
  m_chassisSpeeds.dtheta = units::radian_t(speeds.omega.value());

  m_frontLeft.SetDesiredState(fl);
  m_frontRight.SetDesiredState(fr);
  m_backLeft.SetDesiredState(bl);
  m_backRight.SetDesiredState(br);
}

const frc::Pose2d& SwerveDrivetrain::UpdateOdometry() {
  return m_odometry.Update(GetAngle(), m_frontLeft.GetState(), m_frontRight.GetState(),
                    m_backLeft.GetState(), m_backRight.GetState());
}

const frc::Twist2d& SwerveDrivetrain::GetDrivetrainSpeedsWorld() {
    return m_chassisSpeeds;
}

std::vector<double> SwerveDrivetrain::GetIMUData() {
    std::vector<double> imuData;
    imuData.push_back(m_imu.GetRoll());
    imuData.push_back(m_imu.GetPitch());
    imuData.push_back(m_imu.GetYaw());
    imuData.push_back(m_imu.GetVelocityX());
    imuData.push_back(m_imu.GetVelocityY());
    imuData.push_back(m_imu.GetVelocityZ());
    imuData.push_back(m_imu.GetWorldLinearAccelX());
    imuData.push_back(m_imu.GetWorldLinearAccelY());
    imuData.push_back(m_imu.GetWorldLinearAccelZ());
    return imuData;
}

void SwerveDrivetrain::LogModulesToDashboard() {
    frc::SmartDashboard::PutData(&m_frontLeft);
    frc::SmartDashboard::PutData(&m_frontRight);
    frc::SmartDashboard::PutData(&m_backLeft);
    frc::SmartDashboard::PutData(&m_backRight);
}
