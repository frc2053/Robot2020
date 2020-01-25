#pragma once

#include <frc2/command/Commandbase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/IntakeSubsystem.h"

class AutoFeed 
    : public frc2::CommandHelper<frc2::CommandBase, AutoFeed> {
 public: 
  explicit AutoFeed(IntakeSubsystem* subsystem);

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  IntakeSubsystem* intakeSubsystem;
};