/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/SwerveSubsystem.h"
#include "commands/drive/FollowPath.h"

class ShootBallsAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 ShootBallsAuto> {
 public:
  ShootBallsAuto(SwerveSubsystem* swerveSub, IntakeSubsystem* intakeSub, ShooterSubsystem* shooterSub);
 private:
  SwerveSubsystem* m_swerveSubsystem;
  IntakeSubsystem* m_intakeSubsystem;
  ShooterSubsystem* m_shooterSubsystem;

  frc::Pose2d startPose{0_ft, 0_ft, frc::Rotation2d(0_deg)};
  frc::Rotation2d startAngle;

  FollowPath movePastInitLine {
      10_fps, //max speed
      units::meters_per_second_squared_t(3), //max accel
      startPose, //start pt
      {}, //middle pts
      frc::Pose2d(0_ft, -1_ft, frc::Rotation2d(0_deg)), //end points and angle 
      m_swerveSubsystem //subsystem
  };
};
