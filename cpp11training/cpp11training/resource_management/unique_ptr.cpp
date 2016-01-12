#include "stdafx.h"

#include <gtest/gtest.h>
#include <memory>
#include <functional>

class JarPotVessel {
};

namespace helper {

    template<class Base>
    class NotifyDestruction : public Base {
    public:
        using Base::Base;

        std::function<void()> destructed = [] {};
        virtual ~NotifyDestruction() {
            destructed();
        }
    };

    template<class T>
    struct Container {
        Container(NotifyDestruction<T> *t)
            : destructed{ false }
            , thing {t}
        {
            thing->destructed = [=] { destructed = true; };
        }
        bool destructed;
        NotifyDestruction<T> *thing;
    };

    template<class T> Container<T> make_destructable() {
        Container<T> r{ new NotifyDestruction<T>{} };
        return r;
    };
}

TEST(unique_ptr, object_is_destructed_when_ptr_out_of_scope)
{
    auto thing_wrapper = helper::make_destructable<JarPotVessel>();
    {
        EXPECT_FALSE(thing_wrapper.destructed);
        auto other_wrapper = std::move(thing_wrapper); // there must be only one!
        EXPECT_FALSE(other_wrapper.destructed);
        EXPECT_TRUE(thing_wrapper.destructed);
    };
    EXPECT_TRUE(thing_wrapper.destructed);
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

    auto copy = values;
#endif
}
