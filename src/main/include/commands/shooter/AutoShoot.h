#pragma once

#include <frc2/command/Commandbase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/ShooterSubsystem.h"

class AutoShoot
    : public frc2::CommandHelper<frc2::CommandBase, AutoShoot> {
 public:
  explicit AutoShoot(ShooterSubsystem* subsystem);

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  ShooterSubsystem* shooterSubsystem;
};