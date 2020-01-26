#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include "Constants.h"

class IntakeSubsystem : public frc2::SubsystemBase {
 public: 
  IntakeSubsystem();
  void Periodic();
  void SetIntakeWheelsSpeed(double speed);
  void SetConveyorBeltSpeed(double speed);
  void SetFeederWheelSpeed(double speed);
 private:
  void ConfigIntakeMotor();
  void ConfigConveyorMotor();
  void ConfigFeederMotor();
  ctre::phoenix::motorcontrol::can::TalonSRX intakeMotor{tigertronics::ports::intakeMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX conveyorMotor{tigertronics::ports::conveyorMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX feederMotor{tigertronics::ports::feederMotor};
  };