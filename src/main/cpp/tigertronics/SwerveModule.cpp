#include "tigertronics/SwerveModule.h"

#include <frc_new/geometry/Rotation2d.h>

#define M_PI 3.14159265358979323846

constexpr units::meter_t SwerveModule::kWheelRadius;
constexpr int  SwerveModule::kEncoderResolution;

SwerveModule::SwerveModule(const int driveMotorPort, const int turingMotorPort) 
    : m_driveMotor(driveMotorPort, rev::CANSparkMaxLowLevel::MotorType::kBrushless)
    , m_turningMotor(turingMotorPort), m_drivePIDController(m_driveMotor.GetPIDController())
    , m_driveEncoder(m_driveMotor.GetEncoder()) {
    SetupDriveMotor();
    SetupTurningMotor();
}

frc_new::SwerveModuleState SwerveModule::GetState() {
    units::revolutions_per_minute_t rpm = units::revolutions_per_minute_t(m_driveEncoder.GetVelocity());
    frc_new::SwerveModuleState state;
    state.angle = frc_new::Rotation2d(ConvertEncoderUnitsToRadians(m_turningMotor.GetSelectedSensorPosition()));
    state.speed = ConvertAngularToLinearVelocity(rpm, kWheelRadius);
    return state;
}

void SwerveModule::SetupDriveMotor() {

}

void SwerveModule::SetupTurningMotor() {

}

units::radian_t SwerveModule::ConvertEncoderUnitsToRadians(int encoderTicks) {
    return units::radian_t((encoderTicks * (M_PI * 2)) / kEncoderResolution);
}

units::meters_per_second_t SwerveModule::ConvertAngularToLinearVelocity(units::revolutions_per_minute_t rpm, units::meter_t radius) {
    return units::meters_per_second_t(rpm.value() * radius.value());
}