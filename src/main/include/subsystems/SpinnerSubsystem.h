#pragma once

#include "rev/ColorSensorV3.h"

class Spinner : public frc2::SpinnerSubsystem {
    private: 
    static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    rev::ColorSensorV3 m_colorSensor{i2cPort};
    rev::ColorMatch m_colorMatcher;
    frc::Color color;
    std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> spinnerMotor;
    
    public:
    Spinner();
    //checks for fms data
    void Periodic() override;
    //method to run motor
    void RunSpinnerMotor(double Speed);

    static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
}