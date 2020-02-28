#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/IntakeSubsystem.h"

class TeleopIntakeDown
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TeleopIntakeDown> {
 public:
  TeleopIntakeDown(IntakeSubsystem* intakeSub);
 private:
  IntakeSubsystem* m_intakeSubsystem;
};
