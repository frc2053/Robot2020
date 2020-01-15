/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/SwerveSubsystem.h"
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class SetWheelsToAngle
    : public frc2::CommandHelper<frc2::CommandBase, SetWheelsToAngle> {
 public:
  SetWheelsToAngle(units::radian_t fl, units::radian_t fr, units::radian_t bl, units::radian_t br,
  units::meters_per_second_t fls, units::meters_per_second_t frs, units::meters_per_second_t bls, units::meters_per_second_t brs, SwerveSubsystem* subsystem);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  units::radian_t fl_angle;
  units::radian_t fr_angle;
  units::radian_t bl_angle;
  units::radian_t br_angle;
  units::meters_per_second_t fl_speed;
  units::meters_per_second_t fr_speed;
  units::meters_per_second_t bl_speed;
  units::meters_per_second_t br_speed;
  SwerveSubsystem* m_subsystem;
};
