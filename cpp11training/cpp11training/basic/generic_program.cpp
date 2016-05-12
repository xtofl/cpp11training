#include <gtest/gest.h>
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
	EXPECT_EQ(Type::String, getTypeFor("abc"));
	EXPECT_EQ(Type::String, getTypeFor(std::string{});
	EXPECT_EQ(Type::Number, getTypeFor(1.0));
	EXPECT_EQ(Type::Number, getTypeFor(sizeof(""));
}
#endif
