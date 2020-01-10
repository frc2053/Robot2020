#include "Robot.h"
#include "include/subsystems/SpinnerSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

SpinnerSubsystem::Spinner()
{
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
    color = null;
}

void Periodic()
{
    //check for color 
}

void RunSpinnerMotor()
{

}