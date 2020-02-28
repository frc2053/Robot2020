#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/ShooterSubsystem.h"

class SetShooterToGoal
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 SetShooterToGoal> {
 public:
  SetShooterToGoal(ShooterSubsystem* shooterSub);
 private:
  ShooterSubsystem* m_shooterSubsystem;
};
