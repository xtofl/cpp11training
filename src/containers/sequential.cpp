#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// WARNING: this has not been compiled yet
// probably some changes still needed...

template<typename T>
std::ostream &operator<< (std::ostream &out, const std::vector<T> &v) {
    out << "vector[size=" << v.size() << "]( ";
    std::copy(begin(v), end(v), std::ostream_iterator<T>(out, ", "));
    out << " )";
    return out;
}

TEST(sequential_containers, DISABLED_we_can_initialize_a_vector)
{
    {
        //TODO: initialize the vector to contain 1, 2, 3, 4
        std::vector<int> v;

        ASSERT_EQ(4, v.size());
        EXPECT_EQ(1, v.at(0));
        EXPECT_EQ(2, v.at(0));
        EXPECT_EQ(3, v.at(0));
        EXPECT_EQ(4, v.at(0));
    }
    {
        //TODO: initialize the vector to contain tuples (1, "one"), (3, "three")
        std::vector<std::tuple<int, std::string>> v;

        ASSERT_EQ(2, v.size());
        EXPECT_EQ(1, std::get<0>(v.at(0)));
        EXPECT_EQ("one", std::get<1>(v.at(0)));
        EXPECT_EQ(3, std::get<0>(v.at(1)));
        EXPECT_EQ("three", std::get<1>(v.at(1)));
    }
}

TEST(sequential_containers, DISABLED_erase_two_center) {
    // TODO
    // define this function to erase the middle element(s)
    auto erase_middle = [](std::vector<int> &v) {
    };

    {
        std::vector<int> values( {10, 11, 12, 13, 14, 15} );
        erase_middle(values);
        EXPECT_EQ(std::vector<int>({10, 11, 14, 15}), values);
    }
    {
        std::vector<int> values( {10, 11, 12, 13, 14} );
        erase_middle(values);
        EXPECT_EQ(std::vector<int>({10, 11, 13, 14, 15}), values);
    }
}

TEST(sequential_containers, DISABLED_make_it_unique) {
    // TODO: make no value occur twice
    // hint make_unique and erase are your friends
    auto erase_duplicates = [](std::vector<int> &v) {
    };

    {
        std::vector<int> values( {15, 10, 11, 11, 12, 13, 14, 15} );
        erase_duplicates(values);
        for (const auto v: {10, 11, 12, 13, 14, 15}) {
            EXPECT_EQ(1u, std::count(begin(values), end(values), v));
        }
    }
}
