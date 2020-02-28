#include "commands/intake/SetIntakeSpeed.h"

SetIntakeSpeed::SetIntakeSpeed(IntakeSubsystem* intakeSub, double intakeSpeed) :
  m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
  speed = intakeSpeed;
}

void SetIntakeSpeed::Initialize() {
  m_intakeSubsystem->SetIntakeWheelsSpeed(speed);
}
