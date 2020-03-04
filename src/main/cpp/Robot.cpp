#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/shuffleboard/Shuffleboard.h>

void Robot::RobotInit() {}

void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

void Robot::DisabledInit() {
  m_container.m_shooter.SetServoSpeed(0);
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

void Robot::TeleopPeriodic() {
  frc::SmartDashboard::PutNumber("vision yaw", m_container.m_shooter.GetAngleToTarget().to<double>());
  frc::SmartDashboard::PutNumber("vision error", m_container.m_drivetrain.GetImuYaw().to<double>() - m_container.m_shooter.GetAngleToTarget().to<double>());
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
