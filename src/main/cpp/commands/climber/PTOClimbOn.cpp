#include "commands/climber/PTOClimbOn.h"

PTOClimbOn::PTOClimbOn(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

void PTOClimbOn::Initialize() {
  m_climberSubsystem->SetPTO(frc::DoubleSolenoid::Value::kForward);
}
