#pragma once

#include <functional>
#include <chrono>

inline std::chrono::milliseconds operator"" _ms(unsigned long long count) {
    return std::chrono::milliseconds( count );
}

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

inline std::chrono::milliseconds duration(
        std::function<void()> function_under_test,
        long repetitions = 1'000'000)
{
	return duration(function_under_test, repetitions, [] { return std::chrono::high_resolution_clock::now(); });
}

namespace std {
    inline std::ostream &operator<<(std::ostream &out, std::chrono::milliseconds d) {
        return out << d.count() << " ms";
    }
}

