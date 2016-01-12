#include "stdafx.h"
#include "gtest/gtest.h"
#include <cstdint>

enum class A : std::uint64_t { letter, number };
enum class B { newspaper, letter };


TEST(enums, enums_are_not_confusing)
{
    A character = A::number;
    switch (character) {
    case A::letter:
        FAIL(); break;
    case A::number:
        SUCCEED(); break;
    }
}

TEST(enums, the_size_is_under_control)
{
    EXPECT_EQ(8, sizeof(A));
}