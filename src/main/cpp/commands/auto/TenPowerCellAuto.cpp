/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/auto/TenPowerCellAuto.h"
#include "commands/intake/IntakeDown.h"
#include "commands/intake/IntakeUp.h"
#include "commands/intake/IntakeOn.h"
#include "commands/intake/IntakeOff.h"
#include "commands/conveyor/IndexingOn.h"
#include "commands/conveyor/IndexingOff.h"
#include "commands/conveyor/FiringOn.h"
#include "commands/conveyor/FiringOff.h"
#include "commands/drive/SetRobotPose.h"
#include "commands/drive/FollowPath.h"
#include <frc2/command/WaitUntilCommand.h>
#include "commands/shooter/SetShooterToVelocity.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/drive/TurnToGoal.h"
#include "commands/shooter/SetShooterToGoal.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
TenPowerCellAuto::TenPowerCellAuto(SwerveSubsystem* swerveSub, IntakeSubsystem* intakeSub, ShooterSubsystem* shooterSub, ConveyorSubsystem* conveyorSub) :
  m_swerveSubsystem(swerveSub), m_intakeSubsystem(intakeSub), m_shooterSubsystem(shooterSub), m_conveyorSubsystem(conveyorSub) {

  frc::Pose2d startPose;
  frc::Rotation2d startAngle;
  startPose = frc::Pose2d(0_ft, 43.2_ft, frc::Rotation2d(0_deg));


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
    // Sets where we are on the field
    SetRobotPose(m_swerveSubsystem, startPose, m_swerveSubsystem->m_swerve.GetAngle()),

    // Step 1: Get intake ready to succ balls.
    IntakeOn(m_intakeSubsystem),
    IntakeDown(m_intakeSubsystem),
    IndexingOn(m_conveyorSubsystem),

    // Step 2: Move near control panel and pick up balls.
    // Might have to add a drive backwards command here?
    std::move(toControlPanel),

    // Step 3: Close up intake and prepare shooter.
    IntakeUp(m_intakeSubsystem),
    SetShooterToVelocity(m_shooterSubsystem, [](){return 3000_rpm;}),
    SetHoodToAngle(m_shooterSubsystem, [](){return 45_deg;}),

    // Step 4: Move to first shooting location in front of generator.
    std::move(toGeneratorShoot),

    // Step 5: Turn to align with goal
    TurnToGoal([](){return 0;}, [](){return 0;}, m_shooterSubsystem, m_swerveSubsystem, [](){return false; }),

    // Step 6: Spin up shooter to appropriate rpm and hood angle
    SetShooterToGoal(m_shooterSubsystem),

    // Step 7: Start spraying (Skeet Skeet Skeet!!!)...
    FiringOn(m_conveyorSubsystem),

    // Step 8: Give time to shoot all balls.
    frc2::WaitCommand(5_s),

    // Step 9: Stop shooting. Put intake down for next 5 balls.
    // Spin down shooter to save a bit of power
    FiringOff(m_conveyorSubsystem),
    IntakeDown(m_intakeSubsystem),
    SetShooterToVelocity(m_shooterSubsystem, [](){return 3000_rpm;}),
    SetHoodToAngle(m_shooterSubsystem, [](){return 45_deg;}),

    // Step 10: Go to side of generator, grab two balls.
    std::move(toGeneratorBall),

    // Step 11: Go to our trench, grab 3 more balls.
    std::move(toTrench),

    //Step 12: Close up intake.
    IntakeUp(m_intakeSubsystem),

    // Step 13: Move to front of goal for more accurate shot.
    std::move(toFinalShot),

    // Step 14: Turn to align with goal.
    TurnToGoal([](){return 0;}, [](){return 0;}, m_shooterSubsystem, m_swerveSubsystem, [](){return false; }),

    // Step 15: Spin up shooter to appropriate rpm and hood angle.
    SetShooterToGoal(m_shooterSubsystem),
    
    // Step 16: Skeet Skeet Skeet!!!
    FiringOn(m_conveyorSubsystem),

    // Step 17: Give shooter time to fire all balls.
    frc2::WaitCommand(5_s),

    // Step 18: Done.
    FiringOff(m_conveyorSubsystem),
    IndexingOff(m_conveyorSubsystem)
  );
}
