#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdint>


TEST(uniform_initialization, initialize_builtins)
{
    int a{ 5 };
    EXPECT_EQ(5, a);
    int * a_pointer{ &a }; // yey a leak
    EXPECT_TRUE(&a == a_pointer);
    int an_array[5]{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(5, an_array[4]);
    std::string a_string{ "abc" };
    EXPECT_EQ("abc", a_string);
}

TEST(uniform_initialization, initialize_a_vector)
{
    std::vector<int> ints{ {1, 2, 3, 4, 5} };
    EXPECT_EQ(5u, ints.size());
    EXPECT_EQ(1, ints.at(0));
    EXPECT_EQ(2, ints.at(1));
    EXPECT_EQ(3, ints.at(2));
    EXPECT_EQ(4, ints.at(3));
    EXPECT_EQ(5, ints.at(4));
}


TEST(uniform_initialization, initialize_a_map)
{
    std::map<int, char> ascii{ {'a', 'a'}, {'b', 'b'} };
    EXPECT_EQ('a', ascii.at('a'));
    EXPECT_EQ('b', ascii.at('b'));
}


struct ProtocolMessage {
    using ConversationId = int;
    enum class Type { number, text };
    using Bytes = std::vector<std::uint8_t>;

    ConversationId conversation;
    Type type;
    Bytes bytes;

    ProtocolMessage() : conversation(-1), type(Type::number), bytes() {}
    ProtocolMessage(ConversationId id, Type t, Bytes bytes)
        : conversation(id)
        , type(t)
        , bytes(std::move(bytes))
    {}
};


TEST(uniform_initialization, initialize_an_object)
{
    const ProtocolMessage message( 1, ProtocolMessage::Type::text, {'a', 'b'} );
    EXPECT_EQ(ProtocolMessage::Type::text, message.type);
    ASSERT_EQ(2u, message.bytes.size());
    EXPECT_EQ('a', message.bytes.at(0));
    EXPECT_EQ('b', message.bytes.at(1));
}

class Connection {
public:
    ProtocolMessage receive() {
        return messages.back();
    };
    void send(ProtocolMessage m) {
        messages.emplace_back(std::move(m));
    }

    std::vector<ProtocolMessage> messages;
};

class Peer {
public:
    Peer(std::shared_ptr<Connection> connection)
        : connection{ std::move(connection) }
    {}
    void send(std::string text){
        connection->send({ ProtocolMessage::ConversationId{ 0 }, ProtocolMessage::Type::text, {} });
    }
    void send(int number) {
        connection->send({ ProtocolMessage::ConversationId{ 0 }, ProtocolMessage::Type::number, {} });
    }

    std::string receiveText() {
        const auto &message = connection->receive();
        return reinterpret_cast<const char*>(&message.bytes.at(0));
    }
    int receiveNumber() {
        const auto &message = connection->receive();
        return reinterpret_cast<const int&>(message.bytes.at(0));
    }
private:
    std::shared_ptr<Connection> connection;
};

TEST(uniform_initialization, initialize_a_class_object)
{
    auto connection = std::make_shared<Connection>();
    Peer peer{ connection };
    peer.send(10);
    ASSERT_EQ(1u, connection->messages.size());
    EXPECT_EQ(ProtocolMessage::Type::number, connection->messages.back().type);
    int value = 20;
    ProtocolMessage::Bytes bytes{ reinterpret_cast<const std::uint8_t*>(&value), reinterpret_cast<const std::uint8_t*>(&value) +sizeof(value) };
    ProtocolMessage response{ ProtocolMessage::ConversationId{ 0 }, ProtocolMessage::Type::number, bytes };
    connection->messages.emplace_back(response);
    const auto number = peer.receiveNumber();
    EXPECT_EQ(20, number);
}


std::string concatenate(std::initializer_list<std::string> items) {
    std::string result;
    for (auto &i : items) {
        result += i;
    }
    return result;
}

TEST(uniform_initialization, initializer_list_concat)
{
    EXPECT_EQ("", concatenate({}));
    EXPECT_EQ("abcdefghi", concatenate({ "abc", "def", "ghi" }));
}
