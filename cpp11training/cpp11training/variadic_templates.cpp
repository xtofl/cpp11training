#include <gtest/gtest.h>
#include <string>

namespace {
    std::string serialize() { return ""; }
    std::string serialize(int i) { return "int@" + std::to_string(i); }
    std::string serialize(const std::string &s) { return "string@'" + s + "'"; }
    std::string serialize(const char* sz) { return serialize(std::string(sz)); }

    template<typename T, typename ...Ts>
    std::string serialize(const T & t, const Ts ...ts) {
        return serialize(t) + ", " + serialize(ts...);
    }
}

TEST(serialization, serialize_different_types)
{
    // TODO: create serialize so that the test passes
    // GOAL: get familiar with template parameter packs
    EXPECT_EQ("", serialize());
    EXPECT_EQ("int@1", serialize(1));
    EXPECT_EQ("string@'abc'", serialize("abc"));
    EXPECT_EQ("int@1, string@'abc'", serialize(1, "abc"));
}