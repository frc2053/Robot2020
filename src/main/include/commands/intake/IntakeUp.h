#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class IntakeUp
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 IntakeUp> {
 public:
  IntakeUp(IntakeSubsystem* intake);

  void Initialize() override;
 private:
  IntakeSubsystem* intakeSub;
};
