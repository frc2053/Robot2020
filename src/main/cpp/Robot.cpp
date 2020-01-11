/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/shuffleboard/Shuffleboard.h>

void Robot::RobotInit() {

    frc2::CommandScheduler::GetInstance().OnCommandInitialize(
    [](const frc2::Command& command) {
      frc::Shuffleboard::AddEventMarker(
        "Command Init", command.GetName(),
        frc::ShuffleboardEventImportance::kNormal
      );
    }
  );

  frc2::CommandScheduler::GetInstance().OnCommandExecute(
    [](const frc2::Command& command) {
      frc::Shuffleboard::AddEventMarker(
        "Command Execute", command.GetName(),
        frc::ShuffleboardEventImportance::kNormal
      );
    }
  );

  frc2::CommandScheduler::GetInstance().OnCommandFinish(
    [](const frc2::Command& command) {
      frc::Shuffleboard::AddEventMarker(
        "Command Finish", command.GetName(),
        frc::ShuffleboardEventImportance::kNormal
      );
    }
  );

  frc2::CommandScheduler::GetInstance().OnCommandInterrupt(
    [](const frc2::Command& command) {
      frc::Shuffleboard::AddEventMarker(
        "Command Interrupted", command.GetName(),
        frc::ShuffleboardEventImportance::kNormal
      );
    }
  );

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run();
  std::cout << "Scheduling " << m_container.GetCalibrateWheelsCommand()->IsScheduled() << "\n";
  std::cout << "Finished " << m_container.GetCalibrateWheelsCommand()->IsFinished() << "\n";
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_calibrateWheelsCommand = m_container.GetCalibrateWheelsCommand();
  m_autonomousCommand = m_container.GetAutonomousCommand();

<<<<<<< HEAD
=======
  frc2::WaitCommand waitForWheelCal = frc2::WaitCommand(.25_s);

  m_calibrateWheelsCommand->Schedule();
  waitForWheelCal.Schedule();

>>>>>>> optimization
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
