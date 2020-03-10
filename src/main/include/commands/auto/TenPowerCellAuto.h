#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/SwerveSubsystem.h"
#include "subsystems/ConveyorSubsystem.h"

class TenPowerCellAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TenPowerCellAuto> {
 public:
  TenPowerCellAuto(SwerveSubsystem* swerveSub, IntakeSubsystem* intakeSub, ShooterSubsystem* shooterSub, ConveyorSubsystem* conveyorSub);
 private:
  SwerveSubsystem* m_swerveSubsystem;
  IntakeSubsystem* m_intakeSubsystem;
  ShooterSubsystem* m_shooterSubsystem;
  ConveyorSubsystem* m_conveyorSubsystem;
};
