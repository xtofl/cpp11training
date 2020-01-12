#include "stdafx.h"
#include "class_design/Instrument.h"

class Piano : public Instrument {
public:
	virtual double size_in_cm() const { return 130; }
};
 