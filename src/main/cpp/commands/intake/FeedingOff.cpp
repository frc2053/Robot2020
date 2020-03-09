#include "commands/intake/FeedingOff.h"

FeedingOff::FeedingOff(IntakeSubsystem* intakeSub) :
  m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
}

void FeedingOff::Initialize() {
  m_intakeSubsystem->SetFiring(false);
}
