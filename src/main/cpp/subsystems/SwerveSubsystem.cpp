/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveSubsystem.h"
#include "commands/DriveCommand.h"

#include "RobotMap.h"

SwerveSubsystem::SwerveSubsystem() : frc::Subsystem("SwerveSubsystem") {}

void SwerveSubsystem::InitDefaultCommand() {
  SetDefaultCommand(new DriveCommand());
}
