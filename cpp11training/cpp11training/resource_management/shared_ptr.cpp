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
        std::shared_ptr<Resource> resource;
    };

}


TEST(shared_ptr, resource_is_cleant_up_after_last_user_gone)
{
    auto resource = std::make_shared<Resource>();
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
    resource = nullptr;
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
        std::shared_ptr<Pool::Handle> h(
            new Pool::Handle(pool.allocate()),
            [&](Pool::Handle* h) { pool.free(*h); delete h; });

        ASSERT_EQ(0, *h);
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
    ~Parent() { destructed(); }
};

class Child {
public:
    Child(const std::shared_ptr<Parent>& parent) : parent(parent) {}
    void call_parent() {
        parent.lock()->call();
    }
    std::weak_ptr<Parent> parent;
    std::function<void()> destructed = [] {};
    ~Child() { destructed(); }
};

TEST(shared_ptr, breaking_cycles)
{
    bool parent_destructed = false;
    bool parent_called = false;
    bool child_destructed = false;
    {
        auto parent = std::make_shared<Parent>();
        parent->destructed = [&] { parent_destructed = true; };
        parent->call = [&] { parent_called = true; };

        parent->children.emplace_back(std::make_shared<Child>(parent));
        parent->children.back()->destructed = [&] { child_destructed = true; };

        parent->children.back()->call_parent();
        EXPECT_TRUE(parent_called);
    }
    EXPECT_TRUE(parent_destructed);
    EXPECT_TRUE(child_destructed);
}