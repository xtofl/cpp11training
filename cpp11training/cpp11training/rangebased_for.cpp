#include "stdafx.h"

#include <gtest/gtest.h>

#include <string>

class Range {
public:

    Range(int first, int after_last)
        : first{ first }
        , after_last{ after_last }
    {}

    int first;
    int after_last;
};

// TODO: make this compile
TEST(range_based_for, we_can_iterate_over_a_collection)
{
    int result = 0;
#ifdef solving_this
    for (const auto &element : Range{ 1, 10 })
    { 
        result += element;
    }
#endif
    EXPECT_EQ(45, result);
}
