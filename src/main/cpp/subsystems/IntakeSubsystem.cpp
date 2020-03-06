#include "subsystems/IntakeSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>

IntakeSubsystem::IntakeSubsystem() {
    SetName("IntakeSubsystem");
    ConfigConveyorMotor();
    ConfigFeederMotor();
    ConfigFunnelMotor();
    ConfigIntakeMotor();
    ConfigDashboard();
}

void IntakeSubsystem::ConfigConveyorMotor(){
    conveyorMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    conveyorMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    conveyorMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
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

void IntakeSubsystem::ConfigDashboard() {
    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Intake Subsystem");
    wpi::StringMap<std::shared_ptr<nt::Value>> properties{
        std::make_pair("min", nt::Value::MakeDouble(0)),
        std::make_pair("max", nt::Value::MakeDouble(5))
    };
    dashNumOfBalls = tab.Add("Number of Balls", 0).WithWidget(frc::BuiltInWidgets::kDial).WithSize(2,2).WithProperties(properties).GetEntry();
    dashDetectedBallIn = tab.Add("Detected Ball In", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithSize(1,1).GetEntry();
    dashDetectedBallOut = tab.Add("Detected Ball Out", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithSize(1,1).GetEntry();
    dashRawIntakeDist = tab.Add("Raw Intake Distance", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    dashRawLoaderDist = tab.Add("Raw Loader Distance", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    dashFilteredIntakeDist = tab.Add("Filtered Intake Distance", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    dashFilteredLoaderDist = tab.Add("Filtered Loader Distance", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
}

void IntakeSubsystem::SetConveyorBeltSpeed(double speed){
    conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
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
    double rawIntakeDist = intakeDistSensor.GetRange();
    double rawLoaderDist = loaderDistSensor.GetRange();
    intakeDistFiltered = units::millimeter_t(intakeHighFilter.Calculate(intakeLowFilter.Calculate(rawIntakeDist)));
    loaderDistFiltered = units::millimeter_t(loaderHighFilter.Calculate(loaderLowFilter.Calculate(rawLoaderDist)));
    
    bool ballIn = DetectedBallIn();
    bool ballOut = DetectedBallOut();

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

    dashNumOfBalls.SetDouble(GetNumOfBalls());
    dashDetectedBallIn.SetBoolean(ballIn);
    dashDetectedBallOut.SetBoolean(ballOut);
    dashRawIntakeDist.SetDouble(rawIntakeDist);
    dashRawLoaderDist.SetDouble(rawLoaderDist);
    dashFilteredIntakeDist.SetDouble(intakeDistFiltered.to<double>());
    dashFilteredLoaderDist.SetDouble(loaderDistFiltered.to<double>());
}
