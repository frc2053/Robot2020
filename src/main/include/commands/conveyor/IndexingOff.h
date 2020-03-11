#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ConveyorSubsystem.h"

class IndexingOff
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 IndexingOff> {
 public:
  IndexingOff(ConveyorSubsystem* conveyor);

  void Initialize() override;
 private:
  ConveyorSubsystem* m_conveyorSubsystem;
};
