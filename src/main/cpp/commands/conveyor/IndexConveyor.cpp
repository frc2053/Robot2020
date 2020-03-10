/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/conveyor/IndexConveyor.h"

IndexConveyor::IndexConveyor(ConveyorSubsystem* conveyorSub) :
  m_conveyorSubsystem(conveyorSub) {
  AddRequirements(m_conveyorSubsystem);
}

void IndexConveyor::Initialize() {}

void IndexConveyor::Execute() {}

void IndexConveyor::End(bool interrupted) {}

bool IndexConveyor::IsFinished() { return false; }
