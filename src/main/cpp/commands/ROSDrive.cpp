/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ROSDrive.h"

ROSDrive::ROSDrive(SwerveSubsystem* subsystem) : m_subsystem{subsystem} {
  AddRequirements({m_subsystem});
}

// Called when the command is initially scheduled.
void ROSDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ROSDrive::Execute() {
  std::shared_ptr<RosTypes::Twist> twist = m_subsystem->GetTwist();
  m_subsystem->DriveWithRos(units::meters_per_second_t(twist->linear.x), units::meters_per_second_t(twist->linear.y), units::radians_per_second_t(twist->angular.z));
}

// Called once the command ends or is interrupted.
void ROSDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool ROSDrive::IsFinished() { return false; }
