#include <subsystems/ControlPanelSubsystem.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Constants.h>
#include <frc/DriverStation.h>
#include <frc/shuffleboard/Shuffleboard.h>

ControlPanelSubsystem::ControlPanelSubsystem()
 : controlPanelTalon(tigertronics::ports::controlPanel),
 colorSensor(frc::I2C::Port::kOnboard), colorMatch() {
    controlPanelTalon.ConfigFactoryDefault();
    colorMatch.AddColorMatch(tigertronics::constants::kBlueTarget);
    colorMatch.AddColorMatch(tigertronics::constants::kGreenTarget);
    colorMatch.AddColorMatch(tigertronics::constants::kRedTarget);
    colorMatch.AddColorMatch(tigertronics::constants::kYellowTarget);

    gameData = frc::Color::kCrimson;
    gameDataInput = "";
}

frc::Color ControlPanelSubsystem::GetColor() {
    return gameData;
}

void ControlPanelSubsystem::Periodic() {
    gameDataInput = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    if(gameDataInput.length() > 0)
    {
        switch (gameDataInput[0])
        {
            case 'B' :
            gameData = frc::Color::kBlue;
                break;
            case 'G' :
            gameData = frc::Color::kGreen;
                break;
            case 'R' :
            gameData = frc::Color::kRed;
                break;
            case 'Y' :
            gameData = frc::Color::kYellow;
                break;
            default :
            gameData = frc::Color::kCrimson;
                break;
        }
    } else {
        gameData = frc::Color::kCrimson;
    }

    confidence = 0.0;
    matchedColor = colorMatch.MatchClosestColor(ReturnColorSensed(), confidence);

    if (matchedColor == tigertronics::constants::kBlueTarget) {
      colorString = "Blue";
    } else if (matchedColor == tigertronics::constants::kRedTarget) {
      colorString = "Red";
    } else if (matchedColor == tigertronics::constants::kGreenTarget) {
      colorString = "Green";
    } else if (matchedColor == tigertronics::constants::kYellowTarget) {
      colorString = "Yellow";
    } else {
      colorString = "Unknown";
    }

}

void ControlPanelSubsystem::SetControlPanelWheelSpeed(double speed) {
    controlPanelTalon.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

frc::Color ControlPanelSubsystem::ReturnColorSensed() {
    return colorSensor.GetColor();
}