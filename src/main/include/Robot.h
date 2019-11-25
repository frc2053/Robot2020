/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "subsystems/SwerveSubsystem.h"
#include "subsystems/RosBridge.h"
#include "commands/DriveCommand.h"
#include "commands/DriveWithROS.h"

class Robot : public frc::TimedRobot {
 public:
  static std::unique_ptr<SwerveSubsystem> swerveSubsystem;
  static std::unique_ptr<RosBridge> rosBridgeSubsystem;
  static std::unique_ptr<OI> oi;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
 std::unique_ptr<frc::Command> driveCommand;
 frc::SendableChooser<frc::Command*> driveChooser;
};
