/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/intake/SetNumOfBalls.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
SetNumOfBalls::SetNumOfBalls(IntakeSubsystem* intakeSub, int balls) :
  m_intakeSubsystem(intakeSub), numOfBalls(balls) {
  AddRequirements(m_intakeSubsystem);
}

// Called when the command is initially scheduled.
void SetNumOfBalls::Initialize() {
  m_intakeSubsystem->SetNumOfBalls(numOfBalls);
}
