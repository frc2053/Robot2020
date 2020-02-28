#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/IntakeSubsystem.h"

class SetLoaderWheelSpeed
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetLoaderWheelSpeed> {
 public:
  SetLoaderWheelSpeed(IntakeSubsystem* intakeSub, double intakeSpeed);

  void Initialize() override;
 private:
  IntakeSubsystem* m_intakeSubsystem; 
  double speed = 0;
};
