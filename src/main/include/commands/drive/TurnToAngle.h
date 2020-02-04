/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>
#include <units/units.h>
#include "subsystems/SwerveSubsystem.h"

class TurnToAngle
    : public frc2::CommandHelper<frc2::PIDCommand, TurnToAngle> {
 public:
  TurnToAngle(std::function<double()> fow, std::function<double()> strafe, units::degree_t targetAngle, SwerveSubsystem* swerveSub);

  bool IsFinished() override;
};
