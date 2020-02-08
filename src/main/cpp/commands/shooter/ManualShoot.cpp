//runs the shooter and hood 

#include "commands/shooter/ManualShoot.h"
#include "Constants.h"

ManualShoot::ManualShoot(ShooterSubsystem* subsystem, std::function<double()> run, std::function<double()> adjust)
: shooterSubsystem{subsystem} , runIt(run), adjustIt(adjust){
    SetName("ManualShoot");
    AddRequirements({shooterSubsystem});
    isDone = false;
}

void ManualShoot::Execute() {
    shooterSubsystem->SetShooterToPercentOutput(runIt());
    shooterSubsystem->SetHoodToAngle(adjustIt());
}

bool ManualShoot::IsFinished() { return true; }

void ManualShoot::End(bool) {
    shooterSubsystem->SetShooterToPercentOutput(0);
    shooterSubsystem->SetHoodToAngle(0);
}

