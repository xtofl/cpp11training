#include <gtest/gtest.h>
#include <string>

enum class Type {
	String,
	Number,
	Dict
};
// TODO
// #define I_KNOW_GENERICS
//
// and make the tests compile and succeed

#ifdef I_KNOW_GENERICS

TEST(generic, algorithmCanUseManyInputTypes)
{
	auto s = "abc";

	EXPECT_EQ(Type::String, getTypeFor(s));
	EXPECT_EQ(Type::String, getTypeFor(std::string{}));
	EXPECT_EQ(Type::Number, getTypeFor(1.0));
	EXPECT_EQ(Type::Number, getTypeFor(sizeof("")));
}
#endif

// TODO
// #define I_KNOW_GENERICS_AND_PARTIAL_SPECIALIZATION
//
// and make the tests compile and succeed

#ifdef I_KNOW_GENERICS_AND_PARTIAL_SPECIALIZATION
TEST(generic, algorithmEvenKnowsArrayTypes)
{
	int is [5];
	EXPECT_EQ(Type::Array, getTypeFor(is));
}
TEST(generic, algorithmEvenKnowsArrayTypesUnlessForChars)
{
	EXPECT_EQ(Type::String, getTypeFor("abc"));
}
#endif
