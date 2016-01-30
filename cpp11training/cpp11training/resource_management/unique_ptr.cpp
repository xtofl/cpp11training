#include "stdafx.h"

#include <gtest/gtest.h>
#include <memory>
#include <functional>

class JarPotVessel {
public:
    std::function<void()> destructed = [] {};
    ~JarPotVessel()
    {
        destructed();
    }
};

TEST(unique_ptr, object_is_destructed_when_ptr_out_of_scope)
{
    auto thing_wrapper = new JarPotVessel();
    bool destructed = false;
    thing_wrapper->destructed = [&] { destructed = true; };

    {
        ASSERT_FALSE(destructed);
        auto other_wrapper = std::move(thing_wrapper); // there must be only one!
        EXPECT_FALSE(destructed);
    };
    EXPECT_TRUE(destructed);
}

TEST(unique_ptr, cant_copy_a_unique_ptr)
{
//TODO #define i_know_what_is_wrong
#ifdef i_know_what_is_wrong
    std::vector<std::unique_ptr<int>> values{ {
            std::make_unique<int>(1),
            std::make_unique<int>(2),
        }
    };

    EXPECT_EQ(1, *values.at(0));
    EXPECT_EQ(2, *values.at(1));

    auto copy = values;

    EXPECT_EQ(1, *copy.at(0));
    EXPECT_EQ(2, *copy.at(1));
#endif
}
