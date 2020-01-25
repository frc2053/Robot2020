#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/ControlPanelSubsystem.h"
#include <frc/util/Color.h>

class PositionControl
    : public frc2::CommandHelper<frc2::CommandBase, PositionControl> { 
        public:
        explicit PositionControl(ControlPanelSubsystem* subsystem);

        void Initialize() override;

        void Execute() override;

        void End(bool interrupted) override;

        bool IsFinished() override;

        private:
        ControlPanelSubsystem* controlPanelSubsystem;
        frc::Color currentColor;
        frc::Color colorGoal;
        bool isDone;
    };

