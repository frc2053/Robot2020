#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class IntakeDefault
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 IntakeDefault> {
 public:
  IntakeDefault(IntakeSubsystem* intake);

  void Initialize() override;
 private:
  IntakeSubsystem* m_intakeSubsystem;
};
