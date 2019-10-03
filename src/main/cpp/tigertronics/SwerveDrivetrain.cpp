/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tigertronics/SwerveDrivetrain.h"

SwerveDrivetrain::SwerveDrivetrain() {
    m_imu.ZeroYaw();
}

void SwerveDrivetrain::Drive(units::meters_per_second_t xSpeed,
                       units::meters_per_second_t ySpeed,
                       units::radians_per_second_t rot, bool fieldRelative) {
  auto states = m_kinematics.ToSwerveModuleStates(
      fieldRelative ? frc_new::ChassisSpeeds::FromFieldRelativeSpeeds(
                          xSpeed, ySpeed, rot, GetAngle())
                    : frc_new::ChassisSpeeds{xSpeed, ySpeed, rot});

  m_kinematics.NormalizeWheelSpeeds(&states, kMaxSpeed);

  std::array<frc_new::SwerveModuleState, 4> currentState = states;
  frc_new::SwerveModuleState fl = currentState.at(0);
  frc_new::SwerveModuleState fr = currentState.at(1);
  frc_new::SwerveModuleState bl = currentState.at(2);
  frc_new::SwerveModuleState br = currentState.at(3);

  m_frontLeft.SetDesiredState(fl);
  m_frontRight.SetDesiredState(fr);
  m_backLeft.SetDesiredState(bl);
  m_backRight.SetDesiredState(br);
}

const frc_new::Pose2d& SwerveDrivetrain::UpdateOdometry() {
  return m_odometry.Update(GetAngle(), m_frontLeft.GetState(), m_frontRight.GetState(),
                    m_backLeft.GetState(), m_backRight.GetState());
}
