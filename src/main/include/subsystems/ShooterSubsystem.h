/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include "Constants.h"
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <ntcore.h>
#include <frc/Servo.h>

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();
  void Periodic();
  void SetShooterToPercentOutput(double output);
  void SetShooterToVelocity(units::revolutions_per_minute_t shaftSpeed);
  void SetHoodToAngle(double angle);
  units::revolutions_per_minute_t GetShooterLeftRPM();
  units::revolutions_per_minute_t GetShooterRightRPM();
  units::revolutions_per_minute_t GetShooterAvgRPM();
 private:
  void ConfigureShooterMotors();
  void ConfigureLoaderMotor();
  void ConfigureHood();
  void ConfigureDashboard();
  units::revolutions_per_minute_t ConvertTickVelToRPM(int ticksPer100ms);
  int ConvertRPMToTickVel(units::revolutions_per_minute_t rpm);
  nt::NetworkTableEntry leftShooterDash;
  nt::NetworkTableEntry rightShooterDash;
  nt::NetworkTableEntry avgShooterDash;
  nt::NetworkTableEntry hoodAngleDash;
  nt::NetworkTableEntry hoodAngleSetpointDash;
  nt::NetworkTableEntry shooterSpeedSetpointDash;
  ctre::phoenix::motorcontrol::can::TalonFX shooterMotorLeft{tigertronics::ports::shooterLeft};
  ctre::phoenix::motorcontrol::can::TalonFX shooterMotorRight{tigertronics::ports::shooterRight};
  ctre::phoenix::motorcontrol::can::TalonSRX loaderWheel{tigertronics::ports::loaderWheel};
  frc::Servo hoodServo{tigertronics::ports::hoodServo};
  double kFF = tigertronics::constants::shooterkF;
  double kP = tigertronics::constants::shooterkP;
  double kI = tigertronics::constants::shooterkI;
  double kD = tigertronics::constants::shooterkD;
};
