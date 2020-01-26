#include "commands/ChangeJetsonIP.h"

ChangeJetsonIP::ChangeJetsonIP(std::function<std::string()> newIp, SwerveSubsystem* subsystem)
  : m_newIp(newIp), m_subsystem(subsystem) {
  SetName("Jetson IP Change");
  AddRequirements({m_subsystem});
}

void ChangeJetsonIP::Initialize() {
  std::cout << "Changing jetson IP to " << m_newIp() << "\n";
  m_subsystem->ChangeRosConnection(m_newIp());
}
