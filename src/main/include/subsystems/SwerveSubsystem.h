#pragma once

#include <frc2/command/SubsystemBase.h>
#include "tigertronics/SwerveDrivetrain.h"
#include <units/units.h>

class SwerveSubsystem : public frc2::SubsystemBase {
 public:
  SwerveSubsystem();
  void DriveWithJoystick(double x, double y, double rot, bool fieldRelative);
  void AutoDrive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed);
  units::degree_t GetImuYaw();
  const frc::Pose2d& GetCurrentPose();
  const frc::Twist2d& GetCurrentTwist();
  std::vector<double> GetIMUData();
  void Periodic() override;
  void ManualWheelMove(std::string wheel, int abs_setpoint);
  void ManualWheelMove(std::string wheel, units::radian_t angle, units::meters_per_second_t speed);
  void SetRobotPose(const frc::Pose2d& newPose, const frc::Rotation2d& newYaw);
  frc::SwerveDriveOdometry<4> GetOdom();
  frc::SwerveDriveKinematics<4> GetKinematics();
  SwerveDrivetrain m_swerve;
 private:
  frc::Pose2d currentPose;
  frc::Twist2d currentTwist;
  std::vector<double> currentIMUData;
};
