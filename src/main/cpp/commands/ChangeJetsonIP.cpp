/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ChangeJetsonIP.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
ChangeJetsonIP::ChangeJetsonIP(std::function<std::string()> newIp, SwerveSubsystem* subsystem)
  : m_newIp(newIp), m_subsystem(subsystem) {
  SetName("Jetson IP Change");
  AddRequirements({m_subsystem});
}

// Called when the command is initially scheduled.
void ChangeJetsonIP::Initialize() {
  std::cout << "Changing jetson IP to " << m_newIp() << "\n";
  m_subsystem->ChangeRosConnection(m_newIp());
}
