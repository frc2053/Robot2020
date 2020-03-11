#include "commands/conveyor/FiringOn.h"

FiringOn::FiringOn(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
}

void FiringOn::Initialize() {
  m_conveyorSubsystem->SetFiringOn();
}
