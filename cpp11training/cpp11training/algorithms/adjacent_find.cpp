#include "stdafx.h"

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

const auto make_f = [](auto a, auto b, auto c) {
    return [=](auto x) {
        // https://www.desmos.com/calculator/trpwba2fej
        auto t = (x / 10.0 / b - 10.0 * a);
        return t*t*t - 8 * t*t - 13 * t + c;
    };
};

const auto samples = [](auto f)
{
    std::vector<int> values(1000);
    for (int x = 0; x != values.size(); ++x)
    {
        values[x] = static_cast<int>(f(x));
    }
    return values;
};

TEST(adjacent_find, DISABLED_where_is_the_first_top)
{
    const auto values = samples(make_f(1.1, 10, 6));

    // TODO: calculate where the function values remain equal
    const auto top = std::begin(values);

    EXPECT_EQ(*top, *std::next(top));
}


TEST(adjacent_find, DISABLED_where_is_the_first_zero_crossing)
{
    const auto values = samples([](auto x) { return x*x*x - 8 * x*x - 13 * x - 4; });

    // TODO: calculate where the function values crosses zero
    const auto zerocrossing = std::begin(values);

    EXPECT_TRUE( (*zerocrossing) * (*std::next(zerocrossing)) <= 0 );
}
