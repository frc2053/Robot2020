#include "commands/controlpanel/ManualWheelRotation.h"

ManualWheelRotation::ManualWheelRotation(ControlPanelSubsystem* subsystem, std::function<double()> run) 
: controlPanelSubsystem{subsystem} , runIt(run){
    SetName("ManualWheelRotation");
    AddRequirements({controlPanelSubsystem});
    isDone = false;
}

void ManualWheelRotation::Execute() {
    controlPanelSubsystem->SetControlPanelWheelSpeed(runIt());
    isDone = true;
}

void ManualWheelRotation::End(bool interrupted) {
    controlPanelSubsystem->SetControlPanelWheelSpeed(0);
}

bool ManualWheelRotation::IsFinished() { return isDone; }