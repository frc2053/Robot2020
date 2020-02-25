/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/climber/PTOClimbOff.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
PTOClimbOff::PTOClimbOff(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

// Called when the command is initially scheduled.
void PTOClimbOff::Initialize() {
  m_climberSubsystem->SetPTO(frc::DoubleSolenoid::Value::kReverse);
}
