#include "commands/drive/TurnToAngle.h"
#include "subsystems/SwerveSubsystem.h"
#include "Constants.h"
#include <frc/XboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
TurnToAngle::TurnToAngle(std::function<double()> fow, std::function<double()> strafe, std::function<double()> targetAngle, SwerveSubsystem* swerveSub, std::function<bool()> override)
    : CommandHelper(frc2::PIDController(tigertronics::constants::swerveAnglekP, tigertronics::constants::swerveAnglekI, tigertronics::constants::swerveAnglekD),
                    // This should return the measurement
                    [swerveSub] { return swerveSub->GetImuYaw().to<double>(); },
                    // This should return the setpoint (can also be a constant)
                    targetAngle,
                    // This uses the output
                    [fow, strafe, swerveSub](double output) {
                      swerveSub->DriveWithJoystick(strafe(), fow(), -std::clamp(output, -.4, .4), true);
                    }), controllerOverride(override) {
                      m_controller.EnableContinuousInput(-180, 180);
                      m_controller.SetTolerance(tigertronics::constants::swerveAngleTolerance);
                      AddRequirements({swerveSub});
                    }

// Returns true when the command should end.
bool TurnToAngle::IsFinished() {
  std::cout << "currentAngle: " << m_controller.GetSetpoint() << "\n";
  std::cout << "error: " << m_controller.GetPositionError() << "\n";
  if(frc::DriverStation::GetInstance().IsAutonomous()) {
    return m_controller.AtSetpoint() || controllerOverride();
  }
  else {
    return controllerOverride();
  }
}
