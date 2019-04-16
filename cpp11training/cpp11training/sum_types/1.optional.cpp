#include <string>
#include <optional>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <gtest/gtest.h>


struct FormInput { std::string_view value; }; 
struct Index { int value; };
struct Ratio { double value; };

struct Voltage { double value; };

std::string to_string(Voltage v) {
    std::ostringstream ss;
    ss.precision(1); // fixed for this case
    ss << std::fixed << v.value << "V";
    return ss.str();
}

struct VoltageRange { Voltage low; Voltage high; };

Index fromForm(FormInput input) { return { atoi(input.value.data()) }; }

Ratio fromIndex(Index i) {
    return { static_cast<double>(i.value) / 100.0 };
}

const VoltageRange range{ { 1.0 }, { 10.0 } };

Voltage toVoltage(Ratio r) {
    const auto scale = (range.high.value - range.low.value);
    return {range.low.value + r.value * scale};
}

// The Works: this is called from a `main(argc, argv)` somewhere,
// with `args` filled up with the values in argv
auto toVoltageString(const std::vector<std::string_view> &args)
{
    const auto input = FormInput{ args.at(0) };
    const auto index = fromForm(input);
    const auto ratio = fromIndex(index);
    const auto voltage = toVoltage(ratio);
    return to_string(voltage);
}


// Leave this as is: this tests the basic functionality:
// take an argument, convert it to a voltage.
TEST(optional, we_can_convert_an_argument_to_a_voltage) {
    EXPECT_EQ(toVoltageString({ "0" }), "1.0V");
    EXPECT_EQ(toVoltageString({ "90" }), "9.1V");
    EXPECT_EQ(toVoltageString({ "100" }), "10.0V");
}

// TODO:
//   adapt `toVoltageString` so that it can work with
//   no arguments at all.  Use `std::optional` on the
//   way to express absence of an argument.
//
//   Do this for the following three tests
//
// GOAL:
//   learn to create an `optional`, and handle
//   invalid ones.
TEST(optional, DISABLED_we_can_deal_with_lack_of_arguments) {
    EXPECT_EQ(toVoltageString({ }), "?");
}

// TODO: same as previous test
TEST(optional, DISABLED_we_can_deal_with_invalid_numbers) {
    EXPECT_EQ(toVoltageString({"NotANumber"}), "?");
}

// TODO: same as previous test
TEST(optional, DISABLED_we_can_deal_with_overflow) {
    EXPECT_EQ(toVoltageString({"10000"}), "?");
    EXPECT_EQ(toVoltageString({"-10000"}), "?");
}
