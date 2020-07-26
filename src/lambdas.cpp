#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <exception>
#include <algorithm>
#include <cmath>
#include <cctype>

//////// DON'T TOUCH THIS
// you should override these with local lambdas
// don't touch these functions...
void foo() { throw std::runtime_error{ "not implemented" }; }
int bar() { return 1; }
void baz(int) { }
int length(const std::string &s) { return 100; }
///////////////////////////

TEST(lambdas, DISABLED_we_can_define_local_lambdas)
{
    // TODO: create a lambda that returns the length
    // of a string, and a `foo` that does just nothing
    //
    // GOAL: get acquainted with the lambda expression syntax
    EXPECT_EQ(3, length("abc"));
    EXPECT_EQ(10, length("abcdefghij"));

    EXPECT_NO_THROW(foo());
}

TEST(lambdas, DISABLED_we_can_capture_the_local_variables_by_value)
{
    std::vector<std::function<int(int)>> multipliers;

    for (int i = 0; i != 10; ++i)
    {
        // TODO: alter the lambda represent a different
        // calculation on every iteration, so that we
        // end up with an array of multiplying functions
        // \n -> n * i
        //
        // GOAL: learn that lambda expressions can be used
        // to create functions on-the-fly!

        multipliers.push_back([](int x) { return 0; });
    }

    EXPECT_EQ(1, multipliers[1](1));
    EXPECT_EQ(2, multipliers[1](2));

    EXPECT_EQ(2, multipliers[2](1));
    EXPECT_EQ(9, multipliers[3](3));
}

TEST(lambdas, DISABLED_we_can_capture_local_variables_by_reference)
{
    using F2 = std::function<int(int, int)>;
    using Op = std::string;

    std::vector<Op> sequence;

    std::map<Op, F2> operators{
        // TODO: adapt the lambda's so that they 'log'
        // to the `sequence` container.
        // GOAL: learn how to capture a variable by reference
        // GOAL2: this becomes a use case for a higher order
        // function
        {"+", [](int i, int j){ return i+j;}},
        {"-", [](int i, int j){ return i-j;}}
    };
    EXPECT_EQ(5, operators.at("+")(3, 2));
    EXPECT_EQ(1, operators.at("-")(3, 2));
    EXPECT_EQ(6, operators.at("*")(3, 2));

    EXPECT_EQ((std::vector<Op>{"+", "-", "*"}), sequence);
}

#include <algorithm>
auto transform = [](auto &&x, auto f) {
    return std::transform(begin(x), end(x), begin(x), f);
};

auto lowcase(std::string &s) { return transform(s, [](auto c){ return std::tolower(c);}); }
auto upcase(std::string &s) { return transform(s, [](auto c){ return std::toupper(c);}); }

TEST(lambdas, DISABLED_we_can_capture_by_const_reference)
{
    std::vector<std::string> tokens;

    auto contains_token =
    // TODO:
    //  change the capture expression so that the lambda fails to compile
    //  by capturing tokens as const
    //  cf. https://stackoverflow.com/a/32440415/6610
    //
        [&tokens] (std::string_view text) {
    // GOAL:
    //   Become able to express that a lambda,
    //   though it captures some variable, will not
    //   actually _change_ that variable.
    //
    // NOTE: we only have capture by ref and capture by copy.
    //  maybe capture by const-ref is an oversight in the standard?
    //
    // NOTE 2: you'll have to adapt the labmda body to make the test pass
    //
    // APPLICATION: when you want to avoid expensive copying of the
    // closure, but have no control over the lambda body itself.
    // In this case, the 'lack of control' is approximated by using
    // some mutator functions that are out of our range.
        for(auto &t: tokens) {
            lowcase(t);
            if (text.find(t) != text.npos) {
                return true;
            }
            upcase(t);
            if (text.find(t) != text.npos) {
                return true;
            }
        }
        return false;
    };

    tokens = {"token1", "token2"};
    EXPECT_TRUE(contains_token("bla bla bla token2"));
    EXPECT_EQ("token1", tokens[0]);
    EXPECT_EQ("token2", tokens[1]);
}

TEST(lambdas, DISABLED_we_can_store_internal_state)
{
    // TODO:
    // create a lambda expression `bar` that
    // stores a different value into `bar_calls` upon subsequent calls
    //
    // HINT: lambda expressions are immutable, unless...
    //
    // WHY?  this is sometimes needed in tests to e.g. record the
    // number of times something was called
    //

    // don't touch this:
    EXPECT_EQ(1, bar());
    EXPECT_EQ(2, bar());
    EXPECT_EQ(3, bar());
}

TEST(lambdas, DISABLED_we_can_store_internal_state2)
{
    // sum of lengths
    //
    // TODO: make the lambda `add_length` return
    // the accumulated length of all the strings that have
    // been given to it
    auto add_length = [](std::string s) { return 0; };

    // |  don't touch this
    // V
    EXPECT_EQ(3, add_length("abc"));
    EXPECT_EQ(7, add_length("efgh"));
}


TEST(lambdas, DISABLED_we_can_add_state3)
{
    // average length
    //
    // TODO: make the lambda `add_length` return the average
    // length of all the strings that have been given to it
    auto add_length = [](std::string s) { return 0.0; };

    // |  don't touch this
    // V
    EXPECT_NEAR(3.000, add_length("abc"), 0.01);
    EXPECT_NEAR(3.500, add_length("efgh"), 0.01);
    EXPECT_NEAR(3.333, add_length("ijk"), 0.01);
}


TEST(lambdas, DISABLED_we_can_add_state4)
{
    std::vector<int> ints;
    // TODO: create a lambda that returns the next square
    // on every call
    //
    auto squares = [] { return -1; };
    // |  don't touch this
    // V
    std::generate_n(std::back_inserter(ints), 10, squares);
    EXPECT_EQ(9, ints.at(2));
    EXPECT_EQ(100, ints.at(9));
}


#include "class_design/Thing.h"
#include "class_design/MyBike.h"
#include "class_design/Piano.h"

// TODO: implement this `thing` factory with a map<key, factory function>
// (cf. the next test)
std::unique_ptr<Thing> make(const std::string &what)
{
    using ThingFactory = std::function<Thing*()>;

    // fill in this map to work with bikes, pianos and the like:
    static std::map<std::string, ThingFactory> constructors;

    const auto construct = constructors.at(what);

    return std::unique_ptr<Thing>{construct()};
}

TEST(lambdas, DISABLED_we_can_instantiate_based_on_a_typename)
{
    // TODO: alter the `make` function to return an object
    // of the type specified by the provided argument.
    //
    // GOAL: demonstrate that functions can be stored in containers
    //
    // HINT: a std::map is great for lookup, but is not polymorphic.
    // a std::function can wrap any lambda expression
    auto f = make("my bike");
    EXPECT_FALSE(dynamic_cast<MyBike*>(f.get()) == nullptr);
    auto i = make("piano");
    EXPECT_FALSE(dynamic_cast<Piano*>(i.get()) == nullptr);
}



TEST(lambdas, DISABLED_we_can_bind_arguments)
{
    auto add5 = std::plus<int>();
    //TODO: #define we_can_bind_an_argument
    // and define add5 with std::bind
    //
    // HINT: use a placeholder!
    // GOAL: lay the basis for expression trees; provide
    // an alternative to plain lambdas
    //
#ifdef we_can_bind_an_argument
    EXPECT_EQ(5, add5(0));
    EXPECT_EQ(15, add5(10));
#endif
}


// TODO: alter this function so that it 'wraps' a function
// in a validation-check.  If the check would fail,
// the resulting function should throw an std::runtime_error
auto make_safe(
    std::function<double(double)> unsafe_function,
    std::function<bool(double)> check)
{
    return std::function<double(double)>{};
}

TEST(lambdas, DISABLED_we_can_decorate_a_function_with_a_check)
{
    // TODO: alter `make_safe` so that it throws runtime_error when
    // its check returns false, and otherwise calls the provided function
    //
    // GOAL: learn to create 'meta' functions to allow
    // decoupling aspects of your code even more.  This results
    // in more reusable code.

    const auto reciproc = [](double f) { return 1. / f; };
    const auto sqrt = [](double f) { return std::sqrt(f); };

    const auto &safe_reciproc = make_safe(reciproc, [&](double f) {
        return (f != 0.0);
    });
    const auto &safe_sqrt = make_safe(sqrt, [](double d) {
        return d >= 0;
    });

    EXPECT_NEAR(2.0, safe_reciproc(0.5), 1e-5);
    EXPECT_THROW(safe_reciproc(0.0), std::runtime_error);
    EXPECT_NEAR(2.0, safe_sqrt(4), 1.e5);
    EXPECT_THROW(safe_sqrt(-1), std::runtime_error);
}


#if __cplusplus >= 201402L // but msvc has __cplusplus still defined to 199711L...
// https://blogs.msdn.microsoft.com/vcblog/2018/04/09/msvc-now-correctly-reports-__cplusplus/
// https://connect.microsoft.com/VisualStudio/feedback/details/763051/a-value-of-predefined-macro-cplusplus-is-still-199711l
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