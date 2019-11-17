/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithROS.h"
#include "Robot.h"
#include <memory>
#include <tigertronics/RosBridge/RosTypes.h>
#include <units/units.h>

DriveWithROS::DriveWithROS() {
  Requires(Robot::swerveSubsystem.get());
  Requires(Robot::rosBridgeSubsystem.get());
}

// Called just before this Command runs the first time
void DriveWithROS::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithROS::Execute() {
  std::shared_ptr<RosTypes::Twist> twist = Robot::rosBridgeSubsystem->GetTwist();
  Robot::swerveSubsystem->DriveWithROS(units::meters_per_second_t(twist->linear.x), units::meters_per_second_t(twist->linear.y), units::radians_per_second_t(twist->angular.z));
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithROS::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithROS::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithROS::Interrupted() {}
