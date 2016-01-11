#include "stdafx.h"

#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <string>

// CODE UNDER TEST:
using Language = std::string;
using Word = std::string;
using Number = int;
using LanguageLib = std::map<Language, std::map<Word, Number>>;

LanguageLib mappings{
	{ "nl-nl",{ { "een", 1 },{ "twee", 2 } } },
	{ "en-en",{ { "one", 1 },{ "two", 2 } } }
};


namespace detail {

	template<class Library, class Level1Key, class Level2Key>
	auto find_two_level(const Library &library, const Level1Key &key1, const Level2Key &key2) -> decltype(library.at(key1).at(key2))
	{
		return library.at(key1).at(key2);
	}
}

int find_number(const Word & name)
{
	for (const auto &m : mappings) {
		const auto &it = m.second.find(name);
		if (it != end(m.second)) return it->second;
	}

	throw std::range_error("unknown number");
}

int translate(const Language &language, const Word & name)
{
	return detail::find_two_level(mappings, language, name);
}

void set_entry(const Language &language, Word word, int i)
{
	mappings[language][word] = i;
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


TEST(change_number, we_can_use_generic_lookup_with_deferred_return_type)
{
	EXPECT_EQ(1, detail::find_two_level(mappings, "nl-nl", "een"));
}