#include "stdafx.h"

#include <gtest/gtest.h>

#include "class_design/Thing.h"
#include "class_design/Instrument.h"
#include "class_design/Piano.h"
#include "class_design/Vehicle.h"
#include "class_design/MyBike.h"

// make the compiler complain when we change the Thing::size_in_cm to size_in_m

// make it trivial to add a constructor Thing::Thing(std::string name)
TEST(class_design, adding_constructors_should_be_trivial)
{
	Piano p; // Piano p{"my piano"}
	EXPECT_EQ("making music", p.purpose());
	EXPECT_NEAR(130.0, p.size_in_cm(), 0.00001);
	EXPECT_EQ("my piano", p.name());

	MyBike b;
	EXPECT_EQ("transporting", b.purpose());
	EXPECT_NEAR(60.0, b.size_in_cm(), 0.00001);
}

// make it impossible to copy things
TEST(class_design, synthesized_functions)
{
	Piano p;
	auto q = p; // should not compile.
}
