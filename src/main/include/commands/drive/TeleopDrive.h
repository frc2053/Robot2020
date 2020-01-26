#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/SwerveSubsystem.h"

class TeleopDrive
    : public frc2::CommandHelper<frc2::CommandBase, TeleopDrive> {
 public:

  explicit TeleopDrive(std::function<double()> fow, std::function<double()> strafe, std::function<double()> rot, SwerveSubsystem* subsystem);
  void Execute() override;
  bool IsFinished() override;
  void End(bool interrupted) override;
 private:
  std::function<double()> m_fow;
  std::function<double()> m_strafe;
  std::function<double()> m_rot;
  SwerveSubsystem* m_subsystem;
};
