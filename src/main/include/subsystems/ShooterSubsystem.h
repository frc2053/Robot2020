#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include "Constants.h"
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <ntcore.h>
#include "tigertronics/ContinuousServo.h"
#include "tigertronics/ShooterLookupTable.h"
#include <ctre/phoenix/CANifier.h>
#include <frc/Relay.h>
#include <frc/Encoder.h>
#include <frc/LinearFilter.h>

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();
  void Periodic();
  void SetShooterToPercentOutput(double output);
  void SetShooterToVelocity(units::revolutions_per_minute_t shaftSpeed);
  void SetHoodToAngle(units::degree_t angle);
  void SetServoSpeed(double percent);
  units::revolutions_per_minute_t GetShooterLeftRPM();
  units::revolutions_per_minute_t GetShooterRightRPM();
  units::revolutions_per_minute_t GetShooterAvgRPM();
  units::meter_t GetDistanceToTarget();
  units::degree_t GetAngleToTarget();
  LookupValue GetAngleAndRPMForGoal(units::meter_t distance);
  units::revolutions_per_minute_t GetRPMToGoTo();
  units::degree_t GetAngleToGoTo();
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
  void GetVisionData();
  units::degree_t ConvertHoodTicksToAngle(double ticks);
  ShooterLookupTable table;
  nt::NetworkTableEntry leftShooterDash;
  nt::NetworkTableEntry rightShooterDash;
  nt::NetworkTableEntry avgShooterDash;
  nt::NetworkTableEntry hoodAngleDash;
  nt::NetworkTableEntry hoodAngleSetpointDash;
  nt::NetworkTableEntry shooterSpeedSetpointDash;
  nt::NetworkTableInstance network_table;
  std::shared_ptr<nt::NetworkTable> cameraTable;
  ctre::phoenix::motorcontrol::can::TalonFX shooterMotorLeft{tigertronics::ports::shooterLeft};
  ctre::phoenix::motorcontrol::can::TalonFX shooterMotorRight{tigertronics::ports::shooterRight};
  ctre::phoenix::motorcontrol::can::TalonSRX loaderWheel{tigertronics::ports::loaderWheel};
  frc::Encoder hoodEncoder{tigertronics::ports::hoodEncoderA, tigertronics::ports::hoodEncoderB, false, frc::Encoder::EncodingType::k4X};
  ContinuousServo hoodServo{tigertronics::ports::hoodServo};
  double kFF = tigertronics::constants::shooterkF;
  double kP = tigertronics::constants::shooterkP;
  double kI = tigertronics::constants::shooterkI;
  double kD = tigertronics::constants::shooterkD;
  double visionX = 0;
  double visionY = 0;
  double visionYaw = 0;
  int ENCODER_MAX_VAL = 4000;
  double lastSetpointRpm;
  double lastSetpointAngle;
  frc2::PIDController hoodController{tigertronics::constants::hoodkP, tigertronics::constants::hoodkI, tigertronics::constants::hoodkD};
  frc::Relay m_relay{tigertronics::ports::ledRelay};
  frc::LinearFilter<double> visionFilter = frc::LinearFilter<double>::MovingAverage(10);
  bool lightOn = false;
  units::revolutions_per_minute_t rpmtogoto{0_rpm};
  units::degree_t angletogoto{0_deg};
};
