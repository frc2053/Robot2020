#include "commands/drive/TurnToGoal.h"
#include "commands/drive/TurnToAngle.h"

TurnToGoal::TurnToGoal(std::function<double()> fow, std::function<double()> strafe, ShooterSubsystem* shooterSub, SwerveSubsystem* swerveSub, std::function<bool()> controllerOverride) : m_shooterSubsystem(shooterSub), m_swerveSubsystem(swerveSub) {
  AddCommands(
    TurnToAngle(    
      fow,
      strafe,
      [swerveSub, shooterSub]() { return -shooterSub->GetAngleToTarget().to<double>(); },
      m_swerveSubsystem,
      controllerOverride
    )
  );
}
