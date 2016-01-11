#include "stdafx.h"

#pragma once

#include "class_design/Thing.h"

class Instrument: public Thing {
public:
    using Thing::Thing;
	virtual std::string purpose() const {
		return "making music";
	}
};
