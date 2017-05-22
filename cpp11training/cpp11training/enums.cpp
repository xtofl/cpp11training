#include "stdafx.h"
#include "gtest/gtest.h"

enum A { letter, number };

//TODO: enable following enum definition
// the compiler will not allow this.  Use an enum class
// to make it work (and adapt the client code)
// GOAL: avoid name clashes in enumerates.
//
#ifdef using_enum_classes
enum B { newspaper, letter };
#endif

TEST(enums, DISABLED_enums_are_not_confusing)
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

TEST(enums, DISABLED_the_size_is_under_control)
{
    // TODO: adapt A so that this test passes
    EXPECT_EQ(8, sizeof(A));
}
