#include "subsystems/ShooterSubsystem.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>
#include <algorithm>
#include "tigertronics/Util.h"
#include <frc/smartdashboard/SmartDashboard.h>
ShooterSubsystem::ShooterSubsystem() {
    SetName("Shooter Subsystem");
    ConfigureLoaderMotor();
    ConfigureShooterMotors();
    ConfigureDashboard();
    ConfigureHood();
    SetupLookupTable();
    frc::SmartDashboard::PutBoolean("Light On/Off", lightOn);
    network_table = nt::NetworkTableInstance::GetDefault();
    cameraTable = network_table.GetTable("chameleon-vision")->GetSubTable("USB Camera-B4.09.24.1");

}

void ShooterSubsystem::ConfigureDashboard() {
    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Shooter Subsystem");
    leftShooterDash = tab.Add("Left Motor Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    rightShooterDash = tab.Add("Right Motor Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    avgShooterDash = tab.Add("Average Motor Velocity", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithSize(2,2).GetEntry();
    hoodAngleDash = tab.Add("Hood Angle", 0).WithWidget(frc::BuiltInWidgets::kDial).WithSize(2,2).GetEntry();
    //shooterSpeedSetpointDash = tab.Add("Shooter Setpoint", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithSize(2, 1).GetEntry();
    //hoodAngleSetpointDash = tab.Add("Hood Angle Setpoint", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithSize(2,1 ).GetEntry();
    hoodEncoder.SetSamplesToAverage(50);
    hoodEncoder.SetMinRate(1.0);
    hoodEncoder.SetDistancePerPulse(1);
    hoodEncoder.SetReverseDirection(true);
}

void ShooterSubsystem::SetupLookupTable() {
    //ADD MORE AS NEEDED
    table.AddLookupValue(0_ft, LookupValue{ 2000_rpm, 10_deg });
    table.AddLookupValue(1_ft, LookupValue{ 2500_rpm, 20_deg });
    table.AddLookupValue(2_ft, LookupValue{ 2000_rpm, 20_deg });
    table.AddLookupValue(3_ft, LookupValue{ 2300_rpm, 39_deg });
    table.AddLookupValue(4_ft, LookupValue{ 2400_rpm, 45_deg });
    table.AddLookupValue(5_ft, LookupValue{ 2400_rpm, 49_deg });
    table.AddLookupValue(6_ft, LookupValue{ 2400_rpm, 55_deg });
    table.AddLookupValue(7_ft, LookupValue{ 2400_rpm, 55_deg });
    table.AddLookupValue(8_ft, LookupValue{ 2600_rpm, 58_deg });
    table.AddLookupValue(9_ft, LookupValue{ 2600_rpm, 58_deg });
    table.AddLookupValue(10_ft, LookupValue{ 2700_rpm, 61_deg });
    table.AddLookupValue(11_ft, LookupValue{ 2800_rpm, 62_deg });
    table.AddLookupValue(12_ft, LookupValue{ 2800_rpm, 62_deg });
    table.AddLookupValue(13_ft, LookupValue{ 3400_rpm, 72_deg });
    table.AddLookupValue(14_ft, LookupValue{ 3700_rpm, 71_deg });
    table.AddLookupValue(15_ft, LookupValue{ 3800_rpm, 72_deg });
    table.AddLookupValue(16_ft, LookupValue{ 3800_rpm, 72_deg });
    table.AddLookupValue(17_ft, LookupValue{ 4400_rpm, 71_deg });
    table.AddLookupValue(18_ft, LookupValue{ 4600_rpm, 72_deg });
    table.AddLookupValue(19_ft, LookupValue{ 5000_rpm, 70_deg });
    table.AddLookupValue(20_ft, LookupValue{ 5000_rpm, 70_deg });
    table.AddLookupValue(21_ft, LookupValue{ 5700_rpm, 72_deg });
}

void ShooterSubsystem::ConfigureShooterMotors() {
    shooterMotorLeft.ConfigFactoryDefault();
    shooterMotorRight.ConfigFactoryDefault();

    shooterMotorRight.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor);
    shooterMotorRight.Config_kF(0, kFF);
    shooterMotorRight.Config_kP(0, kP);
    shooterMotorRight.Config_kI(0, kP);
    shooterMotorRight.Config_kD(0, kP);

    shooterMotorRight.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Coast);
    shooterMotorRight.SetInverted(true);

    shooterMotorLeft.Follow(shooterMotorRight);
    shooterMotorLeft.SetInverted(false);

    shooterMotorLeft.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    shooterMotorLeft.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);

    //incase we plug in a bad talon
    shooterMotorRight.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    shooterMotorRight.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ShooterSubsystem::ConfigureLoaderMotor() {
    loaderWheel.ConfigFactoryDefault();

    //incase we plug in a bad talon
    loaderWheel.ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
    loaderWheel.ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled, 10);
}

void ShooterSubsystem::ConfigureHood() {
    SetServoSpeed(0);
    hoodController.SetTolerance(tigertronics::constants::hoodPIDTolerance);
}

void ShooterSubsystem::SetShooterToVelocity(units::revolutions_per_minute_t shaftSpeed) {
    std::cout << "SETTING SHOOTER VEL TO: " << shaftSpeed.to<double>() << "\n";
    shooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, ConvertRPMToTickVel(shaftSpeed));
}

void ShooterSubsystem::SetShooterToPercentOutput(double percent){
    shooterMotorRight.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, percent);
}

void ShooterSubsystem::SetServoSpeed(double percent) {
    hoodServo.Set(std::clamp(percent, -1.0, 1.0));
}

units::degree_t ShooterSubsystem::GetHoodAngle() {
    return units::degree_t(Util::map(hoodEncoder.Get(), 0, ENCODER_MAX_VAL, 0, 90));
}

void ShooterSubsystem::SetHoodToAngle(units::degree_t angle){
    std::cout << "SETTING HOOD ANGLE TO: " << angle.to<double>() << "\n";
    hoodController.SetSetpoint(angle.to<double>());
}

LookupValue ShooterSubsystem::GetAngleAndRPMForGoal(units::meter_t distance) {
    return table.Get(distance);
}

units::revolutions_per_minute_t ShooterSubsystem::GetShooterLeftRPM() {
    return ConvertTickVelToRPM(shooterMotorLeft.GetSelectedSensorVelocity());
}

units::revolutions_per_minute_t ShooterSubsystem::GetShooterRightRPM() {
    return ConvertTickVelToRPM(shooterMotorRight.GetSelectedSensorVelocity());
}

units::revolutions_per_minute_t ShooterSubsystem::GetShooterAvgRPM() {
    return (GetShooterLeftRPM() + GetShooterRightRPM()) / 2;
}

units::revolutions_per_minute_t ShooterSubsystem::ConvertTickVelToRPM(int ticksPer100ms) {
    return units::revolutions_per_minute_t((ticksPer100ms * 600) / (tigertronics::constants::talonFxEncoderTicksPerRev));
}

int ShooterSubsystem::ConvertRPMToTickVel(units::revolutions_per_minute_t rpm) {
    return (rpm.value()  / 600) * (tigertronics::constants::talonFxEncoderTicksPerRev);
}

int ShooterSubsystem::ConvertHoodAngleToTicks(units::degree_t angle) {
    return Util::map(angle.to<double>(), 0, tigertronics::constants::hoodMaxAngle, 0, tigertronics::constants::hoodMaxTicks);
}

units::degree_t ShooterSubsystem::ConvertHoodTicksToAngle(double ticks) {
    return units::degree_t(Util::map(ticks, 0, tigertronics::constants::hoodMaxTicks, 0, tigertronics::constants::hoodMaxAngle));
}

units::meter_t ShooterSubsystem::GetDistanceToTarget() {
    return units::meter_t(visionX);
}

units::degree_t ShooterSubsystem::GetAngleToTarget() {
    return units::degree_t(visionYaw);
}

void ShooterSubsystem::GetVisionData() {
    std::vector<double> defaultVals;
    defaultVals.push_back(0);
    defaultVals.push_back(0);
    defaultVals.push_back(0);
    std::vector<double> targetPose = cameraTable->GetNumberArray("targetPose", defaultVals);
    double targetYaw = cameraTable->GetNumber("targetYaw", 0);
    visionX = targetPose[0];
    visionY = targetPose[1];
    visionYaw = visionFilter.Calculate(targetYaw);
}

units::degree_t ShooterSubsystem::GetAngleToGoTo() {
    return units::degree_t(angletogoto);
}

units::revolutions_per_minute_t ShooterSubsystem::GetRPMToGoTo() {
    return rpmtogoto;
}

void ShooterSubsystem::Periodic() {
    GetVisionData();
    double pidoutputhood = hoodController.Calculate(GetHoodAngle().to<double>());
    SetServoSpeed(pidoutputhood);
    leftShooterDash.SetDouble(GetShooterLeftRPM().value());
    rightShooterDash.SetDouble(GetShooterRightRPM().value());
    avgShooterDash.SetDouble(GetShooterAvgRPM().value());
    hoodAngleDash.SetDouble(GetHoodAngle().to<double>());
    double shufflesetpointrpm = shooterSpeedSetpointDash.GetDouble(0);
    double shufflesetpointangle = hoodAngleSetpointDash.GetDouble(0);
    frc::SmartDashboard::PutNumber("hood raw", hoodEncoder.Get());
    frc::SmartDashboard::PutNumber("distance to goal", GetDistanceToTarget().to<double>());
    //SetShooterToVelocity(units::revolutions_per_minute_t(shufflesetpointrpm));
    //SetHoodToAngle(units::degree_t(shufflesetpointangle));
    if(hoodEncoder.Get() >= 3950) {
        SetServoSpeed(0);
        //hoodEncoder.Set(15635);
    }
    if(hoodEncoder.Get() <= 0){
        SetServoSpeed(0);
        //hoodEncoder.SetQuadraturePosition(-40);
    }
    if(hoodServo.Get() > .1) {
        if(hoodEncoder.GetRate() <= 1) {
            SetServoSpeed(0);
            std::cout << "Servo stalled!\n";
        }
    }
    // Turning LED on/off from SmartDashboard
    lightOn = frc::SmartDashboard::GetBoolean("Light On/Off", false);
    if(lightOn) {
      m_relay.Set(frc::Relay::kOn);
    }
    else {
      m_relay.Set(frc::Relay::kOff);
    }

    LookupValue val = table.Get(GetDistanceToTarget());
    angletogoto = val.angle;
    rpmtogoto = val.rpm;
    frc::SmartDashboard::PutNumber("Angle Setpoint", angletogoto.to<double>());
    frc::SmartDashboard::PutNumber("Rpm Setpoint", rpmtogoto.to<double>());
}
