#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/Joystick.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "commands/drive/WheelTest.h"
#include "commands/drive/TurnToAngle.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/SwerveControllerCommand.h>
#include <commands/shooter/SetHoodToAngle.h>

RobotContainer::RobotContainer() : m_drivetrain(){

  m_drivetrain.SetDefaultCommand(TeleopDrive(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kRightHand); },
    &m_drivetrain
  ));

  m_shooter.Enable();

  ConfigureButtonBindings();

  frc::SmartDashboard::PutNumber("Shooter Velocity", 0);
  frc::SmartDashboard::PutNumber("Shooter Angle", 0);
}

void RobotContainer::ConfigureButtonBindings() {
  frc::SmartDashboard::PutData("Wheel Test", new WheelTest(&m_drivetrain));

  frc::SmartDashboard::PutData("Set Wheel To RPM", new AutoShoot(&m_shooter, [this] { return units::revolutions_per_minute_t(frc::SmartDashboard::GetNumber("Shooter Velocity", 0)); }));
  frc::SmartDashboard::PutData("Set Hood To Angle", new SetHoodToAngle(&m_shooter, [this] { return units::degree_t(frc::SmartDashboard::GetNumber("Shooter Angle", 0)); }));

  frc2::JoystickButton rotateToZeroButton(&driverController, (int)frc::XboxController::Button::kY);
  rotateToZeroButton.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    0_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton rotateToGenerator112Button(&driverController, (int)frc::XboxController::Button::kX);
  rotateToGenerator112Button.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    112.5_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton rotateToGenerator67Button(&driverController, (int)frc::XboxController::Button::kB);
  rotateToGenerator67Button.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    -67.5_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton rotateTo180Button(&driverController, (int)frc::XboxController::Button::kA);
  rotateTo180Button.WhenPressed(TurnToAngle(
    [this] { return driverController.GetY(frc::GenericHID::JoystickHand::kLeftHand); },
    [this] { return driverController.GetX(frc::GenericHID::JoystickHand::kLeftHand); },
    180_deg,
    &m_drivetrain
  ));

  frc2::JoystickButton manualCPWheel(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  manualCPWheel.WhileHeld(ManualWheelRotation(&m_controlpanel, [this] { return operatorController.GetY(frc::GenericHID::JoystickHand::kRightHand);} ));

  frc2::JoystickButton rotControl(&operatorController, (int)frc::XboxController::Button::kBumperLeft);
  rotControl.WhileActiveOnce(RotationControl(&m_controlpanel));
  
  frc2::JoystickButton posControl(&operatorController, (int)frc::XboxController::Button::kB);
  posControl.WhileActiveOnce(PositionControl(&m_controlpanel));
    
  frc2::JoystickButton intakeButton(&operatorController, (int)frc::XboxController::Button::kA);
  intakeButton.WhileHeld(AutoIntake(&m_intake));

  frc2::JoystickButton feederButton(&operatorController, (int)frc::XboxController::Button::kB);
  feederButton.WhileHeld(AutoFeed(&m_intake));

  //frc2::JoystickButton autoShooter(&operatorController, (int)frc::XboxController::Button::kX);
  //autoShooter.WhenHeld(AutoShoot(&m_shooter));
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Set up config for trajectory
  frc::TrajectoryConfig config(10_fps,
                               units::meters_per_second_squared_t(3));
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(m_drivetrain.m_swerve.m_kinematics);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(8_ft, 0_ft)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(8_ft, 5_ft, frc::Rotation2d(0_deg)),
      // Pass the config
      config);

  frc2::SwerveControllerCommand<4> swerveControllerCommand(
      exampleTrajectory, [this]() { return m_drivetrain.GetCurrentPose(); },

      m_drivetrain.m_swerve.m_kinematics,

      frc2::PIDController(0.00158, 0, 0),
      frc2::PIDController(0.00158, 0, 0),
      frc::ProfiledPIDController<units::radians>(
          tigertronics::constants::swerveAnglekP, 0, tigertronics::constants::swerveAnglekD,
          tigertronics::constants::kThetaControllerConstraints),

      [this](auto moduleStates) { m_drivetrain.m_swerve.SetModuleStates(moduleStates); },

      {&m_drivetrain});

  // no auto
  return new frc2::SequentialCommandGroup(
      std::move(swerveControllerCommand), std::move(swerveControllerCommand),
      frc2::InstantCommand(
          [this]() {
            m_drivetrain.AutoDrive(units::meters_per_second_t(0),
                          units::meters_per_second_t(0),
                          units::radians_per_second_t(0));
          },
          {}));
}
