#include "commands/intake/SetLoaderWheelSpeed.h"

SetLoaderWheelSpeed::SetLoaderWheelSpeed(IntakeSubsystem* intakeSub, double loaderSpeed) :
    m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
  speed = loaderSpeed;
}

void SetLoaderWheelSpeed::Initialize() {
  m_intakeSubsystem->SetFeederWheelOverrideSpeed(speed);
}
