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
    SetFiring(false);
    SetOverride(false);
    SetIndexing(false);
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


void IntakeSubsystem::SetOverride(bool isOverride){
    override = isOverride;
}

void IntakeSubsystem::SetIndexing(bool isIndexing){
    indexing = isIndexing;
}
  
void IntakeSubsystem::SetFiring(bool isFiring){
    firing = isFiring;
}

void IntakeSubsystem::SetConveyorBeltOverrideSpeed(double speed){
    // conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
    conveyorOverrideSpeed = speed;
}

void IntakeSubsystem::SetFeederWheelOverrideSpeed(double speed){
    // feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
    feederOverrideSpeed = speed;
}

void IntakeSubsystem::SetFunnelWheelOverrideSpeed(double speed){
    // funnelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
    funnelOverrideSpeed = speed;
}

void IntakeSubsystem::SetIntakeWheelsOverrideSpeed(double speed){
    // intakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
    intakeOverrideSpeed = speed;
}

void IntakeSubsystem::SetIntakeFow() {
    // intakeFlopper.Set(frc::DoubleSolenoid::Value::kForward);
    intakeForward = true;
}

void IntakeSubsystem::SetIntakeRev() {
    // intakeFlopper.Set(frc::DoubleSolenoid::Value::kReverse);
    intakeForward = false;
}

units::millimeter_t IntakeSubsystem::GetIntakeDistFiltered() {
    return intakeDistFiltered;
}

units::millimeter_t IntakeSubsystem::GetLoaderDistFiltered() {
    return loaderDistFiltered;
}

bool IntakeSubsystem::DetectedBallIn() {
    return (intakeDistSensor.GetRange() < 100);
    //return (GetIntakeDistFiltered() > tigertronics::constants::distThreshold);
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

    frc::Shuffleboard::GetTab("Intake Subsystem").Add("intakeForward", intakeForward);
    frc::Shuffleboard::GetTab("Intake Subsystem").Add("override", override);
    frc::Shuffleboard::GetTab("Intake Subsystem").Add("firing", firing);
    frc::Shuffleboard::GetTab("Intake Subsystem").Add("indexing", indexing);
    
    frc::Shuffleboard::GetTab("Intake Subsystem").AddNumber("Intake Distance Filtered", intakeDistFiltered);
    frc::Shuffleboard::GetTab("Intake Subsystem").AddNumber("Loader Distance Filtered", loaderDistFiltered);

    bool ballIn = DetectedBallIn();
    bool ballOut = DetectedBallOut();

    float intakeSpeed = 0;
    float funnelSpeed = 0;
    float conveyorSpeed = 0;
    float feederSpeed = 0;

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
    
    if (intakeForward) {
        intakeFlopper.Set(frc::DoubleSolenoid::Value::kReverse);
    } else {
        intakeFlopper.Set(frc::DoubleSolenoid::Value::kForward);
    }

    //override only is true in auto
    if (override) {
        intakeSpeed = intakeOverrideSpeed;
        funnelSpeed = funnelOverrideSpeed;
        conveyorSpeed = conveyorOverrideSpeed;
        feederSpeed = feederOverrideSpeed;
    } 
    //if we are shooting only
    else if (firing) {
        intakeSpeed = intakeFiringSpeed;
        funnelSpeed = funnelFiringSpeed;
        conveyorSpeed = conveyorFiringSpeed;
        feederSpeed = feederFiringSpeed;
    }
    //default, when we aren't doing anything else
    else if (indexing) {
        if (intakeForward) {
            intakeSpeed = intakeIndexSpeed;
        } else {
            intakeSpeed = 0;
        }

        if (ballIn) {
            conveyorSpeed = conveyorIndexSpeed;
        } else {
            conveyorSpeed = 0;
        }
        funnelSpeed = funnelIndexSpeed;
    } 
    //shouldnt ever get here unless manually override somehow
    else {
        intakeSpeed = 0;
        funnelSpeed = 0;
        conveyorSpeed = 0;
        feederSpeed = 0;
    }

    intakeMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, intakeSpeed);
    funnelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, funnelSpeed);
    conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, conveyorSpeed);
    feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, feederSpeed);

    dashNumOfBalls.SetDouble(GetNumOfBalls());
    dashDetectedBallIn.SetBoolean(ballIn);
    dashDetectedBallOut.SetBoolean(ballOut);
    dashRawIntakeDist.SetDouble(rawIntakeDist);
    dashRawLoaderDist.SetDouble(rawLoaderDist);
    dashFilteredIntakeDist.SetDouble(intakeDistFiltered.to<double>());
    dashFilteredLoaderDist.SetDouble(loaderDistFiltered.to<double>());
}
