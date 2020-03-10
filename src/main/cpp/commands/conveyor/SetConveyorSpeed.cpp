#include "commands/conveyor/SetConveyorSpeed.h"

SetConveyorSpeed::SetConveyorSpeed(ConveyorSubsystem* conveyorSub, double intakeSpeed) :
  m_conveyorSubsystem(conveyorSub) {
  speed = intakeSpeed;
  AddRequirements(m_conveyorSubsystem);
}

void SetConveyorSpeed::Initialize() {
  m_conveyorSubsystem->SetConveyorBeltSpeed(speed);
}
