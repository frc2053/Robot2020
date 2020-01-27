/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "tigertronics/MockAHRS.h"
#include <iostream>

MockAHRS::MockAHRS() {

}

void MockAHRS::ZeroYaw() {
    std::cout << "Zeroed Mock IMU\n";
}

double MockAHRS::GetRoll() {
    return 0;
}

double MockAHRS::GetPitch() {
    return 0;
}

double MockAHRS::GetYaw() {
    return 0;
}

double MockAHRS::GetVelocityX() {
    return 0;
}

double MockAHRS::GetVelocityY() {
    return 0;
}

double MockAHRS::GetVelocityZ() {
    return 0;
}

double MockAHRS::GetWorldLinearAccelX() {
    return 0;
}

double MockAHRS::GetWorldLinearAccelY() {
    return 0;
}

double MockAHRS::GetWorldLinearAccelZ() {
    return 0;
}
