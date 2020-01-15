/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WheelTest.h"
#include "commands/SetWheelsToAngle.h"
#include <frc2/command/WaitCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
WheelTest::WheelTest(SwerveSubsystem* subsystem) : m_subsystem(subsystem) {
  AddRequirements({m_subsystem});
  AddCommands(
    SetWheelsToAngle(0_deg, 0_deg, 0_deg, 0_deg, 3_mps, 3_mps, 3_mps, 3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(45_deg, 45_deg, 45_deg, 45_deg, 3_mps, 3_mps, 3_mps, 3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(90_deg, 90_deg, 90_deg, 90_deg, 3_mps, 3_mps, 3_mps, 3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(135_deg, 135_deg, 135_deg, 135_deg, 3_mps, 3_mps, 3_mps, 3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(180_deg, 180_deg, 180_deg, 180_deg, 3_mps, 3_mps, 3_mps, 3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(225_deg, 225_deg, 225_deg, 225_deg, -3_mps, -3_mps, -3_mps, -3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(270_deg, 270_deg, 270_deg, 270_deg, -3_mps, -3_mps, -3_mps, -3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(315_deg, 315_deg, 315_deg, 315_deg, -3_mps, -3_mps, -3_mps, -3_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(360_deg, 360_deg, 360_deg, 360_deg, -3_mps, -3_mps, -3_mps, -3_mps, subsystem)
  );
}
