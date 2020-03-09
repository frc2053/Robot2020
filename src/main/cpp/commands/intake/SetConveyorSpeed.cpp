#include "commands/intake/SetConveyorSpeed.h"

SetConveyorSpeed::SetConveyorSpeed(IntakeSubsystem* intakeSub, double conveyorSpeed) :
  m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
  speed = conveyorSpeed;
}

void SetConveyorSpeed::Initialize() {
  m_intakeSubsystem->SetConveyorBeltOverrideSpeed(speed);
}
