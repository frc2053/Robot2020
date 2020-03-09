#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class FeedingOff
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 FeedingOff> {
 public:
  FeedingOff(IntakeSubsystem* intakeSub);

  void Initialize() override;
 private:
  IntakeSubsystem* m_intakeSubsystem;
};
