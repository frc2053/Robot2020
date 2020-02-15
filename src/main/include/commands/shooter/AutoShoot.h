/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ShooterSubsystem.h"

class AutoShoot
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 AutoShoot> {
 public:
  AutoShoot(ShooterSubsystem* subsystem, std::function<units::revolutions_per_minute_t()> angle);

  void Initialize() override;
 private:
  ShooterSubsystem* m_subsystem;
  std::function<units::revolutions_per_minute_t()> speed;
};
