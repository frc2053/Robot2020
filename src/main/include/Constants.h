#pragma once

#include "units/units.h"
#include "frc/util/Color.h"
#include <frc/trajectory/TrapezoidProfile.h>

namespace tigertronics {
    namespace constants {
        //PHYSICAL DIMENSIONS
        static constexpr units::meter_t drivebaseLength = 22_in;
        static constexpr units::meter_t drivebaseWidth = 22_in;
        static constexpr units::meter_t driveWheelRadius = 3_in / 2;
        static constexpr double swerveDriveGearReduction = 5.33 / 1;

        //COLOR INFO
        static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
        static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
        static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
        static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

        //ENCODER INFO
        static constexpr int ctreEncoderTicksPerRev = 4096;
        static constexpr int talonFxEncoderTicksPerRev = 2048;
        static constexpr int genericEncoderRobobrio = 1024;

        //SWERVE TURNING MOTOR CONFIG
        static constexpr double swerveTurningkP = 15;
        static constexpr double swerveTurningkI = 0;
        static constexpr double swerveTurningkD = 120;
        static constexpr units::radians_per_second_t swerveTurningMaxVel = 3600_rad_per_s;
        //im too lazy to define radial acceleration right now so this is in ticks/100ms/s
        static constexpr double swerveTurningMaxAccel = 1500;
        static constexpr int swerveTurningErrorAllowance = 5;

        //SWERVE DRIVE MOTOR CONFIG
        static constexpr double swerveDrivekF = 0.000015;
        static constexpr double swerveDrivekP = 0.1;
        static constexpr double swerveDrivekI = 0.0;
        static constexpr double swerveDrivekD = 0.0;

        static constexpr double swerveAnglekP = 0.05;
        static constexpr double swerveAnglekI = 0;
        static constexpr double swerveAnglekD = 0.005;
        static constexpr double swerveAngleTolerance = 2;

        static constexpr int swerveFLCal = 993;  //483
        static constexpr int swerveFRCal = 1360;  //605 
        static constexpr int swerveBLCal = 1531; //2570
        static constexpr int swerveBRCal = 3762; //1420  


        //SHOOTER PHYSICALS
        static constexpr double shooterGearRatio = 1/2;
        static units::inch_t shooterWheelRadius = 2_in;
        static constexpr double hoodMaxTicks = 4096;
        static constexpr double hoodMaxAngle = 90;

        //SHOOTER CONFIG
        static constexpr double shooterkF = 0.000015;
        static constexpr double shooterkP = 0.00006;
        static constexpr double shooterkI = 0.000001;
        static constexpr double shooterkD = 0;

        static constexpr double hoodkP = .1;
        static constexpr double hoodkI = 0;
        static constexpr double hoodkD = 0;

        static constexpr int hoodPIDTolerance = 2;

        //PATH FOLLOWING CONSTS
        static constexpr double pathFollowingkP = 0.00158;
        static constexpr double pathFollowingkI = 0;
        static constexpr double pathFollowingkD = 0;


        //INTAKE
        static constexpr double highPassConst = 0.05;
        static constexpr units::millimeter_t distThreshold = 25.4_mm;

        static const frc::TrapezoidProfile<units::radians>::Constraints kThetaControllerConstraints;
    }

    namespace ports {
        //PCM CAN
        static constexpr int TwentyFourVoltPCM = 1;
        static constexpr int TwelveVoltPCM = 0;

        //SWERVE PORTS
        static constexpr int swerveFLDrive = 2;
        static constexpr int swerveFRDrive = 3;
        static constexpr int swerveBLDrive = 4;
        static constexpr int swerveBRDrive = 5;
        static constexpr int swerveFLTurn = 6;
        static constexpr int swerveFRTurn = 7;
        static constexpr int swerveBLTurn = 8;
        static constexpr int swerveBRTurn = 9;

        //SHOOTER PORTS
        static constexpr int shooterLeft = 10;
        static constexpr int shooterRight = 11;
        static constexpr int loaderWheel = 12;
        static constexpr int hoodServo = 2;
        static constexpr int hoodEncoderA = 1;
        static constexpr int hoodEncoderB = 2;

        //INTAKE PORTS
        static constexpr int intakeMotor = 13;
        static constexpr int conveyorMotor = 14;
        static constexpr int feederMotor = 15;
        static constexpr int funnelMotor = 16;
        static constexpr int tofSensorIntake = 0;
        static constexpr int tofSensorConveyor = 1;
        static constexpr int intakeSolenoidPortFow = 2;
        static constexpr int intakeSolenoidPortRev = 5;

        //CLIMBER PORTS
        static constexpr int climberPTOPortFow = 0;
        static constexpr int climberPTOPortRev = 5;
        static constexpr int climberBrakePortFow = 6;
        static constexpr int climberBrakePortRev = 7;
        static constexpr int climberElevatorSolenoidPortFow = 3;
        static constexpr int climberElevatorSolenoidPortRev = 4;

        //CONTROL PANEL
        static constexpr int controlPanel = 19;

        //LEDs
        static constexpr int ledRelay = 0;
    }
}