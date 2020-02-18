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
#include "commands/shooter/SetShooterToVelocity.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/drive/TurnToGoal.h"
#include "commands/shooter/SetShooterToGoal.h"
#include "commands/intake/SetLoaderWheelSpeed.h"
#include "commands/intake/SetNumOfBalls.h"

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

  FollowPath toControlPanel{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    startPose, //start pt
    {frc::Translation2d(-2.5_ft, 36_ft)}, //middle pts
    frc::Pose2d(-2.5_ft, 31_ft, frc::Rotation2d(0_deg)), //end points and angle 
    m_swerveSubsystem //subsystem
  };

  FollowPath toGeneratorShoot{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    frc::Pose2d(-2.5_ft, 31_ft, frc::Rotation2d(0_deg)), //start pt
    {}, //middle pts
    frc::Pose2d(-20.2_ft, 37_ft, frc::Rotation2d(0_deg)), //end points and angle 
    m_swerveSubsystem //subsystem
  };

  FollowPath toGeneratorBall{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    frc::Pose2d(-20.2_ft, 31_ft, frc::Rotation2d(0_deg)), //start pt
    {frc::Translation2d(-20_ft, 34_ft)}, //middle pts
    frc::Pose2d(-17.5_ft, 32.3_ft, frc::Rotation2d(-45_deg)), //end points and angle 
    m_swerveSubsystem //subsystem
  };

  FollowPath toTrench{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    frc::Pose2d(-17.5_ft, 32.3_ft, frc::Rotation2d(-45_deg)), //start pt
    {frc::Translation2d(-24.6_ft, 34_ft)}, //middle pts
    frc::Pose2d(-24.6_ft, 26.5_ft, frc::Rotation2d(0_deg)), //end points and angle 
    m_swerveSubsystem //subsystem
  };

  FollowPath toFinalShot{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    frc::Pose2d(-24.6_ft, 26.5_ft, frc::Rotation2d(0_deg)), //start pt
    {}, //middle pts
    frc::Pose2d(-19_ft, 38_ft, frc::Rotation2d(0_deg)), //end points and angle 
    m_swerveSubsystem //subsystem
  };

  AddCommands(
    //sets where we are on the field
    SetRobotPose(m_swerveSubsystem, startPose, m_swerveSubsystem->m_swerve.GetAngle()),
    //sets initial number of balls
    SetNumOfBalls(m_intakeSubsystem, 3),
    //gets intake ready to succ balls
    IntakeDown(m_intakeSubsystem),
    SetIntakeSpeed(m_intakeSubsystem, 1),
    SetConveyorSpeed(m_intakeSubsystem, 1),
    //path to balls near control panel
    std::move(toControlPanel),
    //Might have to add a drive backwards command here?
    //Wait until we have 5 balls
    frc2::WaitUntilCommand([this](){return m_intakeSubsystem->GetNumOfBalls() == 5;}),
    //Close up intake
    IntakeUp(m_intakeSubsystem),
    SetIntakeSpeed(m_intakeSubsystem, 0),
    SetConveyorSpeed(m_intakeSubsystem, 0),
    //Premptive spin up of shooter
    SetShooterToVelocity(m_shooterSubsystem, [](){return 3000_rpm;}),
    SetHoodToAngle(m_shooterSubsystem, [](){return 45_deg;}),
    //path to in front of generator
    std::move(toGeneratorShoot),
    //turn to align with goal
    TurnToGoal([](){return 0;}, [](){return 0;}, m_shooterSubsystem, m_swerveSubsystem),
    //spins up shooter to appropriate rpm and hood angle
    SetShooterToGoal(m_shooterSubsystem),
    //start spraying
    SetLoaderWheelSpeed(m_intakeSubsystem, 1),
    SetConveyorSpeed(m_intakeSubsystem, 1),
    //stop when we dont have any more balls
    frc2::WaitUntilCommand([this](){return m_intakeSubsystem->GetNumOfBalls() == 0;}),
    //put intake down for next 5 balls
    IntakeDown(m_intakeSubsystem),
    SetIntakeSpeed(m_intakeSubsystem, 1),
    SetConveyorSpeed(m_intakeSubsystem, 1),
    //Spins down shooter to save a bit of power
    SetShooterToVelocity(m_shooterSubsystem, [](){return 3000_rpm;}),
    SetHoodToAngle(m_shooterSubsystem, [](){return 45_deg;}),
    //go to side of generator
    std::move(toGeneratorBall),
    //grab two ball
    frc2::WaitUntilCommand([this](){return m_intakeSubsystem->GetNumOfBalls() == 2;}),
    //go to our trench
    std::move(toTrench),
    //grab 3 more balls
    frc2::WaitUntilCommand([this](){return m_intakeSubsystem->GetNumOfBalls() == 5;}),
    //Close up intake
    IntakeUp(m_intakeSubsystem),
    SetIntakeSpeed(m_intakeSubsystem, 0),
    SetConveyorSpeed(m_intakeSubsystem, 0),
    //move to front of goal for more accurate shot
    std::move(toFinalShot),
    //turn to align with goal
    TurnToGoal([](){return 0;}, [](){return 0;}, m_shooterSubsystem, m_swerveSubsystem),
    //spins up shooter to appropriate rpm and hood angle
    SetShooterToGoal(m_shooterSubsystem),
    //start spraying
    SetLoaderWheelSpeed(m_intakeSubsystem, 1),
    SetConveyorSpeed(m_intakeSubsystem, 1),
    //Done
    frc2::WaitUntilCommand([this](){return m_intakeSubsystem->GetNumOfBalls() == 5;})
  );
}
