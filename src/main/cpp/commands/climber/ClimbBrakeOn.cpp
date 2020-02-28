#include "commands/climber/ClimbBrakeOn.h"

ClimbBrakeOn::ClimbBrakeOn(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

void ClimbBrakeOn::Initialize() {
  m_climberSubsystem->SetBrake(frc::DoubleSolenoid::Value::kForward);
}
