#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ConveyorSubsystem.h"

class SetConveyorSpeed
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetConveyorSpeed> {
 public:
  SetConveyorSpeed(ConveyorSubsystem* intakeSub, double intakeSpeed);

  void Initialize() override;
 private:
  ConveyorSubsystem* m_conveyorSubsystem; 
  double speed = 0;
};
