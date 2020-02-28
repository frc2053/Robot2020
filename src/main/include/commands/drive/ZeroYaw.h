#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/SwerveSubsystem.h"

class ZeroYaw
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 ZeroYaw> {
 public:
  ZeroYaw(SwerveSubsystem* swerveSub);

  void Initialize() override;
 private:
  SwerveSubsystem* m_subsystem;
};
