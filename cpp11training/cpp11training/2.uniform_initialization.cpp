#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdint>


TEST(uniform_initialization, DISABLED_initialize_builtins)
{
    // TODO: initialize the variables to make the expectations pass
    // Use uniform initialization syntax.
    int a;
    EXPECT_EQ(5, a);
    int * a_pointer = new int; // yey a leak
    EXPECT_TRUE(&a == a_pointer);
    int an_array[5];
    EXPECT_EQ(5, an_array[4]);
    std::string a_string;
    EXPECT_EQ("abc", a_string);
}

TEST(uniform_initialization, DISABLED_initialize_a_vector)
{
    // TODO: initialize the variables to make the expectations pass
    std::vector<int> ints;
    EXPECT_EQ(5u, ints.size());
    EXPECT_EQ(1, ints.at(0));
    EXPECT_EQ(2, ints.at(1));
    EXPECT_EQ(3, ints.at(2));
    EXPECT_EQ(4, ints.at(3));
    EXPECT_EQ(5, ints.at(4));
}


TEST(uniform_initialization, DISABLED_initialize_a_map)
{
    // TODO: initialize the variables to make the expectations pass
    std::map<int, char> ascii;
    EXPECT_EQ('a', ascii.at(65));
    EXPECT_EQ('b', ascii.at(66));
}

// TODO: specify the members of this class
// so that they are properly default-initialized
//
struct ProtocolMessage {
    using ConversationId = int;
    enum class Type { uninitialized, number, text };
    using Bytes = std::vector<std::uint8_t>;

    ConversationId conversation;
    Type type;
    Bytes bytes;

    ProtocolMessage() {}
    ProtocolMessage(const char *) {}
    ProtocolMessage(long) {}
};

TEST(uniform_initialization, DISABLED_initialize_an_object)
{
    // TODO: specify ProtocolMessage to make the expectations pass
    // GOAL: learn to use member defaults
    EXPECT_EQ(ProtocolMessage::Type::uninitialized, ProtocolMessage{}.type);
    EXPECT_EQ(-1, ProtocolMessage{}.conversation);
    EXPECT_EQ(0, ProtocolMessage{}.bytes.size());

    // TODO: use uniform initializer syntax to properly initialize
    // the message
    const ProtocolMessage message("ab");

    EXPECT_EQ(ProtocolMessage::Type::text, message.type);
    EXPECT_EQ(10, message.conversation);
    ASSERT_EQ(2u, message.bytes.size());
    EXPECT_EQ('a', message.bytes.at(0));
    EXPECT_EQ('b', message.bytes.at(1));
}

// TODO #define we_can_use_an_initializer_list
//   and make the code compile and the test succeed.
//   by adding an initializer list argument
//
// GOAL:
//   learn to create functions accepting an initializer list
//
// NOTE: a variadic template would be better.
#ifdef we_can_use_an_initializer_list
std::string concatenate(...) {
    return s;
}

TEST(uniform_initialization, DISABLED_initializer_list_concat)
{
    EXPECT_EQ("", concatenate({}));
    EXPECT_EQ("abcdefghi", concatenate( "abc", "def", "ghi" ));
}
#endif
