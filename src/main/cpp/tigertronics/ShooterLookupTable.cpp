#include "tigertronics/ShooterLookupTable.h"

ShooterLookupTable::ShooterLookupTable() {

}

void ShooterLookupTable::AddLookupValue(units::meter_t distance, LookupValue val) {
    table.insert({ distance, val });
}

void ShooterLookupTable::RemoveLookupValue(units::meter_t distance) {
    auto it = table.find(distance);
    table.erase(it);
}

LookupValue ShooterLookupTable::Get(units::meter_t distance) {
    return Interpolate(distance);
}

LookupValue ShooterLookupTable::Interpolate(units::meter_t val)
{
    // if we have exactly this value in the map, just return it                                                                                                                                                                 
    if (table.find(val) != table.end()) return table.at(val);
    // if we are beyond the limits, return the first/last element                                                                                                                                                               
    if (val < table.begin()->first)   return table.begin()->second;
    if (val > table.rbegin()->first)  return table.rbegin()->second;

    auto lower = table.lower_bound(val) == table.begin() ? table.begin() : --(table.lower_bound(val));
    auto upper = table.upper_bound(val);


    LookupValue retVal;
    retVal.angle = lower->second.angle + (upper->second.angle - lower->second.angle) * units::meter_t(val - lower->first) / units::math::fabs(upper->first - lower->first);
    retVal.rpm = lower->second.rpm + (upper->second.rpm - lower->second.rpm) * units::meter_t(val - lower->first) / units::math::fabs(upper->first - lower->first);
    return retVal;
}