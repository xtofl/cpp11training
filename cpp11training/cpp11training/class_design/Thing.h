#pragma once

#include <string>

// ... imagine a huge class hierarchy
class Thing {
public:
	virtual ~Thing() = default;
	virtual double size_in_cm() const = 0;
	virtual std::string purpose() const = 0;
	
	virtual std::string name() const { return "just a thing"; }
};
