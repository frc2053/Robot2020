#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include "subsystems/SwerveSubsystem.h"
#include "subsystems/ControlPanelSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"
#include "commands/drive/TeleopDrive.h"
#include "commands/controlpanel/ManualWheelRotation.h"
#include "commands/controlpanel/RotationControl.h"
#include "commands/controlpanel/PositionControl.h"
#include "commands/shooter/AutoShoot.h"
#include "commands/intake/AutoFeed.h"
#include "commands/intake/AutoIntake.h"

class RobotContainer {
 public:
  RobotContainer();
  frc2::Command* GetAutonomousCommand();
  SwerveSubsystem m_drivetrain;
  ControlPanelSubsystem m_controlpanel;
  ShooterSubsystem m_shooter;
  IntakeSubsystem m_intake;

 private:

  frc::XboxController driverController{0};
  frc::XboxController operatorController{1};

  void ConfigureButtonBindings();
};
