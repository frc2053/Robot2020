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
  void SetOverride(bool isOverride);
  void SetIndexing(bool isIndexing);
  void SetFiring(bool isFiring);

  void SetIntakeWheelsOverrideSpeed(double speed);
  void SetConveyorBeltOverrideSpeed(double speed);
  void SetFeederWheelOverrideSpeed(double speed);
  void SetFunnelWheelOverrideSpeed(double speed);
  void SetIntakeFow();
  void SetIntakeRev();
  
  void SetNumOfBalls(int balls);
  int GetNumOfBalls();
  units::millimeter_t GetIntakeDistFiltered();
  units::millimeter_t GetLoaderDistFiltered();
 private:
  void ConfigIntakeMotor();
  void ConfigConveyorMotor();
  void ConfigFeederMotor();
  void ConfigFunnelMotor();
  void ConfigDashboard();
  bool DetectedBallIn();
  bool DetectedBallOut();

  int numOfBalls = 0;

  bool override = false;
  bool indexing = true;
  bool firing = false;
  bool intakeDown = false;

  double intakeOverrideSpeed = 0;
  double intakeIndexSpeed = 1.0;
  double intakeFiringSpeed = 0.0;

  double funnelOverrideSpeed = 0;
  double funnelIndexSpeed = 0.5;
  double funnelFiringSpeed = 1;

  double conveyorOverrideSpeed = 0;
  double conveyorIndexSpeed = 0.3;
  double conveyorFiringSpeed = 1.0;

  double feederOverrideSpeed = 0;
  double feederIndexSpeed = 0.0;
  double feederFiringSpeed = 1.0;

  ctre::phoenix::motorcontrol::can::TalonSRX intakeMotor{tigertronics::ports::intakeMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX conveyorMotor{tigertronics::ports::conveyorMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX feederMotor{tigertronics::ports::feederMotor};
  ctre::phoenix::motorcontrol::can::TalonSRX funnelMotor{tigertronics::ports::funnelMotor};
  #if defined(__FRC_ROBORIO__)
  frc::TimeOfFlight intakeDistSensor{tigertronics::ports::tofSensorIntake};
  frc::TimeOfFlight loaderDistSensor{tigertronics::ports::tofSensorConveyor};
  #else
  MockToF intakeDistSensor{0};
  MockToF loaderDistSensor{1};
  #endif
  frc::LinearFilter<double> intakeHighFilter = frc::LinearFilter<double>::HighPass(tigertronics::constants::highPassConst, 0.02_s);
  frc::LinearFilter<double> loaderHighFilter = frc::LinearFilter<double>::HighPass(tigertronics::constants::highPassConst, 0.02_s);
  frc::LinearFilter<double> intakeLowFilter = frc::LinearFilter<double>::SinglePoleIIR(tigertronics::constants::highPassConst, 0.02_s);
  frc::LinearFilter<double> loaderLowFilter = frc::LinearFilter<double>::SinglePoleIIR(tigertronics::constants::highPassConst, 0.02_s);
  bool detectedIntake = false;
  bool detectedLoader = false;
  units::millimeter_t intakeDistFiltered = 0_mm;
  units::millimeter_t loaderDistFiltered = 0_mm;
  frc::DoubleSolenoid intakeFlopper{tigertronics::ports::TwelveVoltPCM, tigertronics::ports::intakeSolenoidPortFow, tigertronics::ports::intakeSolenoidPortRev};
  nt::NetworkTableEntry dashNumOfBalls;
  nt::NetworkTableEntry dashDetectedBallIn;
  nt::NetworkTableEntry dashDetectedBallOut;
  nt::NetworkTableEntry dashRawLoaderDist;
  nt::NetworkTableEntry dashRawIntakeDist;
  nt::NetworkTableEntry dashFilteredLoaderDist;
  nt::NetworkTableEntry dashFilteredIntakeDist;
  };