#include "commands/conveyor/IndexingOff.h"

IndexingOff::IndexingOff(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
}

void IndexingOff::Initialize() {
  m_conveyorSubsystem->SetIndexingOff();
}
