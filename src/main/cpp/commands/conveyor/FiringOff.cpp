#include "commands/conveyor/FiringOff.h"

FiringOff::FiringOff(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
}

void FiringOff::Initialize() {
  m_conveyorSubsystem->SetFiringOff();
}
