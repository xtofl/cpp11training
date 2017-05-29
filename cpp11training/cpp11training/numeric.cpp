#include "stdafx.h"

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <numeric>

namespace {
    enum Edge { in, out, equal };
    struct Stroke {
        int first;
        int after_last;
    };
    bool operator==(const Stroke &lhs, const Stroke &rhs) {
        return lhs.first == rhs.first && lhs.after_last == rhs.after_last;
    }
    using Strokes = std::vector<Stroke>;
}

TEST(adjacent_difference, DISABLED_where_are_the_edges)
{
    // TODO: define edges(...) so that the tests pass
    // GOAL: learn to transform adjacent values
    auto edges = [](const auto &samples) -> std::vector<Edge>
    { return {}; };
    using Edges = std::vector<Edge>;
    EXPECT_EQ(Edges{}, edges(""));
    EXPECT_EQ((Edges{ { equal, in, out } }), edges("..X."));
    EXPECT_EQ((Edges{ { out, equal, equal, in, equal, out} }), edges("X...XX."));
}



TEST(adjacent_difference, DISABLED_what_is_the_longest_stripe)
{
    // TODO: define edges(...) so that the tests pass
    // GOAL: learn to transform adjacent values

    auto runs = [](const auto &samples) -> std::vector<Stroke>
    { return Strokes{}; };
    EXPECT_EQ(Strokes{}, runs(""));
    EXPECT_EQ((Strokes{ Stroke{2, 3} }), runs("..X."));
    EXPECT_EQ((Strokes{ Stroke{0, 1}, Stroke{4, 6 } }), runs("X...XX."));
}
