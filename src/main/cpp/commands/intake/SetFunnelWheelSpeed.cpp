#include "commands/intake/SetFunnelWheelSpeed.h"

SetFunnelWheelSpeed::SetFunnelWheelSpeed(IntakeSubsystem* intakeSub, double intakeSpeed) :
    m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
  speed = intakeSpeed;
}

void SetFunnelWheelSpeed::Initialize() {
  m_intakeSubsystem->SetFunnelWheelSpeed(speed);
}
