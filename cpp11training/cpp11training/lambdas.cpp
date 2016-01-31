#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <exception>

// should override these with local lambdas
void foo() { throw std::runtime_error{ "not implemented" }; }
int length(const std::string &s) { return 100; }

TEST(lambdas, we_can_define_local_lambdas)
{
    EXPECT_EQ(3, length("abc"));
    EXPECT_NO_THROW(foo());
}

TEST(lambdas, we_can_capture_the_local_variables_by_value)
{
    for (int i = 0; i != 10; ++i)
    {
        EXPECT_EQ(i, length("abc"));
    }
}

TEST(lambdas, we_can_capture_local_variables_by_reference)
{
    int receiver = 0;
    for (int i = 0; i != 10; ++i)
    {
        foo();
        EXPECT_EQ(i, receiver);
    }
}


TEST(lambdas, we_can_add_state)
{
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

// TODO: convert this into a map<key, lambda>
std::unique_ptr<Thing> make(const std::string &what)
{
    return nullptr;
}

TEST(lambdas, we_can_instantiate_based_on_a_typename)
{
    auto f = make("my bike");
    EXPECT_FALSE(dynamic_cast<MyBike*>(f.get()) == nullptr);
    auto i = make("piano");
    EXPECT_FALSE(dynamic_cast<Piano*>(i.get()) == nullptr);
}


// TODO: make 
std::function<double(double)> make_adder(double operand)
{
    return std::function<double(double)>{};
}

TEST(lambdas, we_can_instantiate_functions_at_runtime)
{
    auto add5 = make_adder(5.0);
    EXPECT_NEAR(5.0, add5(0.0), 0.001);
    EXPECT_NEAR(15.0, add5(10.0), 0.001);
}

TEST(lambdas, we_can_bind_arguments)
{
    auto add5 = std::plus<int>();
//TODO: #define we_can_bind_an_argument
#ifdef we_can_bind_an_argument
    EXPECT_EQ(5, add5(0));
    EXPECT_EQ(15, add5(10));
#endif
}

std::function<double(double)> make_safe(std::function<double(double)> unsafe_function, std::function<bool(double)> check)
{
    return std::function<double(double)>{};
}

TEST(lambdas, we_can_add_a_policy_to_a_function)
{
    const auto &reciproc = [](double f) { return 1. / f; };
    
    std::string status;
    const auto &safe_reciproc = make_safe(reciproc, [&](double f) {
        if (f == 0.0) {
            status = "division by zero";
            return false;
        }
        else
        {
            return true;
        }
    });
    EXPECT_NO_THROW(safe_reciproc(0.0));
    EXPECT_EQ("division by zero", status);
}

TEST(lambdas, take_care_of_object_lifetimes)
{
    std::function<std::vector<int>()> read;
    {
        std::vector<int> i{ {1, 2, 3, 4} };
        read = [&] { return i; };
    }
    EXPECT_EQ(4u, read().size());

    {
        std::vector<int> i{ {1, 2, 3, 4} };
        read = [&] { return i; };
        auto j = std::move(i);
        EXPECT_EQ(4u, read().size());
    }

}


#if __cplusplus >= 201402L // but msvc has __cplusplus still defined to 199711L... https://connect.microsoft.com/VisualStudio/feedback/details/763051/a-value-of-predefined-macro-cplusplus-is-still-199711l
#include <algorithm>

TEST(lambdas, you_dont_have_to_specify_the_argument_types_in_cpp14)
{
    auto stringify = [](auto i) {
        return std::to_string(i);
    };
    {
        EXPECT_EQ("1", stringify(1));
    }
    {
        EXPECT_EQ("1.0", stringify(1.0));
    }
}
#endif