#include "commands/shooter/SetHoodToAngle.h"

SetHoodToAngle::SetHoodToAngle(ShooterSubsystem* subsystem, std::function<units::degree_t()> angle) : m_subsystem(subsystem), angleToGoTo(angle) {
  SetName("SetHoodToAngle");
  AddRequirements({subsystem});
}

void SetHoodToAngle::Initialize() {
  m_subsystem->SetHoodToAngle(angleToGoTo());
}
