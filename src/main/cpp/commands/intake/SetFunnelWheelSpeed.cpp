#include "commands/intake/SetFunnelWheelSpeed.h"

SetFunnelWheelSpeed::SetFunnelWheelSpeed(IntakeSubsystem* intakeSub, double funnelSpeed) :
    m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
  speed = funnelSpeed;
}

void SetFunnelWheelSpeed::Initialize() {
  m_intakeSubsystem->SetFunnelWheelOverrideSpeed(speed);
}
