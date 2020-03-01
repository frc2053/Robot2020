#include "commands/shooter/SetShooterToGoal.h"
#include "tigertronics/ShooterLookupTable.h"
#include "commands/shooter/SetHoodToAngle.h"
#include "commands/shooter/SetShooterToVelocity.h"
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/PrintCommand.h>

SetShooterToGoal::SetShooterToGoal(ShooterSubsystem* shooterSub) : m_shooterSubsystem(shooterSub) {
  AddCommands(
    SetHoodToAngle(m_shooterSubsystem, [this](){return m_shooterSubsystem->GetAngleToGoTo();}),
    SetShooterToVelocity(m_shooterSubsystem, [this](){return  m_shooterSubsystem->GetRPMToGoTo();})
  );
}
