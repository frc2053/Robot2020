//rotates control panel to target color

#include "commands/controlpanel/PositionControl.h"
#include "subsystems/ControlPanelSubsystem.h"

PositionControl::PositionControl(ControlPanelSubsystem* subsystem) 
: controlPanelSubsystem{subsystem} {
    SetName("PositionControl");
    AddRequirements({controlPanelSubsystem});
    isDone = false;
}

void PositionControl::Initialize() {
    colorGoal = controlPanelSubsystem->GetColor();
    currentColor = controlPanelSubsystem->ReturnColorSensed();
}

//starts rotating the control panel and senses the color
//stops rotating when target color is reached
void PositionControl::Execute() {
    controlPanelSubsystem->SetControlPanelWheelSpeed(.5);
    if(currentColor == colorGoal)
    { isDone = true; }
    currentColor = controlPanelSubsystem->ReturnColorSensed();
}

void PositionControl::End(bool) {
    controlPanelSubsystem->SetControlPanelWheelSpeed(0);
}

bool PositionControl::IsFinished() {
    return isDone;
}