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
  
  void SetIntakeOn();
  void SetIntakeOff();
  void SetIntakeDown();
  void SetIntakeUp();

 private:
  void ConfigIntakeMotor();

  void SetIntakeWheelsSpeed(double speed);

  void SetIntakeFow();
  void SetIntakeRev();

  bool intakeDown = false;
  bool intakeOn = false;

  ctre::phoenix::motorcontrol::can::TalonSRX intakeMotor{tigertronics::ports::intakeMotor};

  frc::DoubleSolenoid intakeFlopper{tigertronics::ports::TwelveVoltPCM, tigertronics::ports::intakeSolenoidPortFow, tigertronics::ports::intakeSolenoidPortRev};
};