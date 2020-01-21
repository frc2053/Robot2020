/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AddressableLED.h>
#include <Constants.h>
#include <frc/util/Color.h>

class LEDSubsystem : public frc2::SubsystemBase {
 public:
  LEDSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void SetAllLEDSToColor(frc::Color color);
  void SetDrivetrainToColor(frc::Color color);
  void SetIntakeToColor(frc::Color color);
  void SetShooterToColor(frc::Color color);
  void SetClimberToColor(frc::Color color);
  void SetControlPanelToColor(frc::Color color);
 private:
  void FillBuffer(frc::Color color, int start, int end);
  void SetLEDs();
  void ClearBuffer();
  frc::AddressableLED m_ledStrip{tigertronics::ports::ledPWM};
  std::array<frc::AddressableLED::LEDData, tigertronics::constants::ledStripLength> m_ledBuffer;
};
