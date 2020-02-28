#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/IntakeSubsystem.h"

class TeleopIntakeUp
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TeleopIntakeUp> {
 public:
  TeleopIntakeUp(IntakeSubsystem* intakeSub);
 private:
  IntakeSubsystem* m_intakeSubsystem;
};
