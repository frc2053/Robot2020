//runs the control panel manipulation motor 

#include "commands/controlpanel/ManualWheelRotation.h"

ManualWheelRotation::ManualWheelRotation(ControlPanelSubsystem* subsystem, std::function<double()> run) 
: controlPanelSubsystem{subsystem} , runIt(run){
    SetName("ManualWheelRotation");
    AddRequirements({controlPanelSubsystem});
    isDone = false;
}

void ManualWheelRotation::Execute() { controlPanelSubsystem->SetControlPanelWheelSpeed(runIt()); }

bool ManualWheelRotation::IsFinished() { return true; }

void ManualWheelRotation::End(bool) { controlPanelSubsystem->SetControlPanelWheelSpeed(0); }