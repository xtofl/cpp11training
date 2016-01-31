#include "stdafx.h"

#include <gtest/gtest.h>
#include <vector>
#include <map>

// TODO: use algorithms to calculate the square of each element
TEST(apply_transform, DISABLED_basic_arithmetic)
{
    const std::vector<int> xs{ {2, 5, 10, 40} };

    std::vector<int> squares;

    ASSERT_EQ(xs.size(), squares.size());
    EXPECT_EQ(4, squares[0]);
    EXPECT_EQ(25, squares[1]);
    EXPECT_EQ(100, squares[2]);
    EXPECT_EQ(1600, squares[3]);
}

TEST(apply_transform, DISABLED_string_representation)
{
    const std::vector<int> xs{ { 2, 5, 10, 40 } };

    std::vector<std::string> squares;

    ASSERT_EQ(xs.size(), squares.size());
    EXPECT_EQ("4", squares[0]);
    EXPECT_EQ("25", squares[1]);
    EXPECT_EQ("100", squares[2]);
    EXPECT_EQ("1600", squares[3]);
}


TEST(apply_transform, DISABLED_extract_map_keys)
{
    const std::map<std::string, int> numbers{ {
        { "two", 2},
        { "five", 5},
        { "ten", 10},
        { "forty", 40 }
    }};

    std::vector<std::string> keys;

    ASSERT_EQ(numbers.size(), keys.size());
    EXPECT_EQ("two", keys[0]);
    EXPECT_EQ("five", keys[1]);
    EXPECT_EQ("ten", keys[2]);
    EXPECT_EQ("forty", keys[3]);
}



TEST(apply_transform, DISABLED_join_two_input_ranges)
{
    const std::vector<std::string> keys{ {"two", "five", "ten", "forty"} };
    const std::vector<int> values{ {2, 5, 10, 40} };

    std::vector<std::string> numbers;

    ASSERT_EQ(keys.size(), numbers.size());
    EXPECT_EQ("two: 2", numbers[0]);
    EXPECT_EQ("five: 5", numbers[1]);
    EXPECT_EQ("ten: 10", numbers[2]);
    EXPECT_EQ("forty: 40", numbers[3]);
}

