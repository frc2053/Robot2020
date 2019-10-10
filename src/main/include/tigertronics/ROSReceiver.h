#pragma once

#include <networktables/NetworkTable.h>
#include "frc/smartdashboard/Sendable.h"
#include "ROSTypes.h"

class ROSReceiver {
public: 
    static void init();
    bool ConnectToTable();
    bool DisconnectToTable();
    static rostypes::Twist GetTwist(wpi::StringRef key);
private:
    virtual ~ROSReceiver() = default;
    std::shared_ptr<nt::NetworkTable> ros_table;
};