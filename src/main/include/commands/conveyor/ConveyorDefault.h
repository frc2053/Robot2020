#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ConveyorSubsystem.h"

class ConveyorDefault
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 ConveyorDefault> {
 public:
  IndexingOn(ConveyorSubsystem* conveyor);

  void Initialize() override;
 private:
  ConveyorSubsystem* m_conveyorSubsystem;
};
