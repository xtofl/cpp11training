#include "stdafx.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include "HeavyObject.h"
#include "perftest.h"

TEST(move, DISABLED_speed_this_up)
{
    auto consume = [](std::vector<Heavy> prototype)
    {
        Consumer cons(std::move(prototype));
    };

    auto d = duration([&]
    {
        std::vector<Heavy> prototype{ 100, Heavy{1000} }; // a 100 copies
        consume(prototype);
    }, 10'000);

    EXPECT_LE(
        d,
        std::chrono::milliseconds(1000)) << d;
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
            return Resource{ "?" };
        }
        
        void return_(Resource) {}

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

    pool.return_(r1);
    EXPECT_EQ(2u, pool.size());
    EXPECT_TRUE(pool.contains("one")); 
    EXPECT_TRUE(pool.contains("two"));
}
