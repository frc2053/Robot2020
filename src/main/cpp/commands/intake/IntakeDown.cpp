#include "commands/intake/IntakeDown.h"

IntakeDown::IntakeDown(IntakeSubsystem* intake) : intakeSub(intake) {
  AddRequirements(intakeSub);
}

void IntakeDown::Initialize() {
  intakeSub->SetIntakeFow();
}
