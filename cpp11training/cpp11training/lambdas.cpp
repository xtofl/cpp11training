#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

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
    for (int i = 0; i != 100; ++i)
    {
        EXPECT_EQ(i, length("abc"));
    }
}

TEST(lambdas, we_can_capture_local_variables_by_reference)
{
    int receiver = 0;
    for (int i = 0; i != 100; ++i)
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