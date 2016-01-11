#include "stdafx.h"

#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <string>

// CODE UNDER TEST:
using Language = std::string;
using Word = std::string;
using Number = int;

std::map<Language, std::map<Word, Number>> mappings{
	{ "nl-nl",{ { "een", 1 },{ "twee", 2 } } },
	{ "en-en",{ { "one", 1 },{ "two", 2 } } }
};

int find_number(const Word & name)
{
	return 0;
}

int translate(const Language &language, const Word & name)
{
	return 0;
}

void set_entry(const Language &language, Word word, int i)
{
}

TEST(find_number, we_can_just_auto_translate)
{
	EXPECT_EQ(1, find_number("een"));
	EXPECT_EQ(2, find_number("twee"));
	EXPECT_EQ(1, find_number("one"));
	EXPECT_EQ(2, find_number("two"));
	EXPECT_THROW(find_number("zork"), std::range_error);
}


TEST(change_number, we_can_change_entries)
{
	EXPECT_NO_THROW(set_entry("en-en", "three", 3));
	EXPECT_EQ(3, translate("en-en", "three"));
}