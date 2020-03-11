/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ConveyorSubsystem.h"
#include <frc/shuffleboard/Shuffleboard.h>

ConveyorSubsystem::ConveyorSubsystem() {
    SetName("ConveyorSubsystem");
    ConfigDashboard();
    ConfigFunnelMotor();
    ConfigConveyorMotor();
    ConfigFeederMotor();

    indexing = false;
    firing = false;
}

void ConveyorSubsystem::ConfigDashboard() {
    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Intake Subsystem");
    
    dashDetectedBallIntake = tab.Add("Detected Ball Intake", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithSize(1,1).GetEntry();
    dashDetectedBallFeeder = tab.Add("Detected Ball Feeder", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithSize(1,1).GetEntry();
}


void ConveyorSubsystem::ConfigFunnelMotor(){
    funnelMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    funnelMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    funnelMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ConveyorSubsystem::ConfigFeederMotor(){
    feederMotor.ConfigFactoryDefault();

    //incase we plug in a bad talon
    feederMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    feederMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ConveyorSubsystem::ConfigConveyorMotor(){
    conveyorMotor.ConfigFactoryDefault();

    conveyorMotor.ConfigClosedloopRamp(0.5);
    
    //incase we plug in a bad talon
    conveyorMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    conveyorMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ConveyorSubsystem::SetFiringOn(){
    firing = true;
}

void ConveyorSubsystem::SetFiringOff(){
    firing = false;
}

void ConveyorSubsystem::SetIndexingOn(){
    indexing = true;
}

void ConveyorSubsystem::SetIndexingOff(){
    indexing = false;
}

void ConveyorSubsystem::SetFunnelSpeed(double speed){
    funnelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void ConveyorSubsystem::SetConveyorSpeed(double speed) {
    conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void ConveyorSubsystem::SetFeederSpeed(double speed){
    feederMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

bool ConveyorSubsystem::DetectedBallIntake() {
    return (units::millimeter_t(intakeDistSensor.GetRange()) < tigertronics::constants::distThreshold);
}

bool ConveyorSubsystem::DetectedBallFeeder() {
    return (units::millimeter_t(feederDistSensor.GetRange()) < tigertronics::constants::distThreshold);
}

// This method will be called once per scheduler run
void ConveyorSubsystem::Periodic() {
    
    bool ballIntake = DetectedBallIntake();
    bool ballFeeder = DetectedBallFeeder();
    double funnelSpeed = 0.0;
    double conveyorSpeed = 0.0;
    double feederSpeed = 0.0;

    // If we're firing, put everythig on full blast.
    // If we're indexing, stop the feeder, run the funnel, and use the sensor for the conveyor.
    // Otherwise, leave the motors off.
    if (firing) {
        funnelSpeed = 1.0;
        conveyorSpeed = 1.0;
        feederSpeed = 1.0;
    } else if (indexing) {
        if (ballIntake) {
            conveyorSpeed = 0.5;
        } else {
            conveyorSpeed = 0.0;
        }
        funnelSpeed = 0.3;
        feederSpeed = 0.3;
    } else {
        funnelSpeed = 0.0;
        conveyorSpeed = 0.0;
        feederSpeed = 0.0;
    }

    // Every 10th cycle, update the dashboard.
    count++;
    if (count > 10){
        dashDetectedBallIntake.SetBoolean(ballIntake);
        dashDetectedBallFeeder.SetBoolean(ballFeeder);
        count = 0;
    }
}
