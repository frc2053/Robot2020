//rotates the control panel 3 < x < 5 times

#include "commands/controlpanel/RotationControl.h"
#include "subsystems/ControlPanelSubsystem.h"

RotationControl::RotationControl(ControlPanelSubsystem* subsystem) 
: controlPanelSubsystem{subsystem} {
    SetName("RotationControl");
    AddRequirements({controlPanelSubsystem});
    isDone = false;
}

void RotationControl::Initialize() {
    previousColor = controlPanelSubsystem->ReturnColorSensed();
    colorSensed = previousColor;
    counter = 0;
    controlPanelSubsystem->SetControlPanelWheelSpeed(1);
}

//senses the current color and constantly checks for change
//after 24 changes of color have been detected, stops
//8 colors on the wheel x 3 rotations = 24 changes
void RotationControl::Execute() {
    colorSensed = controlPanelSubsystem->ReturnColorSensed();
    if(!(colorSensed == previousColor)){
        counter++;
        if(counter >= 24){ isDone = true; }
    }
    previousColor = colorSensed;
}

bool RotationControl::IsFinished() { return isDone; }

void RotationControl::End(bool) { controlPanelSubsystem->SetControlPanelWheelSpeed(0);}