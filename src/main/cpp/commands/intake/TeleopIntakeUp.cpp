#include "commands/intake/TeleopIntakeUp.h"
#include "commands/intake/IntakeUp.h"
#include "commands/intake/SetIntakeSpeed.h"
#include "commands/intake/SetConveyorSpeed.h"
#include <frc2/command/WaitUntilCommand.h>

TeleopIntakeUp::TeleopIntakeUp(IntakeSubsystem* intakeSub) : m_intakeSubsystem(intakeSub) {
  AddCommands(
    IntakeUp(m_intakeSubsystem)
  );
}
