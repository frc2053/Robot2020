/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tigertronics/ContinuousServo.h"
#include "frc/smartdashboard/SendableRegistry.h"

ContinuousServo::ContinuousServo(int channel) : frc::PWMSpeedController(channel) {
    SetBounds(2.1, 2.102, 1.5, .9002, .9);
    SetPeriodMultiplier(frc::PWMSpeedController::kPeriodMultiplier_1X);
    SetSpeed(0.0);
    SetZeroLatch();
}
