/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc_new/geometry/Translation2d.h>
#include <frc_new/kinematics/SwerveDriveKinematics.h>
#include <frc_new/kinematics/SwerveDriveOdometry.h>
#include <AHRS.h>
#include <tigertronics/SwerveModule.h>
#include <Constants.h>

#define M_PI 3.14159265358979323846

/**
 * Represents a swerve drive style drivetrain.
 */
class SwerveDrivetrain {
 public:
  SwerveDrivetrain();

  /**
   * Get the robot angle as a Rotation2d.
   */
  frc_new::Rotation2d GetAngle() {
    // Negating the angle because WPILib Gyros are CW positive.
    return frc_new::Rotation2d(units::degree_t(-m_imu.GetYaw()));
  }

  void Drive(units::meters_per_second_t xSpeed,
             units::meters_per_second_t ySpeed, units::radians_per_second_t rot,
             bool fieldRelative);
  void UpdateOdometry();

  static constexpr units::meters_per_second_t kMaxSpeed =
      3.0_mps;  // 3 meters per second
  static constexpr units::radians_per_second_t kMaxAngularSpeed{
      M_PI};  // 1/2 rotation per second

 private:
    //not what the convension of the translation 2d is
    //so I am sticking with the example where 
    //postive x is left and positive y is 
    units::meter_t widthLoc = tigertronics::constants::drivebaseWidth / 2_m;
    units::meter_t lengthLoc = tigertronics::constants::drivebaseLength / 2_m;
    frc_new::Translation2d m_frontLeftLocation{widthLoc, lengthLoc};
    frc_new::Translation2d m_frontRightLocation{widthLoc, -lengthLoc};
    frc_new::Translation2d m_backLeftLocation{-widthLoc, lengthLoc};
    frc_new::Translation2d m_backRightLocation{-widthLoc, -lengthLoc};

    SwerveModule m_frontLeft{tigertronics::ports::swerveFLDrive, tigertronics::ports::swerveFLTurn, 0};
    SwerveModule m_frontRight{tigertronics::ports::swerveFRDrive, tigertronics::ports::swerveFRTurn, 0};
    SwerveModule m_backLeft{tigertronics::ports::swerveBLDrive, tigertronics::ports::swerveBLTurn, 0};
    SwerveModule m_backRight{tigertronics::ports::swerveBRDrive, tigertronics::ports::swerveBRTurn, 0};

    AHRS m_imu{frc::SPI::Port::kMXP};

    frc_new::SwerveDriveKinematics<4> m_kinematics{
        m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation,
        m_backRightLocation};

    frc_new::SwerveDriveOdometry<4> m_odometry{m_kinematics};
};