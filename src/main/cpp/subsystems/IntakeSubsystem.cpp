#include "subsystems/IntakeSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>

IntakeSubsystem::IntakeSubsystem() {
    SetName("IntakeSubsystem");
    ConfigFeederMotor();
    ConfigFunnelMotor();
    ConfigIntakeMotor();
}


void IntakeSubsystem::ConfigFunnelMotor(){
    funnelMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    funnelMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    funnelMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::ConfigFeederMotor(){
    feederMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    feederMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    feederMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::ConfigIntakeMotor(){
    intakeMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    intakeMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    intakeMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::SetFeederWheelSpeed(double speed){
    feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::SetFunnelWheelSpeed(double speed){
    funnelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::SetIntakeWheelsSpeed(double speed){
    intakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::SetIntakeFow() {
    intakeFlopper.Set(frc::DoubleSolenoid::Value::kForward);
}

void IntakeSubsystem::SetIntakeRev() {
    intakeFlopper.Set(frc::DoubleSolenoid::Value::kReverse);
}


void IntakeSubsystem::Periodic(){

}
