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

  void SetShootingOn();
  void SetShootingOff();
  void SetIndexingOn();
  void SetIndexingOff();
  
  bool DetectedBallIntake();
  bool DetectedBallFeeder();

private:
  void ConfigDashboard();

  void ConfigFunnelMotor();
  void ConfigConveyorMotor();
  void ConfigFeederMotor();

  void SetFunnelSpeed(double speed);
  void SetConveyorSpeed(double speed);
  void SetFeederSpeed(double speed);
  
  ctre::phoenix::motorcontrol::can::TalonSRX funnelMotor{tigertronics::ports::funnelMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX conveyorMotor{tigertronics::ports::conveyorMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX feederMotor{tigertronics::ports::feederMotor};

  #if defined(__FRC_ROBORIO__)
  frc::TimeOfFlight intakeDistSensor{tigertronics::ports::tofSensorIntake};
  frc::TimeOfFlight feederDistSensor{tigertronics::ports::tofSensorFeeder};
  #else
  MockToF intakeDistSensor{0};
  MockToF feederDistSensor{1};
  #endif

  bool firing = false;
  bool indexing = false;

  nt::NetworkTableEntry dashDetectedBallIntake;
  nt::NetworkTableEntry dashDetectedBallFeeder;

  int count = 0;
};
