#pragma once

#include "class_design/Thing.h"

class Vehicle : public Thing {
public:
	virtual std::string purpose() const { return "transportation"; }
	virtual int horse_power() const = 0;
};
