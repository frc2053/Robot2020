/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/PWMSpeedController.h>

class ContinuousServo : public frc::PWMSpeedController {
 public:
  explicit ContinuousServo(int channel);
  ContinuousServo(ContinuousServo&&) = default;
  ContinuousServo& operator=(ContinuousServo&&) = default;
};
