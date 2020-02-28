#include "commands/drive/SetRobotPose.h"

SetRobotPose::SetRobotPose(SwerveSubsystem* swerveSub, const frc::Pose2d& newPose, const frc::Rotation2d& newYaw) :
    m_swerveSubsystem(swerveSub), m_pose(newPose), m_yaw(newYaw) {
    AddRequirements(m_swerveSubsystem);
}

void SetRobotPose::Initialize() {
  m_swerveSubsystem->SetRobotPose(m_pose, m_yaw);
}
