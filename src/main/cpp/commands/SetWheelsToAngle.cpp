/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetWheelsToAngle.h"

SetWheelsToAngle::SetWheelsToAngle(units::radian_t fl, units::radian_t fr, units::radian_t bl, units::radian_t br,
  units::meters_per_second_t fls, units::meters_per_second_t frs, units::meters_per_second_t bls, units::meters_per_second_t brs, SwerveSubsystem* subsystem) : 
  fl_angle(fl), fr_angle(fr), bl_angle(bl), br_angle(br),
  fl_speed(fls), fr_speed(frs), bl_speed(bls), br_speed(brs), m_subsystem(subsystem) {
  SetName("SetWheelsToAngle");
  AddRequirements({m_subsystem});
}

// Called when the command is initially scheduled.
void SetWheelsToAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetWheelsToAngle::Execute() {
  m_subsystem->ManualWheelMove("FL", fl_angle, fl_speed);
  m_subsystem->ManualWheelMove("FR", fr_angle, fr_speed);
  m_subsystem->ManualWheelMove("BL", bl_angle, bl_speed);
  m_subsystem->ManualWheelMove("BR", br_angle, br_speed);
}

// Called once the command ends or is interrupted.
void SetWheelsToAngle::End(bool interrupted) {}

// Returns true when the command should end.
bool SetWheelsToAngle::IsFinished() { return true; }
