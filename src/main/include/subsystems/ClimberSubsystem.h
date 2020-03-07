#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"

class ClimberSubsystem : public frc2::SubsystemBase {
 public:
  ClimberSubsystem();
  void Periodic();
  void SetPTO(frc::DoubleSolenoid::Value state);
  void SetBrake(frc::DoubleSolenoid::Value state);
  void SetElevator(frc::DoubleSolenoid::Value state);
 private:
  
  frc::DoubleSolenoid climbPTO{tigertronics::ports::TwentyFourVoltPCM, tigertronics::ports::climberPTOPortFow, tigertronics::ports::climberPTOPortRev};
  frc::DoubleSolenoid climbBrake{tigertronics::ports::TwentyFourVoltPCM, tigertronics::ports::climberBrakePortFow, tigertronics::ports::climberBrakePortRev};
  frc::DoubleSolenoid climbElevator{tigertronics::ports::TwentyFourVoltPCM, tigertronics::ports::climberElevatorSolenoidPortFow, tigertronics::ports::climberElevatorSolenoidPortRev};
};
