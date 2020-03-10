/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/conveyor/IndexConveyor.h"
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/WaitCommand.h>
#include "commands/conveyor/SetConveyorSpeed.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
IndexConveyor::IndexConveyor(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
  AddCommands (
    SetConveyorSpeed(m_conveyorSubsystem, 0),
    frc2::WaitUntilCommand([this](){ return m_conveyorSubsystem->DetectedBallIn(); }),
    SetConveyorSpeed(m_conveyorSubsystem, indexingSpeed),
    frc2::WaitUntilCommand([this](){ return !m_conveyorSubsystem->DetectedBallIn(); }),
    //This is to make sure the balls dont get jammed together
    frc2::WaitCommand(ballUnjamTime),
    SetConveyorSpeed(m_conveyorSubsystem, 0)
  );
}
