/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/drive/TurnToAngle.h"
#include "subsystems/SwerveSubsystem.h"
#include "Constants.h"
#include "frc/XboxController.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
TurnToAngle::TurnToAngle(std::function<double()> fow, std::function<double()> strafe, units::degree_t targetAngle, SwerveSubsystem* swerveSub, std::function<bool()> override)
    : CommandHelper(frc2::PIDController(tigertronics::constants::swerveAnglekP, tigertronics::constants::swerveAnglekI, tigertronics::constants::swerveAnglekD),
                    // This should return the measurement
                    [swerveSub] { return swerveSub->GetImuYaw().to<double>(); },
                    // This should return the setpoint (can also be a constant)
                    [targetAngle] { return targetAngle.to<double>(); },
                    // This uses the output
                    [fow, strafe, swerveSub](double output) {
                      swerveSub->DriveWithJoystick(strafe(), fow(), std::clamp(output, -.4, .4), true);
                    }), controllerOverride(override) {
                      m_controller.EnableContinuousInput(-180, 180);
                      m_controller.SetTolerance(tigertronics::constants::swerveAngleTolerance);
                      AddRequirements({swerveSub});
                    }

// Returns true when the command should end.
bool TurnToAngle::IsFinished() { 
  return GetController().AtSetpoint() || controllerOverride();
}
