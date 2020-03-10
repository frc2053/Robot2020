/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <units/units.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <TimeOfFlight.h>
#include <frc/LinearFilter.h>
#include "Constants.h"
#include "tigertronics/MockToF.h"

class ConveyorSubsystem : public frc2::SubsystemBase {
public:
  ConveyorSubsystem();
  void Periodic();
  void SetConveyorBeltSpeed(double speed);
  void SetNumOfBalls(int balls);
  int GetNumOfBalls();
  units::millimeter_t GetIntakeDistFiltered();
  units::millimeter_t GetLoaderDistFiltered();
  bool DetectedBallIn();
  bool DetectedBallOut();
private:
  void ConfigConveyorMotor();
  void ConfigDashboard();
  int numOfBalls = 0;
  ctre::phoenix::motorcontrol::can::TalonSRX conveyorMotor{tigertronics::ports::conveyorMotor};

  #if defined(__FRC_ROBORIO__)
  frc::TimeOfFlight intakeDistSensor{tigertronics::ports::tofSensorIntake};
  frc::TimeOfFlight loaderDistSensor{tigertronics::ports::tofSensorConveyor};
  #else
  MockToF intakeDistSensor{0};
  MockToF loaderDistSensor{1};
  #endif

  frc::LinearFilter<double> intakeHighFilter = frc::LinearFilter<double>::HighPass(tigertronics::constants::highPassConst, 0.02_s);
  frc::LinearFilter<double> loaderHighFilter = frc::LinearFilter<double>::HighPass(tigertronics::constants::highPassConst, 0.02_s);
  frc::LinearFilter<double> intakeLowFilter = frc::LinearFilter<double>::SinglePoleIIR(tigertronics::constants::highPassConst, 0.02_s);
  frc::LinearFilter<double> loaderLowFilter = frc::LinearFilter<double>::SinglePoleIIR(tigertronics::constants::highPassConst, 0.02_s);

  bool detectedIntake = false;
  bool detectedLoader = false;
  units::millimeter_t intakeDistFiltered = 0_mm;
  units::millimeter_t loaderDistFiltered = 0_mm;

  nt::NetworkTableEntry dashNumOfBalls;
  nt::NetworkTableEntry dashDetectedBallIn;
  nt::NetworkTableEntry dashDetectedBallOut;
  nt::NetworkTableEntry dashRawLoaderDist;
  nt::NetworkTableEntry dashRawIntakeDist;
  nt::NetworkTableEntry dashFilteredLoaderDist;
  nt::NetworkTableEntry dashFilteredIntakeDist;
};
