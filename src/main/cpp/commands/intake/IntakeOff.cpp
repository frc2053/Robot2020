#include "commands/intake/IntakeOff.h"

IntakeOff::IntakeOff(IntakeSubsystem* intake) : intakeSub(intake) {
  AddRequirements(intakeSub);
}

void IntakeDown::Initialize() {
  intakeSub->SetIntakeOff();
}
