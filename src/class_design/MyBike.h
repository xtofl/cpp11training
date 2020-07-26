#pragma once

#include "class_design/Vehicle.h"

class MyBike : public Vehicle {
public:
	virtual int horse_power() const {
		return 1;
	}

	virtual double size_in_cm() const { return 60.0; }
};
