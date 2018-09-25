#include <gtest/gtest.h>
#include <string>

template<typename T>
size_t adl_size(const T &s)
{
    return size(s);
}


namespace video {
    struct Color {
        int red, green, blue;
    };
}
namespace linear_algebra {

    using Rows = size_t;
    using Cols = size_t;
    
    template<Rows r, Cols c>
    class Matrix {
    public:
        static auto constexpr size = r * c;
        int values[size];
    };
}

TEST(name_lookup, DISABLED_we_can_overload_a_function_with_adl)
{
//#define i_know_where_to_define_a_size_function
    // TODO: enable previous line and add `size` overloads
    // to make it compile
    // GOAL: show that ADL uses the _whole_ namespace of the
    // actual arguments
    // HINT: start with the Color overload.  The Matrix overload
    // requires a template specialization:
    // template<Rows r, Cols c> size_t size(const Matrix<r, c>&);
    // LEVEL: INTERMEDIATE
//#define i_know_where_to_define_a_size_function
#ifdef i_know_where_to_define_a_size_function
    EXPECT_EQ(5u, adl_size(std::string("abcde")));
    EXPECT_EQ(3u, adl_size(video::Color{0xff, 0x00, 0xff}));
    EXPECT_EQ(12u, adl_size(linear_algebra::Matrix<3, 4>{}));
#endif
}
