/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/shooter/SetShooterToGoal.h"
#include "tigertronics/ShooterLookupTable.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/shooter/SetShooterToVelocity.h"
#include <frc2/command/WaitUntilCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
SetShooterToGoal::SetShooterToGoal(ShooterSubsystem* shooterSub) : m_shooterSubsystem(shooterSub) {
  ShooterLookupTable::LookupValue angleAndRpm = m_shooterSubsystem->GetAngleAndRPMForGoal(m_shooterSubsystem->GetDistanceToTarget());
  AddCommands(
    SetHoodToAngle(m_shooterSubsystem, [angleAndRpm](){return angleAndRpm.angle;}),
    SetShooterToVelocity(m_shooterSubsystem, [angleAndRpm](){return angleAndRpm.rpm;}),
    frc2::WaitUntilCommand([this, angleAndRpm](){return m_shooterSubsystem->GetShooterAvgRPM() >= angleAndRpm.rpm;})
  );
}
