#include "tigertronics/SwerveModule.h"

#include <frc_new/geometry/Rotation2d.h>

#define M_PI 3.14159265358979323846

constexpr units::meter_t SwerveModule::kWheelRadius;
constexpr int SwerveModule::kEncoderResolution;
constexpr double SwerveModule::kTurnP;
constexpr double SwerveModule::kTurnI;
constexpr double SwerveModule::kTurnD;
constexpr int SwerveModule::kTurnErrorAllowance;
constexpr units::radians_per_second_t SwerveModule::kMaxTurnVel;
constexpr double SwerveModule::kMaxTurnAccel;

SwerveModule::SwerveModule(const int driveMotorPort, const int turingMotorPort, const int calibrationValue) 
    : m_driveMotor(driveMotorPort, rev::CANSparkMaxLowLevel::MotorType::kBrushless)
    , m_turningMotor(turingMotorPort), m_drivePIDController(m_driveMotor.GetPIDController())
    , m_driveEncoder(m_driveMotor.GetEncoder())
    , kCalibrationValue(calibrationValue) {
    SetupDriveMotor();
    SetupTurningMotor();
}

void SwerveModule::SetDesiredState(const frc_new::SwerveModuleState& state) {
    units::revolutions_per_minute_t setrpm = ConvertLinearToAngularVelocity(state.speed, kWheelRadius);
    m_drivePIDController.SetReference(setrpm.value(), rev::ControlType::kVelocity);
    m_turningMotor.Set(ctre::phoenix::motorcontrol::ControlMode::Position, ConvertRadiansToEncoderTicks(state.angle.Radians()));
}

frc_new::SwerveModuleState SwerveModule::GetState() {
    units::radians_per_second_t wheelSpeed = units::revolutions_per_minute_t(m_driveEncoder.GetVelocity());
    frc_new::SwerveModuleState state;
    state.angle = frc_new::Rotation2d(ConvertEncoderUnitsToRadians(m_turningMotor.GetSelectedSensorPosition()));
    state.speed = ConvertAngularToLinearVelocity(wheelSpeed, kWheelRadius);
    return state;
}

void SwerveModule::SetupDriveMotor() {

}

void SwerveModule::SetupTurningMotor() {
    m_turningMotor.ConfigFactoryDefault();
    m_turningMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    m_turningMotor.SetSensorPhase(false);
    m_turningMotor.SetInverted(false);
    m_turningMotor.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    m_turningMotor.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);
    m_turningMotor.ConfigNominalOutputForward(0, 10);
    m_turningMotor.ConfigNominalOutputReverse(0, 10);
    m_turningMotor.ConfigPeakOutputForward(1, 10);
    m_turningMotor.ConfigPeakOutputReverse(-1, 10);
    m_turningMotor.Config_kF(0, 0, 10);
    m_turningMotor.Config_kP(0, kTurnP, 10);
    m_turningMotor.Config_kI(0, kTurnI, 10);
    m_turningMotor.Config_kD(0, kTurnD, 10);
    m_turningMotor.ConfigAllowableClosedloopError(0, kTurnErrorAllowance, 10);
    m_turningMotor.EnableCurrentLimit(true);
    m_turningMotor.ConfigContinuousCurrentLimit(10, 10);
    m_turningMotor.ConfigPeakCurrentLimit(0, 10);
    m_turningMotor.GetSensorCollection().SyncQuadratureWithPulseWidth(0, 0, true, kCalibrationValue, 10);
    m_turningMotor.ConfigMotionCruiseVelocity(ConvertRadiansPerSecondToTalonVelocity(kMaxTurnVel), 10);
    m_turningMotor.ConfigMotionAcceleration(kMaxTurnAccel, 10);
    m_turningMotor.SetSelectedSensorPosition(0);
}

int SwerveModule::ConvertRadiansToEncoderTicks(units::radian_t rads) {
    return (rads.value() * kEncoderResolution) / (M_PI * 2);
}

int SwerveModule::ConvertRadiansPerSecondToTalonVelocity(units::radians_per_second_t radPerSec) {
    return ConvertRadiansToEncoderTicks(radPerSec) / 10;
}

units::radians_per_second_t SwerveModule::ConvertTalonVelocityToRadiansPerSecond(int ticksPer100ms) {
    return units::radians_per_second_t(ConvertEncoderUnitsToRadians(ticksPer100ms).value() * 10);
}

units::radian_t SwerveModule::ConvertEncoderUnitsToRadians(int encoderTicks) {
    return units::radian_t((encoderTicks * (M_PI * 2)) / kEncoderResolution);
}

units::meters_per_second_t SwerveModule::ConvertAngularToLinearVelocity(units::radians_per_second_t wheelSpeed, units::meter_t radius) {
    return units::meters_per_second_t(wheelSpeed.value() * radius.value());
}

units::radians_per_second_t SwerveModule::ConvertLinearToAngularVelocity(units::meters_per_second_t velocity, units::meter_t radius) {
    return units::radians_per_second_t(velocity.value() / radius.value());
}