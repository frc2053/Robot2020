#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/SwerveSubsystem.h"

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
