#include <gtest/gtest.h>
#include <string>
#include <vector>

// TODO: alter a function template to return the number of arguments passed.
// GOAL: be able to specify a variadic function template and use the sizeof... operator
// GRADE: ENTRY
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
// GRADE: ENTRY
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
    auto add5 = [](auto t) { return t; };
}
TEST(tuples, DISABLED_i_can_transform_all_elements_of_a_tuple) {
    // TODO: make `add5` process each element of the `input` tuple
    // to generate a new tuple where each element is 5 bigger
    // GOAL: learn to use pack expansion in function arguments
    // LEVEL: BASIC
    // HINT: return types can be `auto`
    // HINT: make_tuple deduces its template arguments
    const auto input = std::make_tuple(5, 5.0, 'A');
    const auto &result = add5(input);
    EXPECT_EQ(10, std::get<0>(result));
    EXPECT_EQ(10.0, std::get<1>(result));
    EXPECT_EQ('F', std::get<2>(result));
}

namespace {
    template<typename ...Ts>
    std::string serialize(Ts ...ts) {
        return "";
    }
}
TEST(serialization, DISABLED_serialize_different_types)
{
    // TODO: fill in serialize so that the test passes
    // GOAL: get familiar with template parameter packs
    // GOAL: learn how to expand a (single) parameter pack
    // GRADE: INTERMEDIATE
    EXPECT_EQ("", serialize());
    EXPECT_EQ("int@1", serialize(1));
    EXPECT_EQ("string@'abc'", serialize(std::string("abc")));
    EXPECT_EQ("int@1, string@'abc'", serialize(1, std::string("abc")));
}

// TODO: implement flatten to allow polymorphic concatenation
// GOAL: learn to separate iteration from dispatching
// HINT: the base case is a single vector
// GRADE: INTERMEDIATE
template<typename ...Ts>
auto flatten(Ts... ts) {
    return std::vector<int>();
}
TEST(variadic_monad, DISABLED_flatten_operation)
{
    EXPECT_EQ((std::vector<int>{ 1, 2, 3, 4, 5 }),
        (flatten(std::vector<int>({ 1 }), 2, std::vector<int>{ 3, 4, 5 })));
}


// TODO: adapt `contained_by` to return a callable
// representing a predicate for presence in a compile-time list
// HINT: contained_by()( anything ) will return false.
// GRADE: INTERMEDIATE
template<typename ...Ts>
auto contained_by(Ts&&...ts)
{
    return [](auto x)
    {
        return false;
    };
}

TEST(variadic_templates, DISABLED_create_a_compile_time_list_lookup)
{
    auto in_list = contained_by(1, 2, 3, 4);
    EXPECT_TRUE(in_list(1));
    EXPECT_FALSE(in_list(0));
}

// this exercise will take some more time...
// 
// TODO: fill in the `product` function so that it prints a table
// of the functions applied to the arguments
// GOAL: learn to deal with multiple packs and expansions
// GRADE: HARD
std::string join(std::string sep) {
    return "";
}
namespace std {
    std::string to_string(const std::string &s) { return s; }
}
template<typename T, typename ...Ts>
std::string join(std::string sep, T t, Ts...ts) {
    return std::to_string(t) + sep + join(sep, ts...);
}
template<typename T>
std::string join(std::string sep, T t) {
    return std::to_string(t);
}
TEST(vt, canjoin) {
    EXPECT_EQ("", join(", "));
    EXPECT_EQ("1", join(", ", 1));
    EXPECT_EQ("1, abc", join(", ", 1, std::string("abc")));
}

template<typename ...Fs, typename ...Ts>
std::string product(std::tuple<Fs...> functions, std::tuple<Ts...> arguments)
{
    return "";
}

TEST(composition, print_a_matrix)
{
    const auto table = product(
        std::make_tuple(
            [](auto i) { return i; },
            [](auto i) { return i*i; },
            [](auto i) { return i*i*i - 1; }
            ),
        std::make_tuple(1, 2, 3)
    );
    EXPECT_EQ(R"(
1, 2, 3
1, 4, 9
0, 7, 26
)", table);

    EXPECT_EQ(R"(
1, 4, 9, 100
0, 7, 26, 1000
)", (product(
    std::make_tuple(
        [](auto i) { return i*i; },
        [](auto i) { return i*i*i; }
        ),
    std::make_tuple(1, 2, 3, 10)
)));
}
