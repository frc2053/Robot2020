#include "commands/intake/SetNumOfBalls.h"

SetNumOfBalls::SetNumOfBalls(IntakeSubsystem* intakeSub, int balls) :
  m_intakeSubsystem(intakeSub), numOfBalls(balls) {
  AddRequirements(m_intakeSubsystem);
}

void SetNumOfBalls::Initialize() {
  m_intakeSubsystem->SetNumOfBalls(numOfBalls);
}
