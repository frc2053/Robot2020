#pragma once

#include <map>

class ShooterLookupTable
{
public:
	struct LookupValue {
		double rpm = 0;
		double angle = 0;
	};
	ShooterLookupTable();
	void AddLookupValue(double distance, LookupValue val);
	void RemoveLookupValue(double distance);
	LookupValue Get(double distance);
private:
	LookupValue Interpolate(double val);
	std::map<double, LookupValue> table;
};

