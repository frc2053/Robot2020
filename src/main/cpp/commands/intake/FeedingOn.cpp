#include "commands/intake/FeedingOn.h"

FeedingOn::FeedingOn(IntakeSubsystem* intakeSub) :
  m_intakeSubsystem(intakeSub) {
  AddRequirements(m_intakeSubsystem);
}

void FeedingOn::Initialize() {
  m_intakeSubsystem->SetFiring(true);
}
