#include "commands/climber/ClimbElevatorDown.h"

ClimbElevatorDown::ClimbElevatorDown(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

void ClimbElevatorDown::Initialize() {
  m_climberSubsystem->SetElevator(frc::DoubleSolenoid::Value::kReverse);
}
