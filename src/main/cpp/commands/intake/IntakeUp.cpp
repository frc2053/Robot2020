#include "commands/intake/IntakeUp.h"

IntakeUp::IntakeUp(IntakeSubsystem* intake) : intakeSub(intake) {
  AddRequirements(intakeSub);
}

void IntakeUp::Initialize() {
  intakeSub->SetIntakeUp();
}
