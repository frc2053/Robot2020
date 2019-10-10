#pragma once

#include <networktables/NetworkTable.h>
#include "frc/smartdashboard/Sendable.h"

class ROSReceiver {
public: 
    static void init();
    bool ConnectToTable();
    bool DisconnectToTable();
private:
    virtual ~ROSReceiver() = default;
    std::shared_ptr<nt::NetworkTable> ros_table;
};