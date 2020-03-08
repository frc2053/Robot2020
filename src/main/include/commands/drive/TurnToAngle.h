#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>
#include <units/units.h>
#include "subsystems/SwerveSubsystem.h"
#include <frc/XboxController.h>

class TurnToAngle
    : public frc2::CommandHelper<frc2::PIDCommand, TurnToAngle> {
 public:
  TurnToAngle(std::function<double()> fow, std::function<double()> strafe, std::function<double()> targetAngle, SwerveSubsystem* swerveSub, std::function<bool()> override);

  bool IsFinished() override;
 private:
  std::function<bool()> controllerOverride;
};
