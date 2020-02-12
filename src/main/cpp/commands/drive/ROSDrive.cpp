#include "commands/drive/ROSDrive.h"

ROSDrive::ROSDrive(SwerveSubsystem* subsystem) : m_subsystem{subsystem} {
  AddRequirements({m_subsystem});
}

void ROSDrive::Initialize() {}

void ROSDrive::Execute() {
  std::shared_ptr<RosTypes::Twist> twist = m_subsystem->GetTwist();
  m_subsystem->DriveWithRos(units::meters_per_second_t(twist->linear.x), units::meters_per_second_t(twist->linear.y), units::radians_per_second_t(twist->angular.z));
}

void ROSDrive::End(bool interrupted) {}

bool ROSDrive::IsFinished() { return false; }
