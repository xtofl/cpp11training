#pragma once

#include <functional>
#include <chrono>

// I wish it could be done like this...
//auto duration = [](
//    auto function_under_test,
//    long repetitions = 1'000'000,
//    auto clock = [] { return std::chrono::high_resolution_clock::now(); }
//    )
std::chrono::milliseconds duration(
        std::function<void()> function_under_test,
        long repetitions = 1'000'000,
        std::function<std::chrono::time_point<std::chrono::steady_clock>()> clock = [] { return std::chrono::high_resolution_clock::now(); }
    )
{
    const auto before = clock();
    for (int i = 0; i != repetitions; ++i) function_under_test();
    const auto after = clock();
    return std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
};


namespace pretty_time {
    std::ostream &operator<<(std::ostream &out, std::chrono::milliseconds d) {
        return out << d.count() << " ms";
    }
}

using namespace pretty_time;
using pretty_time::operator<<;
