#include "commands/intake/SetConveyorSpeed.h"

SetConveyorSpeed::SetConveyorSpeed(IntakeSubsystem* intakeSub, double intakeSpeed) :
  m_intakeSubsystem(intakeSub) {
  speed = intakeSpeed;
  AddRequirements(m_intakeSubsystem);
}

void SetConveyorSpeed::Initialize() {
  m_intakeSubsystem->SetConveyorBeltSpeed(speed);
}
