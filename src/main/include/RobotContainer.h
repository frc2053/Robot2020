#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include "subsystems/SwerveSubsystem.h"
#include "subsystems/ControlPanelSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/ConveyorSubsystem.h"
#include "commands/drive/FollowPath.h"
#include <frc/smartdashboard/SendableChooser.h>
#include "subsystems/ClimberSubsystem.h"
#include "commands/auto/TenPowerCellAuto.h"
#include "commands/auto/ShootBallsAuto.h"
#include "commands/controlpanel/ManualWheelRotation.h"
#include "commands/controlpanel/PositionControl.h"
#include "commands/controlpanel/RotationControl.h"
#include "commands/conveyor/ConveyorDefault.h"
#include "commands/intake/IntakeDefault.h"

class RobotContainer {
 public:
  RobotContainer();
  frc2::Command* GetAutonomousCommand();
  SwerveSubsystem m_drivetrain;
  ControlPanelSubsystem m_controlpanel;
  ShooterSubsystem m_shooter;
  IntakeSubsystem m_intake;
  ClimberSubsystem m_climber;
  ConveyorSubsystem m_conveyor;

 private:

  frc::XboxController driverController{0};
  frc::XboxController operatorController{1};

  //KEEP IN MIND THAT PATH ANGLES ARE ONLY RESPECTED AT THE END OF THE PATH
  FollowPath m_followPathAuto{
    10_fps, //max speed
    units::meters_per_second_squared_t(3), //max accel
    frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)), //start pt
    {frc::Translation2d(.5_ft, 0_ft)}, //middle pts
    frc::Pose2d(1_ft, 0_ft, frc::Rotation2d(0_deg)), //end points and angle 
    &m_drivetrain //subsystem
  };

  TenPowerCellAuto m_tenCellAuto{&m_drivetrain, &m_intake, &m_shooter, &m_conveyor};
  ShootBallsAuto m_shootBallsAuto{&m_drivetrain, &m_intake, &m_shooter, &m_conveyor};

  PositionControl m_posControl{&m_controlpanel};
  RotationControl m_rotControl{&m_controlpanel};
  ManualWheelRotation m_wheelControl{&m_controlpanel, [this] { return operatorController.GetX(frc::GenericHID::JoystickHand::kLeftHand); } };

  frc::SendableChooser<frc2::Command*> m_chooser;
  frc::SendableChooser<frc2::Command*> m_controlChooser;

  //SetConveyorSpeed conveyorFullCmd{&m_conveyor, 0};
  ConveyorDefault conveyorDefualt{&m_conveyor};
  IntakeDefault intakeDefualt{&m_intake};

  void ConfigureButtonBindings();
};
