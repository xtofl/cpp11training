#pragma once

#include "class_design/Thing.h"

class Vehicle : public Thing {
public:
    using Thing::Thing;
	virtual std::string purpose() const { return "transporting"; }
	virtual int horse_power() const = 0;
};
