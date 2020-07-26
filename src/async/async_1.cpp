#include <gtest/gtest.h>

#include <thread>
#include <future>
#include <algorithm>
#include <chrono>

#include "perftest.h"
#include "ingredients.hpp"

struct Bolognese {
    Ingredient<Diced<Carrot>> carrots;
    Ingredient<Diced<Paprika>> paprika;
    Ingredient<Cooked<Grated<Meat>>> meat;
};

auto make_sauce() {
    Bolognese sauce {
        diced(Carrot{}, 400),
        diced(Paprika{}, 200),
        cooked(Grated<Meat>{}, 250)
    };
    return Ingredient<Bolognese>{sauce, 1000};
}

struct PastaBolognese {
    Ingredient<Cooked<Pasta>> pasta;
    Ingredient<Grated<Emmental>> cheese;
    Ingredient<Bolognese> sauce;
};

auto make_pasta() {
    auto pasta = PastaBolognese{
        cooked(Pasta{}, 500),
        grated(Emmental{}, 500),
        Ingredient<Bolognese>{make_sauce()}
    };
    return pasta;
}


TEST(AsyncTest, DISABLED_we_can_do_things_in_parallel)
{
    // TODO: tweak the make_pasta and make_sauce functions
    // to do stuff in parallel
    //
    // PURPOSE: learn to use async and gather results from async operations
    EXPECT_GT(1500_ms, duration([&] {
        auto pasta = make_pasta();
    }, 1));
}
