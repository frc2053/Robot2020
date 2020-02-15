#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include "Constants.h"
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <ntcore.h>
#include "tigertronics/ContinuousServo.h"
#include "tigertronics/ShooterLookupTable.h"
#include <ctre/phoenix/CANifier.h>

class ShooterSubsystem : public frc2::PIDSubsystem {
 public:
  ShooterSubsystem();
  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  void Periodic();
  void SetShooterToPercentOutput(double output);
  void SetShooterToVelocity(units::revolutions_per_minute_t shaftSpeed);
  void SetHoodToAngle(units::degree_t angle);
  void SetServoSpeed(double percent);
  units::revolutions_per_minute_t GetShooterLeftRPM();
  units::revolutions_per_minute_t GetShooterRightRPM();
  units::revolutions_per_minute_t GetShooterAvgRPM();
 private:
  void ConfigureShooterMotors();
  void ConfigureLoaderMotor();
  void ConfigureHood();
  void ConfigureDashboard();
  void SetupLookupTable();
  units::degree_t GetHoodAngle();
  units::revolutions_per_minute_t ConvertTickVelToRPM(int ticksPer100ms);
  int ConvertRPMToTickVel(units::revolutions_per_minute_t rpm);
  int ConvertHoodAngleToTicks(units::degree_t angle);
  units::degree_t ConvertHoodTicksToAngle(double ticks);
  ShooterLookupTable table;
  nt::NetworkTableEntry leftShooterDash;
  nt::NetworkTableEntry rightShooterDash;
  nt::NetworkTableEntry avgShooterDash;
  nt::NetworkTableEntry hoodAngleDash;
  nt::NetworkTableEntry hoodAngleSetpointDash;
  nt::NetworkTableEntry shooterSpeedSetpointDash;
  ctre::phoenix::motorcontrol::can::TalonFX shooterMotorLeft{tigertronics::ports::shooterLeft};
  ctre::phoenix::motorcontrol::can::TalonFX shooterMotorRight{tigertronics::ports::shooterRight};
  ctre::phoenix::motorcontrol::can::TalonSRX loaderWheel{tigertronics::ports::loaderWheel};
  ContinuousServo hoodServo{tigertronics::ports::hoodServo};
  ctre::phoenix::CANifier hoodEncoder{tigertronics::ports::canifier};
  double kFF = tigertronics::constants::shooterkF;
  double kP = tigertronics::constants::shooterkP;
  double kI = tigertronics::constants::shooterkI;
  double kD = tigertronics::constants::shooterkD;
  int ENCODER_MAX_VAL = 16585;
};
