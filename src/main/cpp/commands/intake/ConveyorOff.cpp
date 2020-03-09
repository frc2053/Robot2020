#include "commands/intake/ConveyorOff.h"

ConveyorOff::ConveyorOff(IntakeSubsystem* intakeSub) :
  m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
}

void ConveyorOff::Initialize() {
  m_intakeSubsystem->SetIndexing(false);
}
