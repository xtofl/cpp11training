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


template<class Container>
auto sum(const Container &c) -> typename std::remove_const<typename std::remove_reference<decltype(*std::begin(c))>::type>::type
{
    using value_type = std::remove_const<std::remove_reference<decltype(*std::begin(c))>::type>::type;
    value_type result{ 0 };
    static_assert(!std::is_const<value_type>::value, "can't work on const...");
    for (const auto &value : c) {
        result += value;
    }
    return result;
}

TEST(range_based_for, use_on_generic_containers_also_arrays)
{
    std::vector<int> ints{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(55, sum(ints) );

    long longs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    EXPECT_EQ(55, sum(longs));

}

class Range {
public:

    Range(int first, int after_last)
        : first{ first }
        , after_last{ after_last }
    {}

    int first;
    int after_last;
    void operator++() { ++first; }
    bool operator != (const Range &other) const { return first != other.after_last; }
    int operator *() const { return first; }
};

namespace std {
    Range begin(const Range &r) { return r; }
    Range end(const Range &r) { return{ r.after_last, r.after_last }; }
}

// TODO: make this compile
TEST(range_based_for, we_can_iterate_over_a_collection)
{
    int result = 0;
    for (const auto &element : Range{ 1, 11 })
    { 
        result += element;
    }
    EXPECT_EQ(55, result);
}
