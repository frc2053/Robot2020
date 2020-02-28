#pragma once

class MockAHRS {
 public:
  MockAHRS();
  void ZeroYaw();
  double GetRoll();
  double GetPitch();
  double GetYaw();
  double GetVelocityX();
  double GetVelocityY();
  double GetVelocityZ();
  double GetWorldLinearAccelX();
  double GetWorldLinearAccelY();
  double GetWorldLinearAccelZ();
};
