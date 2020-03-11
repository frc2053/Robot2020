#include "commands/intake/IntakeDefault.h"

IntakeDefault::IntakeDefault(IntakeSubsystem* intake) : intakeSub(intake) {
  AddRequirements(intakeSub);
}

void IntakeUp::Initialize() {
  intakeSub->SetIntakeOff();
}
