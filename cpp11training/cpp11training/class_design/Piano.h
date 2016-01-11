#include "stdafx.h"
#include "class_design/Instrument.h"

class Piano : public Instrument {
public:
    using Instrument::Instrument;
    Piano() : Piano{ "a piano" } {}
	virtual double size_in_cm() const { return 130; }
};
 