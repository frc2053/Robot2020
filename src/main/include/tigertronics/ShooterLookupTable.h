#pragma once

#include <map>
#include <units/units.h>

struct LookupValue {
	units::revolutions_per_minute_t rpm = 0_rpm;
	units::radian_t angle = 0_rad;
};

class ShooterLookupTable
{
public:
	ShooterLookupTable();
	void AddLookupValue(units::meter_t distance, LookupValue val);
	void RemoveLookupValue(units::meter_t distance);
	LookupValue Get(units::meter_t distance);
private:
	LookupValue Interpolate(units::meter_t val);
	std::map<units::meter_t, LookupValue> table;
};

