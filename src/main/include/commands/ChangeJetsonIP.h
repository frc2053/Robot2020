#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include <subsystems/SwerveSubsystem.h>

class ChangeJetsonIP
    : public frc2::CommandHelper<frc2::InstantCommand, ChangeJetsonIP> {
 public:
  ChangeJetsonIP(std::function<std::string()> newIp, SwerveSubsystem* subsystem);

  void Initialize() override;
 private:
  std::function<std::string()> m_newIp;
  SwerveSubsystem* m_subsystem;
};
