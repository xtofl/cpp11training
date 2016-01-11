#pragma once

#include <string>

// ... imagine a huge class hierarchy
class Thing {
public:
    Thing(std::string name) : name_(std::move(name)) {}
	virtual ~Thing() {}
	virtual double size_in_cm() const = 0;
	virtual std::string purpose() const = 0;
	
	virtual std::string name() const { return name_; }
private:
    std::string name_;
};
