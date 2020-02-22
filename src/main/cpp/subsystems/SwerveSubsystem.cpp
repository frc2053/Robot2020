#include "subsystems/SwerveSubsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "units/units.h"
#include "frc/geometry/Pose2d.h"
#include "frc/geometry/Twist2d.h"

SwerveSubsystem::SwerveSubsystem() {
    m_swerve.LogModulesToDashboard();
}

frc::SwerveDriveOdometry<4> SwerveSubsystem::GetOdom() {
    return m_swerve.GetOdom();
}

frc::SwerveDriveKinematics<4> SwerveSubsystem::GetKinematics() {
    return m_swerve.GetKinematics();
}

units::degree_t SwerveSubsystem::GetImuYaw() {
    return m_swerve.GetAngle().Degrees();
}

void SwerveSubsystem::ZeroYaw() {
    m_swerve.ZeroYaw();
}

void SwerveSubsystem::ManualWheelMove(std::string wheel, int abs_setpoint) {
    m_swerve.ManualMoveWheel(wheel, abs_setpoint);
}

void SwerveSubsystem::ManualWheelMove(std::string wheel, units::radian_t angle, units::meters_per_second_t speed) {
    m_swerve.ManualMoveWheel(wheel, angle, speed);
}

void SwerveSubsystem::SetRobotPose(const frc::Pose2d& newPose, const frc::Rotation2d& newYaw) {
    m_swerve.m_odometry.ResetPosition(newPose, newYaw);
}

void SwerveSubsystem::DriveWithJoystick(double x, double y, double rot, bool fieldRelative) {
    //need to negative strafe because if you push right on the joystick it returns a + value
    //however, the kinematics expects that left is positive for the y axis
    //similar for rot axis because if you push right on the stick, it returns a positive value
    //however, the kinematics expects a "positive" rotation to be CCW
    double strafeAxis = -1 * x;
    double fowAxis = -1 * y;
    double rotAxis = -1 * rot;
    
    if(strafeAxis > -.2 && strafeAxis < .2) {
        strafeAxis = 0;
    }
    else {
        strafeAxis = strafeAxis * fabs(strafeAxis);
    }
    if(fowAxis > -.2 && fowAxis < .2) {
        fowAxis = 0;
    }
    else {
        fowAxis = fowAxis * fabs(fowAxis);
    }
    if(rotAxis > -.2 && rotAxis < .2) {
        rotAxis = 0;
    }
    else {
        rotAxis = rotAxis * fabs(rotAxis);
    }
    frc::SmartDashboard::PutNumber("X Joystick", strafeAxis);
    frc::SmartDashboard::PutNumber("Y Joystick", fowAxis);
    frc::SmartDashboard::PutNumber("Rot Joystick", rotAxis);
    frc::SmartDashboard::PutString("Drive Mode", "Joystick");
    //x + is forward
    //y + is left
    //rot + is CCW
    const auto xSpeed = fowAxis * m_swerve.kMaxSpeed;
    const auto ySpeed = strafeAxis * m_swerve.kMaxSpeed;
    const auto rotSpeed = rotAxis * m_swerve.kMaxAngularSpeed;
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, fieldRelative, false);
}

void SwerveSubsystem::AutoDrive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed) {
    frc::SmartDashboard::PutString("Drive Mode", "Auto");
    m_swerve.Drive(xSpeed, ySpeed, rotSpeed, false, true);
}

void SwerveSubsystem::Periodic() {
    currentPose = m_swerve.UpdateOdometry();
    currentTwist = m_swerve.GetDrivetrainSpeedsWorld();
    currentIMUData = m_swerve.GetIMUData();
    frc::SmartDashboard::PutNumber("X Pose: ", currentPose.Translation().X().value());
    frc::SmartDashboard::PutNumber("Y Pose: ", currentPose.Translation().Y().value());
    frc::SmartDashboard::PutNumber("Yaw Pose: ", currentPose.Rotation().Degrees().value());
}

const frc::Pose2d& SwerveSubsystem::GetCurrentPose() {
    return currentPose;
}

const frc::Twist2d& SwerveSubsystem::GetCurrentTwist() {
    return currentTwist;
}

std::vector<double> SwerveSubsystem::GetIMUData() {
    return currentIMUData;
}