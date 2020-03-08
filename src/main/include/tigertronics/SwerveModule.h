#pragma once

#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <frc/kinematics/SwerveModuleState.h>
#include "Constants.h"
#include <units/units.h>
#include <frc/smartdashboard/Sendable.h>
#include <frc/smartdashboard/SendableHelper.h>
#include <frc/geometry/Rotation2d.h>

class SwerveModule : public frc::Sendable, public frc::SendableHelper<SwerveModule> {
public:
    SwerveModule(int driveMotorChannel, int turningMotorChannel, int calibrationValue, std::string name);
    frc::SwerveModuleState GetState();
    void CalculateCalibrationSetpoint();
    void SetDesiredState(frc::SwerveModuleState& state, bool velocity);
    void SetDesiredState(units::meters_per_second_t speed, const frc::Rotation2d& angle, bool velocity);
    void InitSendable(frc::SendableBuilder& builder) override;
    void InvertDrive(bool inverted);
    void InvertRot(bool inverted);
    void SetupTurningMotor();
    void SetSetpointAbs(int setpoint);
    std::string GetModuleName();
private:
    void SetupDriveMotor();
    double ConstrainAngle(double inputAngleDegrees);
    frc::SwerveModuleState OptimizeModuleAngle(const frc::SwerveModuleState& desiredState);
    units::meters_per_second_t ConvertAngularToLinearVelocity(units::radians_per_second_t rpm, units::meter_t radius);
    units::radians_per_second_t ConvertLinearToAngularVelocity(units::meters_per_second_t velocity, units::meter_t radius);
    units::radians_per_second_t ConvertTalonVelocityToRadiansPerSecond(int ticksPer100ms, int encoderResolution);
    int ConvertRadiansPerSecondToTalonVelocity(units::radians_per_second_t radPerSec, int encoderResolution);
    units::radian_t ConvertEncoderUnitsToRadians(int encoderTicks, int encoderResolution);
    int ConvertRadiansToEncoderTicks(units::radian_t rads, int encoderResolution);
    std::pair<int, int> FindSetpointInTicks(units::radian_t rads);
    double mod(double a, double b);
    double halfMod(double a, double wrap);
    double minChange(double a, double b, double wrap);
    double minDistance(double a, double b, double wrap);
    static constexpr units::meter_t kWheelRadius = tigertronics::constants::driveWheelRadius;
    static constexpr int kTurningEncoderResolution = tigertronics::constants::ctreEncoderTicksPerRev;
    static constexpr int kDriveEncoderResolution = tigertronics::constants::talonFxEncoderTicksPerRev;
    double kTurnP = tigertronics::constants::swerveTurningkP;
    double kTurnI = tigertronics::constants::swerveTurningkI;
    double kTurnD = tigertronics::constants::swerveTurningkD;
    double kDriveF = tigertronics::constants::swerveDrivekF;
    double kDriveP = tigertronics::constants::swerveDrivekP;
    double kDriveI = tigertronics::constants::swerveDrivekI;
    double kDriveD = tigertronics::constants::swerveDrivekD;
    static constexpr units::radians_per_second_t kMaxTurnVel = tigertronics::constants::swerveTurningMaxVel;
    static constexpr double kMaxTurnAccel = tigertronics::constants::swerveTurningMaxAccel;
    static constexpr int kTurnErrorAllowance = tigertronics::constants::swerveTurningErrorAllowance;
    ctre::phoenix::motorcontrol::can::TalonFX m_driveMotor;
    ctre::phoenix::motorcontrol::can::TalonSRX m_turningMotor;
    int kCalibrationValue;
    std::string moduleName;
};