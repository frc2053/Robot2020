/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ShooterSubsystem.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>

ShooterSubsystem::ShooterSubsystem() {
    SetName("Shooter Subsystem");
    ConfigureLoaderMotor();
    ConfigureShooterMotors();
    ConfigureDashboard();
}

void ShooterSubsystem::ConfigureDashboard() {
    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Shooter Subsystem");
    frc::ShuffleboardLayout& velocityGroup = tab.GetLayout("Velocities", frc::BuiltInLayouts::kList).WithSize(4,6).WithProperties("");
    leftShooterDash = tab.Add("Left Wheel Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    rightShooterDash = tab.Add("Right Wheel Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    avgShooterDash = tab.Add("Average Wheel Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    wheelSpeedDash = tab.Add("Shooter Wheel Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    shooterSpeedSetpointDash = tab.Add("Shooter Setpoint", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithSize(2, 1).GetEntry();
    hoodAngleSetpointDash = tab.Add("Hood Angle Setpoint", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithSize(2,1 ).GetEntry();
}

void ShooterSubsystem::ConfigureShooterMotors() {
    shooterMotorLeft.ConfigFactoryDefault();
    shooterMotorRight.ConfigFactoryDefault();

    shooterMotorRight.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor);
    shooterMotorRight.Config_kF(0, kFF);
    shooterMotorRight.Config_kP(0, kP);
    shooterMotorRight.Config_kI(0, kP);
    shooterMotorRight.Config_kD(0, kP);

    shooterMotorRight.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);

    shooterMotorLeft.Follow(shooterMotorRight);
    shooterMotorLeft.SetInverted(true);

    shooterMotorLeft.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    shooterMotorLeft.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);

    //incase we plug in a bad talon
    shooterMotorRight.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    shooterMotorRight.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ShooterSubsystem::ConfigureLoaderMotor() {
    loaderWheel.ConfigFactoryDefault();

    //incase we plug in a bad talon
    loaderWheel.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    loaderWheel.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ShooterSubsystem::SetShooterToVelocity(units::revolutions_per_minute_t shaftSpeed) {
    shooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, ConvertRPMToTickVel(shaftSpeed));
}

units::revolutions_per_minute_t ShooterSubsystem::GetShooterLeftRPM() {
    return ConvertTickVelToRPM(shooterMotorLeft.GetSelectedSensorVelocity());
}

units::revolutions_per_minute_t ShooterSubsystem::GetShooterRightRPM() {
    return ConvertTickVelToRPM(shooterMotorRight.GetSelectedSensorVelocity());
}

units::revolutions_per_minute_t ShooterSubsystem::GetShooterAvgRPM() {
    return (GetShooterLeftRPM() + GetShooterRightRPM()) / 2;
}

units::feet_per_second_t ShooterSubsystem::GetShooterSurfaceSpeed() {
    return units::feet_per_second_t(GetShooterAvgRPM().value() * tigertronics::constants::shooterWheelRadius.value());
}

units::revolutions_per_minute_t ShooterSubsystem::ConvertTickVelToRPM(int ticksPer100ms) {
    return units::revolutions_per_minute_t((ticksPer100ms * 600) / (tigertronics::constants::ctreEncoderTicksPerRev / tigertronics::constants::shooterGearRatio));
}

int ShooterSubsystem::ConvertRPMToTickVel(units::revolutions_per_minute_t rpm) {
    return (rpm.value()  / 600) * (tigertronics::constants::ctreEncoderTicksPerRev / tigertronics::constants::shooterGearRatio);
}

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {
    leftShooterDash.SetDouble(GetShooterLeftRPM().value());
    rightShooterDash.SetDouble(GetShooterRightRPM().value());
    avgShooterDash.SetDouble(GetShooterAvgRPM().value());
    wheelSpeedDash.SetDouble(GetShooterSurfaceSpeed().value());
}
