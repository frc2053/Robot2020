#include "commands/intake/SetConveyorIndexer.h"

SetConveyorIndexer::SetConveyorIndexer(IntakeSubsystem* intakeSub, double intakeSpeed, bool indexerActive) :
  m_intakeSubsystem(intakeSub) {
  speed = intakeSpeed;
  active = indexerActive
  AddRequirements(m_intakeSubsystem);
}

void SetConveyorIndexer::Initialize() {
  m_intakeSubsystem->SetConveyorBeltSpeed(speed);
  m_intakeSubsystem->SetIndexerActive(active);
}
