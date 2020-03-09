#include "commands/intake/ConveyorOn.h"

ConveyorOn::ConveyorOn(IntakeSubsystem* intakeSub) :
  m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
}

void ConveyorOn::Initialize() {
  m_intakeSubsystem->SetIndexing(true);
}
