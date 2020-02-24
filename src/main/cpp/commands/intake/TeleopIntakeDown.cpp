/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/intake/TeleopIntakeDown.h"
#include "commands/intake/IntakeDown.h"
#include "commands/intake/SetIntakeSpeed.h"
#include "commands/intake/SetConveyorSpeed.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
TeleopIntakeDown::TeleopIntakeDown(IntakeSubsystem* intakeSub) : m_intakeSubsystem(intakeSub) {
  AddCommands(
    IntakeDown(intakeSub),
    SetIntakeSpeed(intakeSub, 1),
    SetConveyorSpeed(intakeSub, 1)
  );
}
