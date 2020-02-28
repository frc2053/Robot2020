#include "commands/climber/PTOClimbOff.h"

PTOClimbOff::PTOClimbOff(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

void PTOClimbOff::Initialize() {
  m_climberSubsystem->SetPTO(frc::DoubleSolenoid::Value::kReverse);
}
