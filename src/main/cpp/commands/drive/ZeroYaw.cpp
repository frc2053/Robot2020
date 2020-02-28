#include "commands/drive/ZeroYaw.h"

ZeroYaw::ZeroYaw(SwerveSubsystem* swerveSub) : m_subsystem(swerveSub) {
  // Use addRequirements() here to declare subsystem dependencies.
}

void ZeroYaw::Initialize() {
  m_subsystem->ZeroYaw();
}
