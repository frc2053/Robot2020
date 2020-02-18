/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/drive/SetRobotPose.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
SetRobotPose::SetRobotPose(SwerveSubsystem* swerveSub, const frc::Pose2d& newPose, const frc::Rotation2d& newYaw) :
    m_swerveSubsystem(swerveSub), m_pose(newPose), m_yaw(newYaw) {
    AddRequirements(m_swerveSubsystem);
}

// Called when the command is initially scheduled.
void SetRobotPose::Initialize() {
  m_swerveSubsystem->SetRobotPose(m_pose, m_yaw);
}
