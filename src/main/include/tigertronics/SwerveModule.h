/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <rev/CANSparkMax.h>
#include <frc_new/kinematics/SwerveModuleState.h>
#include "Constants.h"
#include <units/units.h>

class SwerveModule {
public:
    SwerveModule(int driveMotorChannel, int turningMotorChannel, int calibrationValue);
    frc_new::SwerveModuleState GetState();
    void SetDesiredState(const frc_new::SwerveModuleState& state);

private:
    void SetupDriveMotor();
    void SetupTurningMotor();
    units::meters_per_second_t ConvertAngularToLinearVelocity(units::radians_per_second_t rpm, units::meter_t radius);
    units::radians_per_second_t ConvertLinearToAngularVelocity(units::meters_per_second_t velocity, units::meter_t radius);
    units::radians_per_second_t ConvertTalonVelocityToRadiansPerSecond(int ticksPer100ms);
    int ConvertRadiansPerSecondToTalonVelocity(units::radians_per_second_t radPerSec);
    units::radian_t ConvertEncoderUnitsToRadians(int encoderTicks);
    int ConvertRadiansToEncoderTicks(units::radian_t rads);
    static constexpr units::meter_t kWheelRadius = tigertronics::constants::driveWheelRadius;
    static constexpr int kEncoderResolution = tigertronics::constants::ctreEncoderTicksPerRev;
    static constexpr double kTurnP = tigertronics::constants::swerveTurningkP;
    static constexpr double kTurnI = tigertronics::constants::swerveTurningkI;
    static constexpr double kTurnD = tigertronics::constants::swerveTurningkD;
    static constexpr units::radians_per_second_t kMaxTurnVel = tigertronics::constants::swerveTurningMaxVel;
    static constexpr double kMaxTurnAccel = tigertronics::constants::swerveTurningMaxAccel;
    static constexpr int kTurnErrorAllowance = tigertronics::constants::swerveTurningErrorAllowance;
    int kCalibrationValue;
    rev::CANSparkMax m_driveMotor;
    rev::CANPIDController m_drivePIDController;
    rev::CANEncoder m_driveEncoder;
    ctre::phoenix::motorcontrol::can::TalonSRX m_turningMotor;
};