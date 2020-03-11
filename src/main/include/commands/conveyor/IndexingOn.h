#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ConveyorSubsystem.h"

class IndexingOn
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 IndexingOn> {
 public:
  IndexingOn(ConveyorSubsystem* conveyor);

  void Initialize() override;
 private:
  ConveyorSubsystem* m_conveyorSubsystem;
};
