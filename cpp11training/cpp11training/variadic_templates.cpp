#include <gtest/gtest.h>
#include <string>

namespace {
    template<typename ...Ts>
    std::string serialize(Ts ...ts) {
        return "";
    }
}

TEST(serialization, DISABLED_serialize_different_types)
{
    // TODO: create serialize so that the test passes
    // GOAL: get familiar with template parameter packs
    EXPECT_EQ("", serialize());
    EXPECT_EQ("int@1", serialize(1));
    EXPECT_EQ("string@'abc'", serialize("abc"));
    EXPECT_EQ("int@1, string@'abc'", serialize(1, "abc"));
}