#include "commands/intake/IntakeOn.h"

IntakeOn::IntakeOn(IntakeSubsystem* intake) : intakeSub(intake) {
  AddRequirements(intakeSub);
}

void IntakeUp::Initialize() {
  intakeSub->SetIntakeOn();
}
