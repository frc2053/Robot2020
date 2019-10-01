#pragma once

#include "units/units.h"

namespace tigertronics {
    namespace constants {
        //PHYSICAL DIMENSIONS
        static constexpr units::meter_t driveWheelRadius = 2.5_in / 2;


        //ENCODER INFO
        static constexpr int ctreEncoderTicksPerRev = 4096;
    }
}