/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "frc_new/geometry/Pose2d.h"
#include "frc_new/geometry/Translation2d.h"
#include "frc_new/geometry/Rotation2d.h"
#include "frc_new/trajectory/TrajectoryGenerator.h"
#include "frc_new/trajectory/Trajectory.h"

std::unique_ptr<OI> Robot::oi;
std::unique_ptr<SwerveSubsystem> Robot::swerveSubsystem;
std::unique_ptr<RosBridge> Robot::rosBridgeSubsystem;

void Robot::RobotInit() {
    driveChooser.SetDefaultOption("DriveJoystick", new DriveCommand());
    driveChooser.AddOption("DriveROS", new DriveWithROS());
	SmartDashboard::PutData("DriveMode", &driveChooser);

    swerveSubsystem = std::make_unique<SwerveSubsystem>();
    rosBridgeSubsystem = std::make_unique<RosBridge>();
    oi = std::make_unique<OI>();
    
    /*std::vector<frc_new::Pose2d> waypoints;
    waypoints.push_back(frc_new::Pose2d(frc_new::Translation2d(0_m, 0_m), frc_new::Rotation2d(0_rad)));
    waypoints.push_back(frc_new::Pose2d(frc_new::Translation2d(10_m, 0_m), frc_new::Rotation2d(0_rad)));

    std::vector<std::unique_ptr<frc_new::TrajectoryConstraint>> constraints;

    frc_new::Trajectory traj = frc_new::TrajectoryGenerator::GenerateTrajectory(waypoints, std::move(constraints), 0_mps, 0_mps, 10_mps, 100_mps_sq, false);

    units::second_t time = 0_s;
    units::second_t dt = 20_ms;
    units::second_t duration = traj.TotalTime();

    while(time < duration) {
    const frc_new::Trajectory::State point = traj.Sample(time);
    time = time + dt;
    std::cout << "Pose at time " << time << " : (" << point.pose.Translation().X() << ", " << point.pose.Translation().Y() << ", " << point.pose.Rotation().Degrees() << ")\n";
    }

    std::cout << "Testing!" << std::endl;*/
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
    driveCommand.reset(driveChooser.GetSelected());
    swerveSubsystem->SetCurrentCommand(driveCommand.get());
}

void Robot::TeleopPeriodic() {
    driveCommand.reset(driveChooser.GetSelected());
    swerveSubsystem->SetCurrentCommand(driveCommand.get());
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
