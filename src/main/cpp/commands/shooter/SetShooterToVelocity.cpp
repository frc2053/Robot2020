#include "commands/shooter/SetShooterToVelocity.h"

SetShooterToVelocity::SetShooterToVelocity(ShooterSubsystem* subsystem, std::function<units::revolutions_per_minute_t()> angle) : m_subsystem(subsystem), speed(angle) {
  SetName("SetShooterToVelocity");
  AddRequirements({subsystem});
}

void SetShooterToVelocity::Initialize() {
  m_subsystem->SetShooterToVelocity(speed());
}
