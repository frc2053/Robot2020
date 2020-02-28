#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ShooterSubsystem.h"

class SetHoodToAngle
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetHoodToAngle> {
 public:
  SetHoodToAngle(ShooterSubsystem* subsystem, std::function<units::degree_t()> angle);

  void Initialize() override;
 private:
  ShooterSubsystem* m_subsystem;
  std::function<units::degree_t()> angleToGoTo;
};
