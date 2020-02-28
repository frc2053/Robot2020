#pragma once

#include <frc/PWMSpeedController.h>

class ContinuousServo : public frc::PWMSpeedController {
 public:
  explicit ContinuousServo(int channel);
  ContinuousServo(ContinuousServo&&) = default;
  ContinuousServo& operator=(ContinuousServo&&) = default;
};
