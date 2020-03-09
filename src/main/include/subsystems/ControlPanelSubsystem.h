#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/util/Color.h>
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
#include "rev/ColorSensorV3.h"
#include <Constants.h>
#include "rev/ColorMatch.h"

class ControlPanelSubsystem : public frc2::SubsystemBase {
public:
    ControlPanelSubsystem();
    frc::Color GetColor();
    void Periodic() override;
    void SetControlPanelWheelSpeed(double speed);
    frc::Color ReturnColorSensed();
    std::string GetColorString();
private:
    frc::Color gameData;
    frc::Color matchedColor;
    std::string gameDataInput;
    ctre::phoenix::motorcontrol::can::TalonSRX controlPanelTalon;
    rev::ColorSensorV3 colorSensor;
    rev::ColorMatch colorMatch;
    std::string colorString;
    double confidence;
};