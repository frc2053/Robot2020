#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ShooterSubsystem.h"

class SetShooterToVelocity
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 SetShooterToVelocity> {
 public:
  SetShooterToVelocity(ShooterSubsystem* subsystem, std::function<units::revolutions_per_minute_t()> angle);

  void Initialize() override;
 private:
  ShooterSubsystem* m_subsystem;
  std::function<units::revolutions_per_minute_t()> speed;
};
