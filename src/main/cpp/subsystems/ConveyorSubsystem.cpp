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
    ConfigConveyorMotor();
    ConfigDashboard();
}

void ConveyorSubsystem::ConfigConveyorMotor(){
    conveyorMotor.ConfigFactoryDefault();

    conveyorMotor.ConfigClosedloopRamp(0.5);
    
    //incase we plug in a bad talon
    conveyorMotor.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    conveyorMotor.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ConveyorSubsystem::ConfigDashboard() {
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

void ConveyorSubsystem::SetConveyorBeltSpeed(double speed) {
    conveyorMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

units::millimeter_t ConveyorSubsystem::GetIntakeDistFiltered() {
    return intakeDistFiltered;
}

units::millimeter_t ConveyorSubsystem::GetLoaderDistFiltered() {
    return loaderDistFiltered;
}

bool ConveyorSubsystem::DetectedBallIn() {
    return (units::millimeter_t(intakeDistSensor.GetRange()) < tigertronics::constants::distThreshold);
}

bool ConveyorSubsystem::DetectedBallOut() {
    return (units::millimeter_t(loaderDistSensor.GetRange()) < tigertronics::constants::distThreshold);
}

void ConveyorSubsystem::SetNumOfBalls(int balls) {
    numOfBalls = balls;
}

int ConveyorSubsystem::GetNumOfBalls() {
    return numOfBalls;
}

// This method will be called once per scheduler run
void ConveyorSubsystem::Periodic() {
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
