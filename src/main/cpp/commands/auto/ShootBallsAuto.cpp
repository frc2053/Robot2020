/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/auto/ShootBallsAuto.h"
#include "commands/intake/IntakeDown.h"
#include "commands/intake/IntakeUp.h"
#include "commands/conveyor/FiringOff.h"
#include "commands/conveyor/FiringOn.h"
#include "commands/drive/SetRobotPose.h"
#include <frc2/command/WaitUntilCommand.h>
#include "commands/shooter/SetShooterToVelocity.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/drive/TurnToGoal.h"
#include "commands/shooter/SetShooterToGoal.h"
#include "commands/conveyor/SetNumOfBalls.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/WaitCommand.h>
#include "commands/intake/SetFunnelWheelSpeed.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
ShootBallsAuto::ShootBallsAuto(SwerveSubsystem* swerveSub, IntakeSubsystem* intakeSub, ShooterSubsystem* shooterSub, ConveyorSubsystem* conveyorSub) :
  m_swerveSubsystem(swerveSub), m_intakeSubsystem(intakeSub), m_shooterSubsystem(shooterSub), m_conveyorSubsystem(conveyorSub) {
  AddCommands(
    SetRobotPose(m_swerveSubsystem, startPose, m_swerveSubsystem->m_swerve.GetAngle()),
    frc2::InstantCommand(
      [this]() {
          m_shooterSubsystem->moveRequested = true;
      }
    ),
    // Step 1: Prepare shooter and hood.
    SetShooterToVelocity(m_shooterSubsystem, [](){return 3000_rpm;}),
    SetHoodToAngle(m_shooterSubsystem, [](){return 45_deg;}),

    // Step 2: Aim for target using auto-aim.
    TurnToGoal([](){return 0;}, [](){return 0;}, m_shooterSubsystem, m_swerveSubsystem, [](){ return false; }).WithTimeout(2_s),
    SetHoodToAngle(m_shooterSubsystem, [this](){return m_shooterSubsystem->GetAngleToGoTo();}),
    SetShooterToVelocity(m_shooterSubsystem, [this](){return m_shooterSubsystem->GetRPMToGoTo();}),

    // Step 3: Wait for shooter to get to correct speed.
    frc2::WaitUntilCommand([this](){return m_shooterSubsystem->GetShooterAvgRPM() >= m_shooterSubsystem->GetRPMToGoTo();}).WithTimeout(2_s),

    // Step 4: Start firing. Give some time to shoot all balls.
    FiringOn(m_conveyorSubsystem),
    frc2::WaitCommand(5_s),

    // Step 5: Stop shooter.
    FiringOff(m_conveyorSubsystem),
    SetHoodToAngle(m_shooterSubsystem, [this](){return 0_deg;}),
    SetShooterToVelocity(m_shooterSubsystem, [this](){return 0_rpm;}),

    // Step 6: Move past line.
    frc2::InstantCommand(
      [this]() {
          m_shooterSubsystem->moveRequested = false;
      }
    ),
    std::move(movePastInitLine)
  );
}
