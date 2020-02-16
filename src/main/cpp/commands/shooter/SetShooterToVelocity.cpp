/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/shooter/SetShooterToVelocity.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
SetShooterToVelocity::SetShooterToVelocity(ShooterSubsystem* subsystem, std::function<units::revolutions_per_minute_t()> angle) : m_subsystem(subsystem), speed(angle) {
  SetName("SetShooterToVelocity");
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void SetShooterToVelocity::Initialize() {
  m_subsystem->SetShooterToVelocity(speed());
}
