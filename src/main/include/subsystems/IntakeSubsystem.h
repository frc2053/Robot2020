#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <TimeOfFlight.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"
#include "tigertronics/MockToF.h"
#include <frc/LinearFilter.h>
#include <frc/Timer.h>
class IntakeSubsystem : public frc2::SubsystemBase {
 public: 
  IntakeSubsystem();
  void Periodic();
  void SetIntakeWheelsSpeed(double speed);
  void SetFeederWheelSpeed(double speed);
  void SetFunnelWheelSpeed(double speed);
  void SetIntakeFow();
  void SetIntakeRev();

 private:
  void ConfigIntakeMotor();
  void ConfigFeederMotor();
  void ConfigFunnelMotor();

  ctre::phoenix::motorcontrol::can::TalonSRX intakeMotor{tigertronics::ports::intakeMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX feederMotor{tigertronics::ports::feederMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX funnelMotor{tigertronics::ports::funnelMotor};

  frc::DoubleSolenoid intakeFlopper{tigertronics::ports::TwelveVoltPCM, tigertronics::ports::intakeSolenoidPortFow, tigertronics::ports::intakeSolenoidPortRev};
};