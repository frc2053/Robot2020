#include "commands/conveyor/SetNumOfBalls.h"

SetNumOfBalls::SetNumOfBalls(ConveyorSubsystem* conveyorSub, int balls) :
  m_conveyorSubsystem(conveyorSub), numOfBalls(balls) {
  AddRequirements(m_conveyorSubsystem);
}

void SetNumOfBalls::Initialize() {
  m_conveyorSubsystem->SetNumOfBalls(numOfBalls);
}
