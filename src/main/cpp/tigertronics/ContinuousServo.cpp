#include "tigertronics/ContinuousServo.h"
#include "frc/smartdashboard/SendableRegistry.h"

ContinuousServo::ContinuousServo(int channel) : frc::PWMSpeedController(channel) {
    SetBounds(1.9, 1.89, 1.550, 1.11, 1.1);
    SetPeriodMultiplier(frc::PWMSpeedController::kPeriodMultiplier_4X);
    SetSpeed(0.0);
}
