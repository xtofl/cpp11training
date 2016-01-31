#include "stdafx.h"
#include "gtest/gtest.h"

enum A { letter, number };

//TODO fefine it
#ifdef using_enum_classes
enum B { newspaper, letter };
#endif

TEST(enums, enums_are_not_confusing)
{
    A character = number;
    switch (character) {
    case letter:
        FAIL(); break;

//TODO: make it compile
    case number:
        SUCCEED(); break;
    }
}

TEST(enums, the_size_is_under_control)
{
    EXPECT_EQ(8, sizeof(A));
}