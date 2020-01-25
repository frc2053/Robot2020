#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/ControlPanelSubsystem.h"
#include <frc/util/Color.h>

class RotationControl
    : public frc2::CommandHelper<frc2::CommandBase, RotationControl> { 
        public:
        explicit RotationControl(ControlPanelSubsystem* subsystem);

        void Initialize() override;

        void Execute() override;

        void End(bool interrupted) override;

        bool IsFinished() override;

        private:
        ControlPanelSubsystem* controlPanelSubsystem;
        frc::Color colorSensed;
        frc::Color previousColor;
        bool isDone;
        int counter;
    };