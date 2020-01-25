#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <subsystems/SwerveSubsystem.h>

class ROSDrive
    : public frc2::CommandHelper<frc2::CommandBase, ROSDrive> {
 public:
  ROSDrive(SwerveSubsystem* subsystem);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  SwerveSubsystem* m_subsystem;
};
