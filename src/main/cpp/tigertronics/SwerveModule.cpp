#include "tigertronics/SwerveModule.h"

#include <frc/geometry/Rotation2d.h>
#include <frc/smartdashboard/SendableBuilder.h>
#include <frc/smartdashboard/SendableRegistry.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "tigertronics/Util.h"

#define M_PI 3.14159265358979323846

constexpr units::meter_t SwerveModule::kWheelRadius;
constexpr int SwerveModule::kDriveEncoderResolution;
constexpr int SwerveModule::kTurningEncoderResolution;
constexpr int SwerveModule::kTurnErrorAllowance;
constexpr units::radians_per_second_t SwerveModule::kMaxTurnVel;
constexpr double SwerveModule::kMaxTurnAccel;

SwerveModule::SwerveModule(const int driveMotorPort, const int turingMotorPort, const int calibrationValue, const std::string name) 
    : m_driveMotor(driveMotorPort)
    , m_turningMotor(turingMotorPort)
    , kCalibrationValue(calibrationValue)
    , moduleName(name) {
    SetupDriveMotor();
    SetupTurningMotor();
    CalculateCalibrationSetpoint();
}

std::string SwerveModule::GetModuleName() {
    return moduleName;
}

void SwerveModule::SetDesiredState(units::meters_per_second_t speed, const frc::Rotation2d& angle, bool velocity) {
    frc::SwerveModuleState state;
    state.speed = speed;
    state.angle = angle;
    //dont reset modules to zero when letting go of joystick
    if(speed == 0_mps) {
        m_driveMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
        return;
    }
    SetDesiredState(state, velocity);
}

void SwerveModule::CalculateCalibrationSetpoint() {
    int currentPos = m_turningMotor.GetSensorCollection().GetPulseWidthPosition() & 0xFFF;
    int setpoint = currentPos - kCalibrationValue;
    m_turningMotor.SetSelectedSensorPosition(setpoint, 0, 10);
    SetSetpointAbs(setpoint);
}

void SwerveModule::SetSetpointAbs(int setpoint) {
    m_turningMotor.Set(ctre::phoenix::motorcontrol::ControlMode::Position, setpoint);
}

double SwerveModule::minDistance(double a, double b, double wrap) {
    return fabs(minChange(a, b, wrap));
}

double SwerveModule::minChange(double a, double b, double wrap) {
    return halfMod(a - b, wrap);
}

double SwerveModule::halfMod(double a, double wrap) {
    double aa = mod(a, wrap);
    double halfWrap = wrap / 2.0;
    if(aa >= halfWrap) {
        aa = aa - wrap;
    }
    return aa;
}

double SwerveModule::mod(double a, double b) {
    double r = fmod(a, b);
    if (r < 0) {
        r = r + b;
    }
    return r;
}

double SwerveModule::ConstrainAngle(double inputAngleDegrees) {
    inputAngleDegrees = fmod(inputAngleDegrees,360);
    if (inputAngleDegrees < 0)
        inputAngleDegrees += 360;
    return inputAngleDegrees;
}

std::pair<int, int> SwerveModule::FindSetpointInTicks(units::radian_t rads) {
    std::pair<int, int> retVal;
    int speedMulti = 1;
    int currentTicks = m_turningMotor.GetSelectedSensorPosition();
    int origTicks = ConvertRadiansToEncoderTicks(rads, kTurningEncoderResolution);
    int newTicks = minChange(origTicks, currentTicks, kTurningEncoderResolution / 2.0) + currentTicks;
    if(minDistance(newTicks, origTicks, kTurningEncoderResolution) < 0.001) {
        speedMulti = 1;
    }
    else {
        speedMulti = -1;
    }
    retVal.first = newTicks;
    retVal.second = speedMulti;
    return retVal;
}

void SwerveModule::SetDesiredState(frc::SwerveModuleState& state, bool velocityMode) {
    units::revolutions_per_minute_t setrpm = ConvertLinearToAngularVelocity(state.speed, kWheelRadius);
    //m_drivePIDController.Set(setrpm.value(), rev::ControlType::kVelocity);

    //frc::SwerveModuleState optimizedState = OptimizeModuleAngle(state);

    //state.angle = frc::Rotation2d(units::degree_t(ConstrainAngle(state.angle.Degrees().to<double>())));

    std::pair<int, int> finalSet = FindSetpointInTicks(state.angle.Radians());
    m_driveMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, Util::map(state.speed.value() * finalSet.second, -3, 3, -1, 1));
    m_turningMotor.Set(ctre::phoenix::motorcontrol::ControlMode::Position, finalSet.first);
    frc::SmartDashboard::PutNumber(GetModuleName(), m_turningMotor.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber(GetModuleName() + " setpoint", state.angle.Degrees().to<double>());
}

frc::SwerveModuleState SwerveModule::GetState() {
    units::radians_per_second_t wheelSpeed = units::revolutions_per_minute_t(ConvertTalonVelocityToRadiansPerSecond(m_driveMotor.GetSelectedSensorVelocity(), 6697));
    frc::SwerveModuleState state;
    state.angle = frc::Rotation2d(ConvertEncoderUnitsToRadians(m_turningMotor.GetSelectedSensorPosition(), kTurningEncoderResolution));
    state.speed = ConvertAngularToLinearVelocity(wheelSpeed, kWheelRadius);
    return state;
}

void SwerveModule::SetupDriveMotor() {
    m_driveMotor.ConfigFactoryDefault();
    m_driveMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 10);
    m_driveMotor.Config_kF(0, kDriveF, 10);
    m_driveMotor.Config_kP(0, kDriveP, 10);
    m_driveMotor.Config_kI(0, kDriveI, 10);
    m_driveMotor.Config_kD(0, kDriveD, 10);
    m_driveMotor.SetInverted(false);
    m_driveMotor.ConfigOpenloopRamp(.25, 10);
    m_driveMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
}

void SwerveModule::SetupTurningMotor() {
    m_turningMotor.ConfigFactoryDefault();
    m_turningMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    m_turningMotor.SetSensorPhase(false);
    m_turningMotor.SetInverted(true);
    m_turningMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
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
    m_turningMotor.ConfigMotionCruiseVelocity(ConvertRadiansPerSecondToTalonVelocity(kMaxTurnVel, kTurningEncoderResolution), 10);
    m_turningMotor.ConfigMotionAcceleration(kMaxTurnAccel, 10);
    m_turningMotor.SetSelectedSensorPosition(0);
    m_turningMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    m_turningMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    m_turningMotor.ConfigOpenloopRamp(.1);
}

int SwerveModule::ConvertRadiansToEncoderTicks(units::radian_t rads, int encoderResolution) {
    return (rads.value() * encoderResolution) / (M_PI * 2);
}

int SwerveModule::ConvertRadiansPerSecondToTalonVelocity(units::radians_per_second_t radPerSec, int encoderResolution) {
    return ConvertRadiansToEncoderTicks(units::radian_t(radPerSec.value()), encoderResolution) / 10;
}

units::radians_per_second_t SwerveModule::ConvertTalonVelocityToRadiansPerSecond(int ticksPer100ms, int encoderResolution) {
    return units::radians_per_second_t(ConvertEncoderUnitsToRadians(ticksPer100ms, encoderResolution).value() * 10);
}

units::radian_t SwerveModule::ConvertEncoderUnitsToRadians(int encoderTicks, int encoderResolution) {
    return units::radian_t((encoderTicks * (M_PI * 2)) / encoderResolution);
}

units::meters_per_second_t SwerveModule::ConvertAngularToLinearVelocity(units::radians_per_second_t wheelSpeed, units::meter_t radius) {
    return units::meters_per_second_t(wheelSpeed.value() * radius.value());
}

units::radians_per_second_t SwerveModule::ConvertLinearToAngularVelocity(units::meters_per_second_t velocity, units::meter_t radius) {
    return units::radians_per_second_t(velocity.value() / radius.value());
}

void SwerveModule::InitSendable(frc::SendableBuilder& builder) {
    builder.SetSmartDashboardType("SwerveModule");
    builder.AddDoubleProperty("turnP", [=]() { return kTurnP; }, [=](double value) { kTurnP = value; });
    builder.AddDoubleProperty("turnI", [=]() { return kTurnI; }, [=](double value) { kTurnI = value; });
    builder.AddDoubleProperty("turnD", [=]() { return kTurnD; }, [=](double value) { kTurnD = value; });
    builder.AddDoubleProperty("driveF", [=]() { return kDriveF; }, [=](double value) { kDriveF = value; });
    builder.AddDoubleProperty("driveP", [=]() { return kDriveP; }, [=](double value) { kDriveP = value; });
    builder.AddDoubleProperty("driveI", [=]() { return kDriveI; }, [=](double value) { kDriveI = value; });
    builder.AddDoubleProperty("driveD", [=]() { return kDriveD; }, [=](double value) { kDriveD = value; });
    builder.AddDoubleProperty("driveSetpoint", [=]() { return GetState().speed.value(); }, 
    [=](double value) { SetDesiredState(units::meters_per_second_t(value), GetState().angle, false); });
    builder.AddDoubleProperty("angleSetpoint", [=]() { return GetState().angle.Degrees().value(); }, 
    [=](double value) { SetDesiredState(GetState().speed, frc::Rotation2d(units::degree_t(value)), false); });
}

void SwerveModule::InvertDrive(bool inverted) {
    m_driveMotor.SetInverted(inverted);
}

void SwerveModule::InvertRot(bool inverted) {
    m_turningMotor.SetInverted(inverted);
}

frc::SwerveModuleState SwerveModule::OptimizeModuleAngle(const frc::SwerveModuleState& desiredState) {
    frc::SwerveModuleState finalStateAfterOptimization = desiredState;
    frc::Rotation2d deltaAngle{finalStateAfterOptimization.angle.Degrees() -
                          GetState().angle.Degrees()};
    if (units::math::abs(deltaAngle.Degrees()) > 90_deg &&
        units::math::abs(deltaAngle.Degrees()) < 270_deg) {
      finalStateAfterOptimization.angle =
          finalStateAfterOptimization.angle + frc::Rotation2d(180_deg);
      finalStateAfterOptimization.speed = -finalStateAfterOptimization.speed;
    }
    return finalStateAfterOptimization;
}