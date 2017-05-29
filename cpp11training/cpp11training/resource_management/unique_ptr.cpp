#include "stdafx.h"

#include <gtest/gtest.h>
#include <memory>
#include <array>
#include <functional>

class JarPotVessel {
public:
    std::function<void()> destructed = [] {};
    ~JarPotVessel()
    {
        destructed();
    }
};

TEST(unique_ptr, DISABLED_object_is_destructed_when_ptr_out_of_scope)
{
	// TODO: make `thing_wrapper` 'own' the object,
	// to prevent it from leaking
    // GOAL: learn to use unique_ptr to express ownership of
    // objects on the free store.
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

TEST(unique_ptr, DISABLED_cant_copy_a_unique_ptr)
{
// TODO:
// #define i_know_what_is_wrong
// and make the code compile:
// a vector of owners can't be copied, since then there would be
// two owners of each contained object.
#ifdef i_know_what_is_wrong
    std::array<std::unique_ptr<int>, 2> values {
            std::make_unique<int>(1),
            std::make_unique<int>(2),
    };

    EXPECT_EQ(1, *values.at(0));
    EXPECT_EQ(2, *values.at(1));

    // TODO: tinker with this line to let the test pass
    auto target = values;

    EXPECT_EQ(1, *target.at(0));
    EXPECT_EQ(2, *target.at(1));
#endif
}
