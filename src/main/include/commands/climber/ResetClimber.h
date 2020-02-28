#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/ClimberSubsystem.h"
#include "subsystems/ShooterSubsystem.h"

class ResetClimber
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 ResetClimber> {
 public:
  ResetClimber(ShooterSubsystem* shooterSub, ClimberSubsystem* climberSub);
 private:
  ShooterSubsystem* m_shooterSubsystem;
  ClimberSubsystem* m_climberSubsystem;
};
