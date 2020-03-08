#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class SetConveyorIndexer
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetConveyorIndexer> {
 public:
  SetConveyorIndexer(IntakeSubsystem* intakeSub, double intakeSpeed, bool active);

  void Initialize() override;
 private:
  IntakeSubsystem* m_intakeSubsystem; 
  double speed = 0;
  bool active = false;
};
