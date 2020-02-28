#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class IntakeDown
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 IntakeDown> {
 public:
  IntakeDown(IntakeSubsystem* intake);

  void Initialize() override;
 private:
  IntakeSubsystem* intakeSub;
};
