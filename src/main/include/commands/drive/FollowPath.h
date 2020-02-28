#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/SwerveSubsystem.h"
#include <vector>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Translation2d.h>

class FollowPath
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 FollowPath> {
 public:
  FollowPath(units::meters_per_second_t maxSpeed, units::meters_per_second_squared_t maxAccel, const frc::Pose2d& startPt, const std::vector<frc::Translation2d>& middlePts, const frc::Pose2d& endPt, SwerveSubsystem* swerve);
 private:
  units::meters_per_second_t m_maxSpeed;
  units::meters_per_second_squared_t m_maxAccel;
  const frc::Pose2d& m_startPt;
  const std::vector<frc::Translation2d>& m_middlePts;
  const frc::Pose2d& m_endPt;
  SwerveSubsystem* m_drivetrain;
};
