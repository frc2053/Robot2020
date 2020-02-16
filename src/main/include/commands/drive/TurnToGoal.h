/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/SwerveSubsystem.h"

class TurnToGoal
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TurnToGoal> {
 public:
  TurnToGoal(std::function<double()> fow, std::function<double()> strafe, ShooterSubsystem* shooterSub, SwerveSubsystem* swerveSub);
 private:
  ShooterSubsystem* m_shooterSubsystem;
  SwerveSubsystem* m_swerveSubsystem;
};
