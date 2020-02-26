/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/drive/TurnToGoal.h"
#include "commands/drive/TurnToAngle.h"
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
TurnToGoal::TurnToGoal(std::function<double()> fow, std::function<double()> strafe, ShooterSubsystem* shooterSub, SwerveSubsystem* swerveSub, std::function<bool()> controllerOverride) : m_shooterSubsystem(shooterSub), m_swerveSubsystem(swerveSub) {
  AddCommands(
    TurnToAngle(    
      fow,
      strafe,
      [swerveSub, shooterSub]() { return swerveSub->GetImuYaw().to<double>() - shooterSub->GetAngleToTarget().to<double>(); },
      m_swerveSubsystem,
      controllerOverride
    )
  );
}
