#include <gtest/gtest.h>
#include <iostream>
#include <string>

// WARNING: this has not been compiled yet
// probably some changes still needed...

//TODO:
// complete these functions to make the tests pass
namespace {
    struct Data {
        int i;
        std::string s;
        double d;
    };
    Data read(std::istream& in)
    {
        return {0, "", 0.0};
    }
    std::ostream & write(std::ostream &out, const Data &data)
    {
        return out;
    }
}

TEST(formatted_io, DISABLED_we_can_read_basic_types_from_streams) {
    std::string s_data("1 abc 200.5");
    std::stringstream ss(s_data);

    // TODO: tweak the `read` function so that it reads in the members
    // of the Data object
    auto data = read(ss);
    EXPECT_EQ(1, data.i);
    EXPECT_EQ("abc", data.s);
    EXPECT_NEAR(200.5, data.d, 1e-10);
}

TEST(formatted_io, DISABLED_we_can_handle_bad_formatting_with_an_exception) {
    std::string s_data("1 abc not_a_floating_point");
    std::stringstream ss(s_data);

    // TODO: when either member cannot be read, make sure an exception
    // is thrown (we don't want invalid data to exist!)
    EXPECT_THROW(read(ss), std::runtime_error);
}

TEST(formatted_io, DISABLED_we_can_handle_end_of_stream_with_an_exception) {
    std::string s_data("1 abc");
    std::stringstream ss(s_data);

    // TODO: when either member cannot be read, make sure an exception
    // is thrown (we don't want invalid data to exist!)
    EXPECT_THROW(read(ss), std::runtime_error);
}

TEST(formatted_io, DISABLED_we_can_write_basic_types_from_streams) {
    std::string s_data;
    std::stringstream ss(s_data);

    Data data{ 1, "xyz", 5.0 };
    write(ss, data);
    EXPECT_EQ("1 xyz 5.0", s_data);
}

TEST(formatted_io, DISABLED_we_can_print_numbers_in_hex)
{
    std::stringstream ss;

    ss << 0xabcd;

    EXPECT_EQ("0000ABCD", ss.str());
}
