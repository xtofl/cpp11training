#pragma once

#include <functional>
#include <chrono>

// I wish it could be done like this...
//auto duration = [](
//    auto function_under_test,
//    long repetitions = 1'000'000,
//    auto clock = [] { return std::chrono::high_resolution_clock::now(); }
//    )
template<class Clock>
std::chrono::milliseconds duration(
        std::function<void()> function_under_test,
        long repetitions,
        Clock clock
    )
{
    const auto before = clock();
    for (int i = 0; i != repetitions; ++i) function_under_test();
    const auto after = clock();
    return std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
};

std::chrono::milliseconds duration(
        std::function<void()> function_under_test,
        long repetitions = 1'000'000)
{
	return duration(function_under_test, repetitions, [] { return std::chrono::high_resolution_clock::now(); });
}

namespace pretty_time {
    std::ostream &operator<<(std::ostream &out, std::chrono::milliseconds d) {
        return out << d.count() << " ms";
    }
}

using namespace pretty_time;
using pretty_time::operator<<;
