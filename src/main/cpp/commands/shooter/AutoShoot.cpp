//shoots balls, *very* unfinished

#include "commands/shooter/AutoShoot.h"

AutoShoot::AutoShoot(ShooterSubsystem* subsystem) 
: shooterSubsystem{subsystem} {
    SetName("AutoShoot");
    AddRequirements({shooterSubsystem});
}

void AutoShoot::Execute() {
    //shooter value set to an arbitrary value
    shooterSubsystem->SetShooterToPercentOutput(.75);
    //still needs control of hood (if necessary)
    //and running the belt to feed balls
}

bool AutoShoot::IsFinished() { return true; }

void AutoShoot::End(bool) {
    shooterSubsystem->SetShooterToPercentOutput(0);
    //still needs to set the belt to speed(0)
}