#include "commands/shooter/SetShooterToVelocity.h"

SetShooterToVelocity::SetShooterToVelocity(ShooterSubsystem* subsystem, std::function<units::revolutions_per_minute_t()> speed) : m_subsystem(subsystem), m_speed(speed) {
  SetName("SetShooterToVelocity");
  AddRequirements({subsystem});
}

void SetShooterToVelocity::Initialize() {
  m_subsystem->SetShooterToVelocity(m_speed());
}
