#include "commands/intake/SetLoaderWheelSpeed.h"

SetLoaderWheelSpeed::SetLoaderWheelSpeed(IntakeSubsystem* intakeSub, double intakeSpeed) :
    m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
  speed = intakeSpeed;
}

void SetLoaderWheelSpeed::Initialize() {
  m_intakeSubsystem->SetFeederWheelSpeed(speed);
}
