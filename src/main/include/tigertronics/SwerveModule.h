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
    SwerveModule(int driveMotorChannel, int turningMotorChannel);
    frc::SwerveModuleState GetState() const;
    void SetDesiredState(const frc::SwerveModuleState& state);

private:
    static constexpr units::meter_t kWheelRadius = tigertronics::constants::driveWheelRadius;
    static constexpr int kEncoderResolution = tigertronics::constants::ctreEncoderTicksPerRev;

    rev::SparkMax m_driveMotor;
    ctre::phoenix::motorcontrol::can::TalonSRX m_turningMotor;
};