/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LEDSubsystem.h"

LEDSubsystem::LEDSubsystem() {}

// This method will be called once per scheduler run
void LEDSubsystem::Periodic() {}


void LEDSubsystem::SetAllLEDSToColor(frc::Color color) {
    FillBuffer(color, 0, tigertronics::constants::controlPanelEndLed);
    SetLEDs();
}

void LEDSubsystem::SetDrivetrainToColor(frc::Color color) {
    FillBuffer(color, 0, tigertronics::constants::drivetrainEndLed);
    SetLEDs();
}

void LEDSubsystem::SetIntakeToColor(frc::Color color) {
    FillBuffer(color, tigertronics::constants::drivetrainEndLed + 1, tigertronics::constants::intakeEndLed);
    SetLEDs();
}

void LEDSubsystem::SetShooterToColor(frc::Color color) {
    FillBuffer(color, tigertronics::constants::intakeEndLed + 1, tigertronics::constants::shooterEndLed);
    SetLEDs();
}

void LEDSubsystem::SetClimberToColor(frc::Color color) {
    FillBuffer(color, tigertronics::constants::shooterEndLed + 1, tigertronics::constants::climberEndLed);
    SetLEDs();
}

void LEDSubsystem::SetControlPanelToColor(frc::Color color) {
    FillBuffer(color, tigertronics::constants::climberEndLed + 1, tigertronics::constants::controlPanelEndLed);
    SetLEDs();
}

void LEDSubsystem::FillBuffer(frc::Color color, int start, int end) {
    for(int i = start; i < end; i++) {
        m_ledBuffer[i].SetRGB(color.red, color.green, color.blue);
    }
}

void LEDSubsystem::SetLEDs() {
    m_ledStrip.SetData(m_ledBuffer);
}

void LEDSubsystem::ClearBuffer() {
    for(int i = 0; i < tigertronics::constants::ledStripLength; i++) {
        m_ledBuffer[i].SetRGB(0, 0, 0);
    }
}