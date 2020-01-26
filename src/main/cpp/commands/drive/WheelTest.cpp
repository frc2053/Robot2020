#include "commands/drive/WheelTest.h"
#include "commands/drive/SetWheelsToAngle.h"
#include <frc2/command/WaitCommand.h>

WheelTest::WheelTest(SwerveSubsystem* subsystem) : m_subsystem(subsystem) {
  AddRequirements({m_subsystem});
  AddCommands(
    SetWheelsToAngle(0_deg, 0_deg, 0_deg, 0_deg, 0_mps, 0_mps, 0_mps, 0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(45_deg, 45_deg, 45_deg, 45_deg, 0_mps, 0_mps, 0_mps, 0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(90_deg, 90_deg, 90_deg, 90_deg, 0_mps, 0_mps, 0_mps, 0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(135_deg, 135_deg, 135_deg, 135_deg, 0_mps, 0_mps, 0_mps, 0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(180_deg, 180_deg, 180_deg, 180_deg, 0_mps, 0_mps, 0_mps, 0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(225_deg, 225_deg, 225_deg, 225_deg, -0_mps, -0_mps, -0_mps, -0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(270_deg, 270_deg, 270_deg, 270_deg, -0_mps, -0_mps, -0_mps, -0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(315_deg, 315_deg, 315_deg, 315_deg, -0_mps, -0_mps, -0_mps, -0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(360_deg, 360_deg, 360_deg, 360_deg, -0_mps, -0_mps, -0_mps, -0_mps, subsystem),
    frc2::WaitCommand(1_s),
    SetWheelsToAngle(410_deg, 410_deg, 410_deg, 410_deg, 0_mps, 0_mps, 0_mps, 0_mps, subsystem)
  );
}
