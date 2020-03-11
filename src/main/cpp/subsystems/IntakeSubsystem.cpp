#include "subsystems/IntakeSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>

IntakeSubsystem::IntakeSubsystem() {
    SetName("IntakeSubsystem");
    ConfigIntakeMotor();
    ResetIntake();
    intakeDown = false;
    intakeOn = false;
}

void IntakeSubsystem::ConfigIntakeMotor(){
    intakeMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    intakeMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    intakeMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void IntakeSubsystem::SetIntakeOn() {
    intakeOn = true;
}

void IntakeSubsystem::SetIntakeOff(){
    intakeOn = false;
}

void IntakeSubsystem::SetIntakeDown() {
    intakeDown = true;
}

void IntakeSubsystem::SetIntakeUp(){
    intakeDown = false;
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
    double intakeSpeed = 0.0;

    if (intakeDown){
        SetIntakeFow();
    } else {
        SetIntakeRev();
    }

    // Intake must be activated and down to allow the motor to run.
    if (intakeOn && intakeDown){
        intakeSpeed = 0.5
    } else {
        intakeSpeed = 0.0;
    }
    
    SetIntakeWheelsSpeed(intakeSpeed);
}
