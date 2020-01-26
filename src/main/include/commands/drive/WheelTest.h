#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/SwerveSubsystem.h"

class WheelTest
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, WheelTest> {
 public:
  WheelTest(SwerveSubsystem* subsystem);
 private:
  SwerveSubsystem* m_subsystem;
};
