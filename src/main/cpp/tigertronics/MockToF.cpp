#include "tigertronics/MockToF.h"
#include <iostream>

MockToF::MockToF(int port) {
    portNum = port;
    currentMode = RangingMode::kMedium;
    tlX = 0;
    tlY = 0;
    brX = 1;
    brY = 1;
}

void MockToF::IdentifySensor() {
    std::cout << "I AM TOF SENSOR " << portNum << "\n";
}

int MockToF::GetFirmwareVersion() const {
    return 420;
}

int MockToF::GetSerialNumber() const {
    return 420;
}

bool MockToF::IsRangeValid() const {
    return true;
}

double MockToF::GetRange() const {
    return 12.5;
}

double MockToF::GetRangeSigma() const {
    return 0.1;
}

double MockToF::GetAmbientLightLevel() const {
    return 0.25;
}

MockToF::Status MockToF::GetStatus() const {
    return MockToF::Status::kValid;
}

void MockToF::SetRangingMode(MockToF::RangingMode mode) {
    currentMode = mode;
}

void MockToF::SetRangeOfInterest(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
    tlX = topLeftX;
    tlY = topLeftY;
    brX = bottomRightX;
    brY = bottomRightY;
}