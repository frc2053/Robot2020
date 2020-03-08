#include "commands/drive/FollowPath.h"

#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/SwerveControllerCommand.h>
#include <frc2/command/InstantCommand.h>

FollowPath::FollowPath(units::meters_per_second_t maxSpeed, units::meters_per_second_squared_t maxAccel, const frc::Pose2d& startPt, const std::vector<frc::Translation2d>& middlePts, const frc::Pose2d& endPt, SwerveSubsystem* swerve) :
  m_maxSpeed(maxSpeed),
  m_maxAccel(maxAccel),
  m_startPt(startPt),
  m_middlePts(middlePts),
  m_endPt(endPt), 
  m_drivetrain(swerve) {
    // Set up config for trajectory
  frc::TrajectoryConfig config(m_maxSpeed,
                               m_maxAccel);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(m_drivetrain->m_swerve.m_kinematics);

  // An example trajectory to follow.  All units in meters.
  std::cout << "start point: X: " << m_startPt.Translation().X() << ", Y: " << m_startPt.Translation().Y() << ", Yaw: " << m_startPt.Rotation().Degrees() << "\n";

  for(frc::Translation2d middlePt : m_middlePts) {
      std::cout << "middle point: X: " << middlePt.X() << ", Y: " << middlePt.Y() << "\n";
  }

  std::cout << "end point: X: " << m_endPt.Translation().X() << ", Y: " << m_endPt.Translation().Y() << ", Yaw: " << m_endPt.Rotation().Degrees() << "\n";

  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      m_startPt,
      m_middlePts,
      m_endPt,
      config);

  frc2::SwerveControllerCommand<4> swerveControllerCommand(
      exampleTrajectory, [this]() { return m_drivetrain->GetCurrentPose(); },

      m_drivetrain->m_swerve.m_kinematics,

      frc2::PIDController(tigertronics::constants::pathFollowingkP, tigertronics::constants::pathFollowingkI, tigertronics::constants::pathFollowingkD),
      frc2::PIDController(tigertronics::constants::pathFollowingkP, tigertronics::constants::pathFollowingkI, tigertronics::constants::pathFollowingkD),
      frc::ProfiledPIDController<units::radians>(
          tigertronics::constants::swerveAnglekP, tigertronics::constants::swerveAnglekI, tigertronics::constants::swerveAnglekD,
          tigertronics::constants::kThetaControllerConstraints),

      [this](auto moduleStates) { m_drivetrain->m_swerve.SetModuleStates(moduleStates); },

      {m_drivetrain});

  AddCommands(
    std::move(swerveControllerCommand),
    frc2::InstantCommand(
    [this]() {
      m_drivetrain->AutoDrive(units::meters_per_second_t(0),
                    units::meters_per_second_t(0),
                    units::radians_per_second_t(0));
    },
    {})
  );
}
