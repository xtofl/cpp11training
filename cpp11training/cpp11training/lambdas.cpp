#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <exception>

// should override these with local lambdas
// don't touch these functions...
void foo() { throw std::runtime_error{ "not implemented" }; }
int bar() { return 1; }
int length(const std::string &s) { return 100; }

TEST(lambdas, DISABLED_we_can_define_local_lambdas)
{
	// TODO: create a lambda that returns the length
	// of a string, and a `foo` that does just nothing
	//
    // GOAL: get acquainted with the lambda expression syntax
    EXPECT_EQ(3, length("abc"));
    EXPECT_NO_THROW(foo());
}

TEST(lambdas, DISABLED_we_can_capture_the_local_variables_by_value)
{
    std::vector<std::function<int(int)>> multipliers;

    for (int i = 0; i != 10; ++i)
    {
        // TODO: alter my_function to return
        // a different function on every iteration:
        // end up with an array of multiplying functions
        // \n -> \n * i
        //
        // GOAL: lambda expressions can be used
        // to create functions on-the-fly!
        auto create_function = [] {
            return [] (int x) { return 0; };
        };

        multipliers.push_back(create_function());
    }

    EXPECT_EQ(1, multipliers[1](1));
    EXPECT_EQ(2, multipliers[1](2));

    EXPECT_EQ(2, multipliers[2](1));
    EXPECT_EQ(9, multipliers[3](3));
}

TEST(lambdas, DISABLED_we_can_capture_local_variables_by_reference)
{
    int receiver = 0;
    // TODO: create a local lambda expression that
    // makes `receiver` equal to `i` every time
    //
    for (int i = 0; i != 10; ++i)
    {
        foo();
        EXPECT_EQ(i, receiver);
    }
}


TEST(lambdas, DISABLED_we_can_add_state)
{
    // TODO:
    // create a lambda expression `foo` that
    // returns a different value upon subsequent calls
    //
    // HINT: lambda expressions are immutable, unless...
    int foo_calls = 0;
    foo();
    EXPECT_EQ(1, foo_calls);
    foo();
    EXPECT_EQ(2, foo_calls);

    {
        // sum of lengths
        EXPECT_EQ(3, length("abc"));
        EXPECT_EQ(7, length("efgh"));
    }
    {
        // average length
        EXPECT_NEAR(3.000, length("abc"), 0.01);
        EXPECT_NEAR(3.500, length("efgh"), 0.01);
        EXPECT_NEAR(3.333, length("ijk"), 0.01);
    }
}


#include "class_design/Thing.h"
#include "class_design/MyBike.h"
#include "class_design/Piano.h"

// TODO: implement this with a map<key, factory function>
std::unique_ptr<Thing> make(const std::string &what)
{
    return nullptr;
}

TEST(lambdas, DISABLED_we_can_instantiate_based_on_a_typename)
{
    // TODO: alter the `make` function to return an object
    // of the type specified by the provided argument.
    //
    // HINT: a std::map is great for lookup, but is not polymorphic.
    // a std::function can wrap any lambda expression
    auto f = make("my bike");
    EXPECT_FALSE(dynamic_cast<MyBike*>(f.get()) == nullptr);
    auto i = make("piano");
    EXPECT_FALSE(dynamic_cast<Piano*>(i.get()) == nullptr);
}


std::function<double(double)> make_adder(double operand)
{
    return std::function<double(double)>{};
}

TEST(lambdas, DISABLED_we_can_instantiate_functions_at_runtime)
{
    // TODO: alter make_adder so that it can be used
    // to create different functions, depending on the argument
    //
    // GOAL: an entry-level functional programming exercise
    //
    auto add5 = make_adder(5.0);
    EXPECT_NEAR(5.0, add5(0.0), 0.001);
    EXPECT_NEAR(15.0, add5(10.0), 0.001);
}

TEST(lambdas, DISABLED_we_can_bind_arguments)
{
    auto add5 = std::plus<int>();
//TODO: #define we_can_bind_an_argument
// and define add5 with std::bind
//
// HINT: use a placeholder!
#ifdef we_can_bind_an_argument
    EXPECT_EQ(5, add5(0));
    EXPECT_EQ(15, add5(10));
#endif
}

std::function<double(double)> make_safe(
    std::function<double(double)> unsafe_function,
    std::function<bool(double)> check)
{
    return std::function<double(double)>{};
}

TEST(lambdas, DISABLED_we_can_add_a_policy_to_a_function)
{
    const auto reciproc = [](double f) { return 1. / f; };

    const auto &safe_reciproc = make_safe(reciproc, [&](double f) {
        return (f != 0.0);
    });
    // TODO: alter `make_safe` so that it throws runtime_error when
    // its policy returns false, and otherwise calls the provided function
    EXPECT_NEAR(2.0, safe_reciproc(0.5), 1e-5);
    EXPECT_THROW(safe_reciproc(0.0), std::runtime_error);
}


#if __cplusplus >= 201402L // but msvc has __cplusplus still defined to 199711L... https://connect.microsoft.com/VisualStudio/feedback/details/763051/a-value-of-predefined-macro-cplusplus-is-still-199711l
#include <algorithm>

TEST(lambdas, DISABLED_you_dont_have_to_specify_the_argument_types_in_cpp14)
{
    auto stringify = [](auto i) {
        return std::to_string(i);
    };
    {
        EXPECT_EQ("1", stringify(1));
    }
    {
        EXPECT_EQ(std::to_string(1.0), stringify(1.0));
    }
}
#endif

// MORE ADVANCED:
// revisit use_auto.cpp: implement TEST(find_number, DISABLED_we_can_just_auto_translate)
// with lambda expressions