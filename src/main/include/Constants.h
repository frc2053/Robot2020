#pragma once

#include "units/units.h"

namespace tigertronics {
    namespace constants {
        //PHYSICAL DIMENSIONS
        constexpr units::meter_t driveWheelRadius = 2.5_in / 2;


        //ENCODER INFO
        constexpr int ctreEncoderTicksPerRev = 4096;
    }
}