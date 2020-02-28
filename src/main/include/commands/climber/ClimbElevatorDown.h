#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ClimberSubsystem.h"

class ClimbElevatorDown
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 ClimbElevatorDown> {
 public:
  ClimbElevatorDown(ClimberSubsystem* climbSub);

  void Initialize() override;
 private: 
  ClimberSubsystem* m_climberSubsystem;
};
