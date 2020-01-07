#pragma once

#include "rev/ColorSensorV3.h"

class Spinner : public frc2::SpinnerSubsystem {
    private: 
    std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> spinnerMotor;
    frc::Color color;

    public:
    Spinner();
    //checks for fms data
    void Periodic() override;
    //method to return color
    frc::Color getColor();
    //method to run motor
    void RunSpinnerMotor(double Speed);
}