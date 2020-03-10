#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ConveyorSubsystem.h"

class SetNumOfBalls
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetNumOfBalls> {
 public:
  SetNumOfBalls(ConveyorSubsystem* intakeSub, int balls);

  void Initialize() override;
 private:
  ConveyorSubsystem* m_conveyorSubsystem;
  int numOfBalls;
};
