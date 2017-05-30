#include <gtest/gtest.h>
#include <string>

// TODO: alter a function template to return the number of arguments passed.
// GOAL: be able to specify a variadic function template and use the sizeof... operator

// #define i_can_specify_a_variadic_function_template
#ifdef i_can_specify_a_variadic_function_template
template<typename T1 = int, typename T2 = int, typename T3 = int>
size_t count_args(T1 = T1{}, T2 = T2{}, T3 = T3{}) { return 0; }

TEST(variadic, we_can_count_arguments)
{

    EXPECT_EQ(2u, count_args(1, 2));
    EXPECT_EQ(3u, count_args('one', 2.0, 3));
}
#endif

// TODO: alter the class template to know its number of arguments
// GOAL: be able to specify a variadic class template and use the sizeof... operator

//#define i_can_specify_a_variadic_class_template
#ifdef i_can_specify_a_variadic_class_template

template<typename T1 = int, typename T2 = int, typename T3 = int>
struct CountArgs
{
    static constexpr size_t value = 0;
};

TEST(variadic, we_can_count_arguments2)
{
    EXPECT_EQ(2u, (CountArgs<int, bool>::value));
    EXPECT_EQ(3u, (CountArgs<int, char, long>::value));
}
#endif



namespace {
    template<typename ...Ts>
    std::string serialize(Ts ...ts) {
        return "";
    }
}
TEST(serialization, DISABLED_serialize_different_types)
{
    // TODO: create serialize so that the test passes
    // GOAL: get familiar with template parameter packs
    EXPECT_EQ("", serialize());
    EXPECT_EQ("int@1", serialize(1));
    EXPECT_EQ("string@'abc'", serialize("abc"));
    EXPECT_EQ("int@1, string@'abc'", serialize(1, "abc"));
}