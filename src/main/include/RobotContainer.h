#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include "commands/drive/TeleopDrive.h"
#include "subsystems/SwerveSubsystem.h"
#include "subsystems/ControlPanelSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "commands/controlpanel/ManualWheelRotation.h"
#include "commands/controlpanel/RotationControl.h"
#include "commands/controlpanel/PositionControl.h"
#include "commands/shooter/ManualShoot.h"

class RobotContainer {
 public:
  RobotContainer();

  SwerveSubsystem m_drivetrain;
  ControlPanelSubsystem m_controlpanel;
  ShooterSubsystem m_shooter;

 private:

  frc::XboxController driverController{0};
  frc::XboxController operatorController{1};

  void ConfigureButtonBindings();
};
