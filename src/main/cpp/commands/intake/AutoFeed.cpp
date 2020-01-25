//feeds stored balls into shooter, unfinished

#include "commands/intake/AutoFeed.h"

AutoFeed::AutoFeed(IntakeSubsystem* subsystem)
 : intakeSubsystem{subsystem} {
     SetName("AutoFeed");
     AddRequirements({intakeSubsystem});
}

void AutoFeed::Execute() {
    //motor speeds are random values
    intakeSubsystem->SetFeederWheelSpeed(.5);
}

bool AutoFeed::IsFinished() { return true; }

void AutoFeed::End(bool) {
    intakeSubsystem->SetFeederWheelSpeed(0);
}