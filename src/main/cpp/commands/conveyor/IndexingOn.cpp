#include "commands/conveyor/IndexingOn.h"

IndexingOn::IndexingOn(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
}

void IndexingOn::Initialize() {
  m_conveyorSubsystem->SetIndexingOn();
}
