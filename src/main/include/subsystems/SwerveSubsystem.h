/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "tigertronics/SwerveDrivetrain.h"

class SwerveSubsystem : public frc::Subsystem {
 public:
  SwerveSubsystem();
  void InitDefaultCommand() override;
  void DriveWithJoystick(bool fieldRelative);
  void DriveWithRos(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed);
  virtual void Periodic();
 private:
  SwerveDrivetrain m_swerve;
};
