/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/auto/TenPowerCellAuto.h"
#include "commands/intake/IntakeDown.h"
#include "commands/intake/IntakeUp.h"
#include "commands/intake/SetIntakeSpeed.h"
#include "commands/intake/SetConveyorSpeed.h"
#include "commands/drive/SetRobotPose.h"
#include "commands/drive/FollowPath.h"
#include <frc2/command/WaitUntilCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
TenPowerCellAuto::TenPowerCellAuto(SwerveSubsystem* swerveSub, IntakeSubsystem* intakeSub, ShooterSubsystem* shooterSub, bool redAlli) :
  m_swerveSubsystem(swerveSub), m_intakeSubsystem(intakeSub), m_shooterSubsystem(shooterSub), redAlliance(redAlli) {

  frc::Pose2d startPose;
  frc::Rotation2d startAngle;
  if(redAlli) {
    startPose = frc::Pose2d(0_ft, 43.2_ft, frc::Rotation2d(0_deg));
  }
  else {
    startPose = frc::Pose2d(0_ft, 43.2_ft, frc::Rotation2d(0_deg));
  }

  FollowPath m_followPathAuto{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    startPose, //start pt
    {frc::Translation2d(-2.5_ft, 36_ft)}, //middle pts
    frc::Pose2d(-2.5_ft, 31_ft, frc::Rotation2d(0_deg)), //end points and angle 
    m_swerveSubsystem //subsystem
  };

  AddCommands(
    SetRobotPose(m_swerveSubsystem, startPose, m_swerveSubsystem->m_swerve.GetAngle()),
    IntakeUp(m_intakeSubsystem),
    SetIntakeSpeed(m_intakeSubsystem, 1),
    SetConveyorSpeed(m_intakeSubsystem, 1),
    std::move(m_followPathAuto),
    frc2::WaitUntilCommand([this](){return m_intakeSubsystem->GetNumOfBalls() == 5;})
  );
}
