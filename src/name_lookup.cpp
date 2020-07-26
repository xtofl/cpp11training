#include <gtest/gtest.h>
#include <string>
#include <algorithm>

template<typename T>
auto length(T t) { return 0; }

namespace linear_algebra {

    template<size_t N>
    class Vector {
    public:
        int values[N];
        int norm() const {
            // TODO:
            // define norm so that 'longer' vectors
            // have bigger norms
            // HINT: std::reduce, std::accumulate
            return 0;
        };

    };

    // for the EXPECT_EQ
    template<size_t N>
    bool operator==(const Vector<N> &v1, const Vector<N> &v2) {
        using namespace std;
        const auto mismatch = std::mismatch(
                begin(v1.values), end(v1.values),
                begin(v2.values)
            );

        return mismatch.first == end(v1.values);
    }
}

template<typename T>
auto sorted_by_increasing_length(const std::vector<T> &s)
{
    // TODO: adapt this function body to
    // return a sorted vector, where the order is
    // defined by a length function.
    //
    // GOAL:
    //   define a generic function without
    //   imposing changes on the types.
    //
    // HINT: use `std::sort`
    //
    return s;
}


TEST(name_lookup, DISABLED_we_can_use_adl_to_adapt_to_a_library_function)
{
    // TODO:
    // define the sorted_by_increasing_length so that
    // the size is found by ADL (not by injection!)
    //
    // GOAL: show that ADL uses the namespace of the
    // actual arguments
    {
        std::vector<std::string> strings{"xyzabcdx", "abc", "abcde", "abcdefg"};
        auto sorted = sorted_by_increasing_length(strings);
        EXPECT_EQ("abc", sorted.at(0));
        EXPECT_EQ("abcde", sorted.at(1));
        EXPECT_EQ("abcdefg", sorted.at(2));
        EXPECT_EQ("xyzabcdx", sorted.at(3));
    }

    {
        using Point = linear_algebra::Vector<3>;
        std::vector<Point> points{
            {0, 10, 0},
            {10, 10, 0},
            {1, 1, 1}
        };
        auto sorted = sorted_by_increasing_length(points);
        EXPECT_EQ((Point{1, 1, 1}), sorted.at(0));
        EXPECT_EQ((Point{0, 10, 0}), sorted.at(1));
        EXPECT_EQ((Point{10, 10, 0}), sorted.at(2));
    }
}
