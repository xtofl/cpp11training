#include "stdafx.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include "HeavyObject.h"
#include "perftest.h"

// TODO: add move support to `HeavyObject` class
//
TEST(move, DISABLED_speed_this_up_by_adding_move_support)
{
    auto constructing_objects = duration([&]
    {
        // construct
        std::array<Heavy, Consumer::size> prototype;
        std::generate(begin(prototype), end(prototype), [] { return Heavy{ 1000 }; });
        // and do stuff with it so that this loop
        // can't be optimized away (by the compiler)
        Consumer::access(prototype);
    }, 10'000);

    auto consuming_objects = duration([&]
    {
        // construct
        std::array<Heavy, Consumer::size> prototype;
        std::generate( begin(prototype), end(prototype), [] { return Heavy{ 1000 }; });
        // and move to sink
        Consumer cons(std::move(prototype));
    }, 10'000);

    EXPECT_TRUE(consuming_objects < constructing_objects * 1.1)
        << "consuming: " << consuming_objects
        << " vs. constructing: " << constructing_objects;
}



TEST(move, DISABLED_there_should_be_only_one_owner)
{
    class Resource {
    public:
        Resource(std::string id)
            : id(std::move(id))
        {}

        std::string id;
    };

    class Pool {
    public:
        Pool()
            : resources{ {Resource{"one"}, Resource{"two"}} }
        {}
        size_t size() const {
            return resources.size();
        }
        
        Resource borrow() {
            Resource r = std::move(resources.front());
            resources.erase(resources.begin());
            return r;
        }
        
        void return_(Resource &&r) {
            resources.emplace_back(std::move(r));
        }

        bool contains(const std::string &id) const
        {
            return std::any_of(begin(resources), end(resources),
                [&](const auto &resource) { return resource.id == id; });
        }
    private:
        std::vector<Resource> resources;
    };


    Pool pool;
    auto r1 = pool.borrow();
    EXPECT_EQ("one", r1.id);
    EXPECT_EQ(1u, pool.size());
    EXPECT_FALSE(pool.contains("one"));
    EXPECT_TRUE(pool.contains("two"));

    pool.return_(std::move(r1));
    EXPECT_EQ(2u, pool.size());
    EXPECT_TRUE(pool.contains("one")); 
    EXPECT_TRUE(pool.contains("two"));
}
