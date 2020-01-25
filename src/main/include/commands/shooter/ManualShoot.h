#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/ShooterSubsystem.h"

class ManualShoot
    : public frc2::CommandHelper<frc2::CommandBase, ManualShoot> {
 public:
  explicit ManualShoot(ShooterSubsystem* subsystem, std::function<double()> run, std::function<double()> adjust);

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  ShooterSubsystem* shooterSubsystem;
  std::function<double()> runIt;
  std::function<double()> adjustIt;
  bool isDone;
};