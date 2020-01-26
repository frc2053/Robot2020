//intakes balls, unfinished

#include "commands/intake/AutoIntake.h"

AutoIntake::AutoIntake(IntakeSubsystem* subsystem)
 : intakeSubsystem{subsystem} {
     SetName("AutoIntake");
     AddRequirements({intakeSubsystem});
}

void AutoIntake::Execute() {
    //motor speeds are random values
    intakeSubsystem->SetConveyorBeltSpeed(.25);
    intakeSubsystem->SetIntakeWheelsSpeed(.75);
}

bool AutoIntake::IsFinished() { return true; }

void AutoIntake::End(bool) {
    intakeSubsystem->SetIntakeWheelsSpeed(0);
    intakeSubsystem->SetConveyorBeltSpeed(0);
}