#include <gtest/gtest.h>
#include <algorithm>
#include <array>

namespace {
	void do_stuff_with(FILE* f) {
	}
}

TEST(RAII, DISABLED_objectsCanBeCleantAtDestructionTime)
{
	// TODO: make this bunch of code _not_ leak
	// resources
	// 
	// write a class to wrap it,
	// or less generic: use an std class
	FILE* f = fopen("file", "w+");
	do_stuff_with(f);
}


