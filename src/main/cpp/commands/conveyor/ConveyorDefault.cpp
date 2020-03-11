#include "commands/conveyor/ConveyorDefault.h"

IndexingOn::IndexingOn(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
}

void IndexingOn::Initialize() {
  m_conveyorSubsystem->SetIndexingOff();
  m_conveyorSubsystem->SetFiringOff();
}
