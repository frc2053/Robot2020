//runs the control panel manipulation motor 

#include "commands/controlpanel/ManualWheelRotation.h"
#include <frc/shuffleboard/Shuffleboard.h>

ManualWheelRotation::ManualWheelRotation(ControlPanelSubsystem* subsystem, std::function<double()> run) 
: controlPanelSubsystem{subsystem} , runIt(run){
    SetName("ManualWheelRotation");
    AddRequirements({controlPanelSubsystem});
    isDone = false;
}

void ManualWheelRotation::Execute() { 
    controlPanelSubsystem->SetControlPanelWheelSpeed(runIt()); 
}

bool ManualWheelRotation::IsFinished() { return false; }

void ManualWheelRotation::End(bool) { }