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
//finishes when target color is reached
void PositionControl::Execute() {
    /*
    controlPanelSubsystem->SetControlPanelWheelSpeed(.1);
    if(currentColor == colorGoal)
    { isDone = true; }
    currentColor = controlPanelSubsystem->ReturnColorSensed();
    */
   while(!(colorGoal == currentColor)){
       std::cout << "inside while loop\n";
       controlPanelSubsystem->SetControlPanelWheelSpeed(.1);
       std::cout << "wheel is on in the code\n";
       currentColor = controlPanelSubsystem->ReturnColorSensed();
       std::cout << "color has been sensed:\n";

   }
   isDone = true;
}


void PositionControl::End(bool) {
    controlPanelSubsystem->SetControlPanelWheelSpeed(0);
}

bool PositionControl::IsFinished() {
    return isDone;
}