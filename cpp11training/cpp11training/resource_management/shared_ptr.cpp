#include "stdafx.h"

#include <gtest/gtest.h>
#include <memory>
#include <functional>

namespace {
    class Resource {
    public:
        void use()
        {
            ++usage_count;
        }

        ~Resource() { destructed(); }

        int usage_count = 0;
        std::function<void()> destructed = [] {};
    };

    class User {
    public:
        void foo() {
            resource->use();
        }
        Resource *resource;
    };

}


TEST(shared_ptr, resource_is_cleant_up_after_last_user_gone)
{
    auto resource = new Resource;
    bool destructed = false;
    resource->destructed = [&] { destructed = true; };

    std::vector<User> users;
    EXPECT_FALSE(destructed);

    users.emplace_back(User{ resource });
    EXPECT_FALSE(destructed);
    users.emplace_back(User{ resource });
    EXPECT_FALSE(destructed);

    auto users_copy = users;
    EXPECT_FALSE(destructed);

    users.clear();
    EXPECT_FALSE(destructed);

    users_copy.clear();
    EXPECT_TRUE(destructed);
}

class Pool {
public:
    using  Handle = int;
    std::set<Handle> handles;
    Handle next_free_handle = Handle{};
    Handle allocate() {
        auto h = next_free_handle++;
        handles.insert(h);
        return h;
    }
    void free(Handle h) {
        handles.erase(h);
    }

    bool allocated(Handle h) {
        return handles.find(h) != end(handles);
    }
};

TEST(shared_ptr, not_only_for_objects)
{
    Pool pool;
    try {
        // TODO: make sure h does not leak
        auto h = pool.allocate();

        ASSERT_EQ(0, h);
        throw std::runtime_error("");
    }
    catch (const std::runtime_error &)
    {
        EXPECT_FALSE(pool.allocated(0));
    }
}

class Child;

class Parent {
public:
    std::vector<std::shared_ptr<Child>> children;
    std::function<void()> call = [] {};
    std::function<void()> destructed = [] {};
};

class Child {
public:
    Child(std::shared_ptr<Parent> parent) : parent(std::move(parent)) {}
    void call_parent() {
        parent->call();
    }
    std::shared_ptr<Parent> parent;
    std::function<void()> destructed = [] {};
};

TEST(shared_ptr, breaking_cycles)
{
    bool parent_destructed = false;
    bool parent_called = false;
    bool child_destructed = false;
    {
        auto parent = std::make_shared<Parent>();
        parent->children.emplace_back(std::make_shared<Child>(parent));
        parent->children.back()->call_parent();
        EXPECT_TRUE(parent_called);
    }
    EXPECT_TRUE(parent_destructed);
    EXPECT_TRUE(child_destructed);
}