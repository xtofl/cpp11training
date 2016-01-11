#include "stdafx.h"

#include <gtest/gtest.h>

#include <string>

TEST(range_based_for, rewrite_to_cpp11)
{
    std::vector<int> ints{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = 0;
    for (std::vector<int>::const_iterator it = ints.begin(); it != ints.end(); ++it)
    {
        result += *it;
    };
    EXPECT_EQ(55, result);
}


template<class Container, class result_type = Container::value_type>
result_type sum(const Container &c)
{
    result_type result = 0;
    typename Container::const_iterator it = c.begin();
    const typename Container::const_iterator itEnd = c.end();
    for (; it != itEnd; ++it)
    {
        result += *it;
    }
    return result;
}

TEST(range_based_for, use_on_generic_containers_also_arrays)
{
    std::vector<int> ints{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(55, sum(ints) );
// TODO: make this compile (and run...)
#if working_on_this
    long longs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(55, sum(longs));
#endif
}

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
    for (const auto &element : Range{ 1, 11 })
    { 
        result += element;
    }
#endif
    EXPECT_EQ(55, result);
}
