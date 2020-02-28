#include "commands/climber/ResetClimber.h"
#include "commands/climber/PTOClimbOff.h"
#include "commands/climber/ClimbBrakeOff.h"
#include "commands/climber/ClimbElevatorDown.h"
#include "commands/shooter/SetShooterToVelocity.h"

ResetClimber::ResetClimber(ShooterSubsystem* shooterSub, ClimberSubsystem* climberSub) : m_shooterSubsystem(shooterSub), m_climberSubsystem(climberSub) {
  AddCommands(
    SetShooterToVelocity(m_shooterSubsystem, [](){return 0_rpm;}),
    PTOClimbOff(m_climberSubsystem),
    ClimbBrakeOff(m_climberSubsystem),
    ClimbElevatorDown(m_climberSubsystem)
  );
}
