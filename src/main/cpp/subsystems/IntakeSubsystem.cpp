#include "subsystems/IntakeSubsystem.h"

IntakeSubsystem::IntakeSubsystem() {
    SetName("IntakeSubsystem");
    ConfigConveyorMotor();
    ConfigFeederMotor();
    ConfigIntakeMotor();
}

void IntakeSubsystem::ConfigConveyorMotor(){
    conveyorMotor.ConfigFactoryDefault();
    conveyorMotor.ConfigOpenloopRamp(.1);

    //incase we plug in a bad talon
    conveyorMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    conveyorMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::ConfigFeederMotor(){
    feederMotor.ConfigFactoryDefault();
    feederMotor.ConfigOpenloopRamp(.1);

    //incase we plug in a bad talon
    feederMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    feederMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::ConfigIntakeMotor(){
    intakeMotor.ConfigFactoryDefault();
    intakeMotor.ConfigOpenloopRamp(.1);

    //incase we plug in a bad talon
    intakeMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    intakeMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::SetConveyorBeltSpeed(double speed){
    conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::SetFeederWheelSpeed(double speed){
    feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::SetIntakeWheelsSpeed(double speed){
    intakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::Periodic(){}
