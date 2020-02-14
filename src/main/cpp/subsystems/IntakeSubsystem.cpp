#include "subsystems/IntakeSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

IntakeSubsystem::IntakeSubsystem() {
    SetName("IntakeSubsystem");
    ConfigConveyorMotor();
    ConfigFeederMotor();
    ConfigIntakeMotor();
    frc::SmartDashboard::PutNumber("intake input", 0);
    frc::SmartDashboard::PutNumber("loader input", 0);
}

void IntakeSubsystem::ConfigConveyorMotor(){
    conveyorMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    conveyorMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    conveyorMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
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

void IntakeSubsystem::SetConveyorBeltSpeed(double speed){
    conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void IntakeSubsystem::SetFeederWheelSpeed(double speed){
    feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
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

units::millimeter_t IntakeSubsystem::GetIntakeDistFiltered() {
    return intakeDistFiltered;
}

units::millimeter_t IntakeSubsystem::GetLoaderDistFiltered() {
    return loaderDistFiltered;
}

bool IntakeSubsystem::DetectedBallIn() {
    return (GetIntakeDistFiltered() > tigertronics::constants::distThreshold);
}

bool IntakeSubsystem::DetectedBallOut() {
    return (GetLoaderDistFiltered() > tigertronics::constants::distThreshold);
}

void IntakeSubsystem::SetNumOfBalls(int balls) {
    numOfBalls = balls;
}

int IntakeSubsystem::GetNumOfBalls() {
    return numOfBalls;
}

void IntakeSubsystem::Periodic(){
    //double rawIntakeDist = intakeDistSensor.GetRange();
    //double rawLoaderDist = loaderDistSensor.GetRange();
    double rawIntakeDist = frc::SmartDashboard::GetNumber("intake input", 0);
    double rawLoaderDist = frc::SmartDashboard::GetNumber("loader input", 0);
    intakeDistFiltered = units::millimeter_t(intakeHighFilter.Calculate(intakeLowFilter.Calculate(rawIntakeDist)));
    loaderDistFiltered = units::millimeter_t(loaderHighFilter.Calculate(loaderLowFilter.Calculate(rawLoaderDist)));

    frc::SmartDashboard::PutNumber("raw intake dist", rawIntakeDist);
    frc::SmartDashboard::PutNumber("raw loader dist", rawLoaderDist);

    frc::SmartDashboard::PutNumber("filtered intake dist", intakeDistFiltered.to<double>());
    frc::SmartDashboard::PutNumber("filtered loader dist", loaderDistFiltered.to<double>());
    
    bool ballIn = DetectedBallIn();
    bool ballOut = DetectedBallOut();

    frc::SmartDashboard::PutBoolean("detected ball in", ballIn);
    frc::SmartDashboard::PutBoolean("detected ball out", ballOut);

    if(ballIn != detectedIntake) {
        if(ballIn) {
            numOfBalls = numOfBalls + 1;
        }
        detectedIntake = ballIn;
    }

    if(ballOut != detectedLoader) {
        if(ballOut) {
            numOfBalls = numOfBalls - 1;
        }
        detectedLoader = ballOut;
    }

    frc::SmartDashboard::PutNumber("num of balls", numOfBalls);
}
