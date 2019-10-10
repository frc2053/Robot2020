#include "tigertronics/ROSReceiver.h"

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "frc/smartdashboard/SendableBuilderImpl.h"

class ROSData {
public:
    ROSData() = default;
    explicit ROSData(frc::Sendable* sendable_) : sendable(sendable_) {}
    frc::Sendable* sendable = nullptr;
    frc::SendableBuilderImpl builder;
};

class Singleton {
public:
    static Singleton& GetInstance();
    std::shared_ptr<nt::NetworkTable> table;
    wpi::StringMap<ROSData> tablesToData;
    wpi::mutex tablesToDataMutex;
private:
    Singleton() {
        table = nt::NetworkTableInstance::GetDefault().GetTable("ROS");
    }
    Singleton(const Singleton&) = default;
    Singleton& operator=(const Singleton&) = default;
};

Singleton& Singleton::GetInstance() {
    static Singleton instance;
    return instance;
}

void ROSReceiver::init() {
    Singleton::GetInstance();
}