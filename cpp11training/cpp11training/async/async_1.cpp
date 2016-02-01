#include "stdafx.h"

#include <gtest/gtest.h>

#include <thread>
#include <future>

#include "perftest.h"

std::chrono::milliseconds operator"" _ms(unsigned long long count) {
    return std::chrono::milliseconds(count);
}

namespace www {

    auto get_web_page(std::string url)
    {
        std::this_thread::sleep_for(1000_ms);
        return "results for " + url;
    }

    template<class Urls>
    auto get_parallel(const Urls &urls)
    {
        for (const auto &url : urls)
        {
            www::get_web_page(url);
        }
    }

    const std::string urls[] = {
        "http://google.com", "http://yahoo.com", "http://sioux.eu"
    };
}

TEST(async_1, DISABLED_we_can_delegate_stuff)
{
    EXPECT_GT(2 * 1000_ms, duration([] {www::get_parallel(www::urls); }, 1));
}