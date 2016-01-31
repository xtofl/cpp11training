#include "stdafx.h"

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

TEST(apply_transform, basic_arithmetic)
{
    const std::vector<int> xs{ {2, 5, 10, 40} };

    std::vector<int> squares;
    std::transform(std::begin(xs), std::end(xs),
        std::back_inserter(squares),
        [](int i) { return i * i; });

    ASSERT_EQ(xs.size(), squares.size());
    EXPECT_EQ(4, squares[0]);
    EXPECT_EQ(25, squares[1]);
    EXPECT_EQ(100, squares[2]);
    EXPECT_EQ(1600, squares[3]);
}

TEST(apply_transform, string_representation)
{
    const std::vector<int> xs{ { 2, 5, 10, 40 } };

    std::vector<std::string> squares;
    std::transform(std::begin(xs), std::end(xs),
        std::back_inserter(squares),
        [](int i) { return std::to_string(i*i); });

    ASSERT_EQ(xs.size(), squares.size());
    EXPECT_EQ("4", squares[0]);
    EXPECT_EQ("25", squares[1]);
    EXPECT_EQ("100", squares[2]);
    EXPECT_EQ("1600", squares[3]);
}


TEST(apply_transform, extract_map_keys)
{
    const std::vector<std::pair<std::string, int>> numbers{ {
        { "two", 2},
        { "five", 5},
        { "ten", 10},
        { "forty", 40 }
    }};

    std::vector<std::string> keys;
    std::transform(std::begin(numbers), std::end(numbers),
        std::back_inserter(keys),
        [](auto p) { return p.first; });

    ASSERT_EQ(numbers.size(), keys.size());
    EXPECT_EQ("two", keys[0]);
    EXPECT_EQ("five", keys[1]);
    EXPECT_EQ("ten", keys[2]);
    EXPECT_EQ("forty", keys[3]);
}



TEST(apply_transform, join_two_input_ranges)
{
    const std::vector<std::string> keys{ {"two", "five", "ten", "forty"} };
    const std::vector<int> values{ {2, 5, 10, 40} };

    std::vector<std::string> numbers;
    std::transform(
        std::begin(keys), std::end(keys),
        std::begin(values),
        std::back_inserter(numbers),
        [](auto p, auto q) { return p + ": " + std::to_string(q); });

    ASSERT_EQ(keys.size(), numbers.size());
    EXPECT_EQ("two: 2", numbers[0]);
    EXPECT_EQ("five: 5", numbers[1]);
    EXPECT_EQ("ten: 10", numbers[2]);
    EXPECT_EQ("forty: 40", numbers[3]);
}

