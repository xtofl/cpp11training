#include "stdafx.h"

#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <string>

// CODE UNDER TEST:
int find_number(const std::string & name)
{
	const std::vector<std::map<std::string, int>> mappings{
		{ { "een", 1 },{ "twee", 2 } },
		{ { "one", 1 },{ "two", 2 } }
	};

	return 0;
}

TEST(auto_usage, we_can_limit_the_amount_of_typing)
{
	EXPECT_EQ(1, find_number("een"));
	EXPECT_EQ(2, find_number("twee"));
	EXPECT_EQ(1, find_number("one"));
	EXPECT_EQ(2, find_number("two"));
	EXPECT_THROW(find_number("zork"), std::range_error);
}