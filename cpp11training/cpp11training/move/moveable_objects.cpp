#include "stdafx.h"

#include <gtest/gtest.h>

#include "perftest.h"

TEST(move, speed_this_up)
{
    struct Heavy {
        int * data = nullptr;
        size_t size = 0;
        Heavy() {}
        explicit Heavy(int size)
            : data(new int[size])
            , size(size)
        {}
        Heavy(const Heavy &other)
            : data(new int[other.size])
            , size(other.size)
        {}
        ~Heavy() { delete[] data; }
    };

    auto consume = [](std::vector<Heavy> prototype)
    {
        auto copy = prototype;
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