/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CalibrateWheels.h"

CalibrateWheels::CalibrateWheels(SwerveSubsystem* subsystem) : m_subsystem{subsystem} {
  SetName("CalibrateWheels");
  AddRequirements({m_subsystem});
  isDone = false;
}

void CalibrateWheels::Initialize() {
  m_subsystem->ChangeToCalibrationMode();
  isDone = false;
}

// Called repeatedly when this Command is scheduled to run
void CalibrateWheels::Execute() {
  m_subsystem->ManualWheelMove("FL", tigertronics::constants::swerveFLCal);
  m_subsystem->ManualWheelMove("FR", tigertronics::constants::swerveFRCal);
  m_subsystem->ManualWheelMove("BL", tigertronics::constants::swerveBLCal);
  m_subsystem->ManualWheelMove("BR", tigertronics::constants::swerveBRCal);
  isDone = true;
}

// Called once the command ends or is interrupted.
void CalibrateWheels::End(bool interrupted) {
 // m_subsystem->ChangeToDrivingMode();
}

// Returns true when the command should end.
bool CalibrateWheels::IsFinished() { return isDone; }
