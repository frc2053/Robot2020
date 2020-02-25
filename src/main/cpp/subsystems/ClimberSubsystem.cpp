/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimberSubsystem.h"

ClimberSubsystem::ClimberSubsystem() {
    SetName("Climber Subsystem");
}

void ClimberSubsystem::SetPTO(frc::DoubleSolenoid::Value state) {
    climbPTO.Set(state);
}

void ClimberSubsystem::SetBrake(frc::DoubleSolenoid::Value state) {
    climbBrake.Set(state);
}

void ClimberSubsystem::SetElevator(frc::DoubleSolenoid::Value state) {
    climbElevator.Set(state);
}

// This method will be called once per scheduler run
void ClimberSubsystem::Periodic() {}
