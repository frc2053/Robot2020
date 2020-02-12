#include "ShooterLookupTable.h"

ShooterLookupTable::ShooterLookupTable() {

}

void ShooterLookupTable::AddLookupValue(double distance, LookupValue val) {
    table.insert({ distance, val });
}

void ShooterLookupTable::RemoveLookupValue(double distance) {
    auto it = table.find(distance);
    table.erase(it);
}

ShooterLookupTable::LookupValue ShooterLookupTable::Get(double distance) {
    return Interpolate(distance);
}

ShooterLookupTable::LookupValue ShooterLookupTable::Interpolate(double val)
{
    // if we have exactly this value in the map, just return it                                                                                                                                                                 
    if (table.find(val) != table.end()) return table.at(val);
    // if we are beyond the limits, return the first/last element                                                                                                                                                               
    if (val < table.begin()->first)   return table.begin()->second;
    if (val > table.rbegin()->first)  return table.rbegin()->second;

    auto lower = table.lower_bound(val) == table.begin() ? table.begin() : --(table.lower_bound(val));
    auto upper = table.upper_bound(val);


    LookupValue retVal;
    retVal.angle = double(lower->second.angle + (upper->second.angle - lower->second.angle) * float(val - lower->first) / fabs(upper->first - lower->first));
    retVal.rpm = double(lower->second.rpm + (upper->second.rpm - lower->second.rpm) * float(val - lower->first) / fabs(upper->first - lower->first));
    return retVal;
}