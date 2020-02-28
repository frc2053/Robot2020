#include "commands/shooter/SetShooterToGoal.h"
#include "tigertronics/ShooterLookupTable.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/shooter/SetShooterToVelocity.h"
#include <frc2/command/WaitUntilCommand.h>

SetShooterToGoal::SetShooterToGoal(ShooterSubsystem* shooterSub) : m_shooterSubsystem(shooterSub) {
  ShooterLookupTable::LookupValue angleAndRpm = m_shooterSubsystem->GetAngleAndRPMForGoal(m_shooterSubsystem->GetDistanceToTarget());
  AddCommands(
    SetHoodToAngle(m_shooterSubsystem, [angleAndRpm](){return angleAndRpm.angle;}),
    SetShooterToVelocity(m_shooterSubsystem, [angleAndRpm](){return angleAndRpm.rpm;}),
    frc2::WaitUntilCommand([this, angleAndRpm](){return m_shooterSubsystem->GetShooterAvgRPM() >= angleAndRpm.rpm;})
  );
}
