#include <gtest/gtest.h>
#include <algorithm>
#include <array>
#include <utility>


// TODO: increase the usage depth
// until you get a stack overflow
constexpr size_t recursion_depth = 100;

namespace dont_touch_this {
	struct Tiny {
	};

	struct Moderate {
		int value1;
		double value2;
	};

	struct Big {
		std::array<int, 100000> data;
	};
}

namespace {

	template<typename Arg>
		void use(const Arg a, size_t depth = recursion_depth) {
		   if (depth) use(a, depth-1);
		}
}

using namespace dont_touch_this;

TEST(storage_types, DISABLED_evenBigObjectsCanBePassedAroundSomehow)
{
	// TODO: update the `use` function signature
	// in order to make the test pass without
	// stack overflows
	use(Tiny{});
	use(Moderate{});
	use(Big{});
}


