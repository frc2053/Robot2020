#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class ConveyorOff
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 ConveyorOff> {
 public:
  ConveyorOff(IntakeSubsystem* intakeSub);

  void Initialize() override;
 private:
  IntakeSubsystem* m_intakeSubsystem;
};
