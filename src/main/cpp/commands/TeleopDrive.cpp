/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TeleopDrive.h"

TeleopDrive::TeleopDrive(std::function<double()> fow, 
                         std::function<double()> strafe,
                         std::function<double()> rot, 
                         SwerveSubsystem* subsystem)
    : m_fow(fow), m_strafe(strafe), m_rot(rot), m_subsystem{subsystem} {
        SetName("TeleopDrive");
        AddRequirements({m_subsystem});
}

void TeleopDrive::Execute() { m_subsystem->DriveWithJoystick(m_strafe(), m_fow(), m_rot(), true); }

bool TeleopDrive::IsFinished() { return false; }

void TeleopDrive::End(bool) { m_subsystem->DriveWithJoystick(0,0,0,true); }