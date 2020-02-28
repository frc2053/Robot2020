#include "commands/climber/ClimbElevatorUp.h"

ClimbElevatorUp::ClimbElevatorUp(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

void ClimbElevatorUp::Initialize() {
  m_climberSubsystem->SetElevator(frc::DoubleSolenoid::Value::kForward);
}
