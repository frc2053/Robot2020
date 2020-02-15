#pragma once

#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <AHRS.h>
#include <tigertronics/SwerveModule.h>
#include <Constants.h>
#include <units/units.h>
#include <tigertronics/MockAHRS.h>

#define M_PI 3.14159265358979323846

class SwerveDrivetrain {
public:
    SwerveDrivetrain();
    // Get the robot angle as a Rotation2d.
    frc::Rotation2d GetAngle() {
        // Negating the angle because WPILib Gyros are CW positive.
        return frc::Rotation2d(units::degree_t(-m_imu.GetYaw()));
    }

    std::vector<double> GetIMUData();

    void Drive(units::meters_per_second_t xSpeed,
            units::meters_per_second_t ySpeed, units::radians_per_second_t rot,
            bool fieldRelative, bool velocity);
    const frc::Pose2d& UpdateOdometry();
    void LogModulesToDashboard();
    const frc::Twist2d& GetDrivetrainSpeedsWorld();

    frc::SwerveDriveOdometry<4> GetOdom();
    frc::SwerveDriveKinematics<4> GetKinematics();

    units::meters_per_second_t kMaxSpeed =
    3.0_mps;  // 3 meters per second
    units::radians_per_second_t kMaxAngularSpeed{
    10};  // 1/2 rotation per second

    void ManualMoveWheel(std::string wheel, int setpoint);
    void ManualMoveWheel(std::string wheel, units::radian_t angle, units::meters_per_second_t speed);
    
    //Apparently all of math is Right Hand Rule Coordinate system but I dont like it
    units::meter_t widthLoc = tigertronics::constants::drivebaseWidth / 2;
    units::meter_t lengthLoc = tigertronics::constants::drivebaseLength / 2;
    frc::Translation2d m_frontLeftLocation{lengthLoc, widthLoc};
    frc::Translation2d m_frontRightLocation{lengthLoc, -widthLoc};
    frc::Translation2d m_backLeftLocation{-lengthLoc, widthLoc};
    frc::Translation2d m_backRightLocation{-lengthLoc, -widthLoc};

    SwerveModule m_frontLeft{tigertronics::ports::swerveFLDrive, tigertronics::ports::swerveFLTurn, tigertronics::constants::swerveFLCal, "FL"};
    SwerveModule m_frontRight{tigertronics::ports::swerveFRDrive, tigertronics::ports::swerveFRTurn, tigertronics::constants::swerveFRCal, "FR"};
    SwerveModule m_backLeft{tigertronics::ports::swerveBLDrive, tigertronics::ports::swerveBLTurn, tigertronics::constants::swerveBLCal, "BL"};
    SwerveModule m_backRight{tigertronics::ports::swerveBRDrive, tigertronics::ports::swerveBRTurn, tigertronics::constants::swerveBRCal, "BR"};

    #if defined(__FRC_ROBORIO__)
    AHRS m_imu{frc::SPI::Port::kMXP};
    #else
    MockAHRS m_imu{};
    #endif

    frc::Twist2d m_chassisSpeeds;
    frc::SwerveDriveKinematics<4> m_kinematics{
        m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation,
        m_backRightLocation};

    frc::SwerveDriveOdometry<4> m_odometry{m_kinematics, GetAngle(), frc::Pose2d()};
    void SetModuleStates(std::array<frc::SwerveModuleState, 4> desiredStates);

 private:
};