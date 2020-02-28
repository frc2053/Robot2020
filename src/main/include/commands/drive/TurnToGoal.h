#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/SwerveSubsystem.h"

class TurnToGoal
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TurnToGoal> {
 public:
  TurnToGoal(std::function<double()> fow, std::function<double()> strafe, ShooterSubsystem* shooterSub, SwerveSubsystem* swerveSub, std::function<bool()> controllerOverride);
 private:
  ShooterSubsystem* m_shooterSubsystem;
  SwerveSubsystem* m_swerveSubsystem;
};
