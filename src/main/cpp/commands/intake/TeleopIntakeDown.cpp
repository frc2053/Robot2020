#include "commands/intake/TeleopIntakeDown.h"
#include "commands/intake/IntakeDown.h"
#include "commands/intake/SetIntakeSpeed.h"
#include "commands/intake/SetConveyorSpeed.h"
#include "commands/intake/SetLoaderWheelSpeed.h"

TeleopIntakeDown::TeleopIntakeDown(IntakeSubsystem* intakeSub) : m_intakeSubsystem(intakeSub) {
  AddCommands(
    IntakeDown(m_intakeSubsystem)
  );
}
