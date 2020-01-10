#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/ControlPanelSubsystem.h"

class ManualWheelRotation 
    : public frc2::CommandHelper<frc2::CommandBase, ManualWheelRotation> {
 public: 
  explicit ManualWheelRotation(ControlPanelSubsystem* subsystem, std::function<double()> run);

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  ControlPanelSubsystem* controlPanelSubsystem;
  std::function<double()> runIt;
  bool isDone;
};