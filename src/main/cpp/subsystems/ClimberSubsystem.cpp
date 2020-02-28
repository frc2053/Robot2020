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

void ClimberSubsystem::Periodic() {}
