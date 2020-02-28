#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/SwerveSubsystem.h"

class SetRobotPose
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetRobotPose> {
 public:
  SetRobotPose(SwerveSubsystem* swerveSub, const frc::Pose2d& newPose, const frc::Rotation2d& newYaw);

  void Initialize() override;
 private:
  SwerveSubsystem* m_swerveSubsystem;
  const frc::Pose2d& m_pose;
  const frc::Rotation2d& m_yaw;
};
