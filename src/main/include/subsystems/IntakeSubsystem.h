#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <TimeOfFlight.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"
#include "tigertronics/MockToF.h"

class IntakeSubsystem : public frc2::SubsystemBase {
 public: 
  IntakeSubsystem();
  void Periodic();
  void SetIntakeWheelsSpeed(double speed);
  void SetConveyorBeltSpeed(double speed);
  void SetFeederWheelSpeed(double speed);
  void SetIntakeFow();
  void SetIntakeRev();
 private:
  void ConfigIntakeMotor();
  void ConfigConveyorMotor();
  void ConfigFeederMotor();
  ctre::phoenix::motorcontrol::can::TalonSRX intakeMotor{tigertronics::ports::intakeMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX conveyorMotor{tigertronics::ports::conveyorMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX feederMotor{tigertronics::ports::feederMotor};
  #if defined(__FRC_ROBORIO__)
  frc::TimeOfFlight intakeDistSensor{tigertronics::ports::tofSensorIntake};
  frc::TimeOfFlight loaderDistSensor{tigertronics::ports::tofSensorConveyor};
  #else
  MockToF intakeDistSensor{0};
  MockToF loaderDistSensor{1};
  #endif
  frc::DoubleSolenoid intakeFlopper{tigertronics::ports::TwelveVoltPCM, tigertronics::ports::intakeSolenoidPortFow, tigertronics::ports::intakeSolenoidPortRev};
  };