#include "commands/climber/ClimbBrakeOff.h"

ClimbBrakeOff::ClimbBrakeOff(ClimberSubsystem* climbSub) : m_climberSubsystem(climbSub) {
  AddRequirements(m_climberSubsystem);
}

void ClimbBrakeOff::Initialize() {
  m_climberSubsystem->SetBrake(frc::DoubleSolenoid::Value::kReverse);
}
