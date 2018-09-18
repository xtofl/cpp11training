#include "stdafx.h"

#include <gtest/gtest.h>

#include <thread>
#include <future>
#include <algorithm>
#include <map>

#include "perftest.h"

class TheWeb {
public:
    // This is scaffolding to facilitate writing test cases
    // like "this function has been called before that function"
    using Args = std::map<std::string, std::string>;
    class Events {
        // a thread-safe event queue
    public:
        struct Event {
            std::string source;
            std::string message;
            bool operator == (const Event &other) const {
                return source == other.source && message == other.message;
            }
            Args arguments;
        };
        void push(Event s) {
            std::scoped_lock guard(mutex);
            events.emplace_back(std::move(s));
        }

        int index(const Event &e) {
            std::scoped_lock guard(mutex);
            auto it = std::find(std::begin(events), std::end(events), e);
            return distance(std::begin(events), it);
        }
        auto find_iterator(const Event &e) {
            std::scoped_lock guard(mutex);
            return std::find(std::begin(events), std::end(events), e);
        }
        bool ordered(const Event &e1, const Event &e2) {
            std::scoped_lock guard(mutex);
            return find_iterator(e1) < find_iterator(e2);
        }
        const Event &find(const Event &e) {
            std::scoped_lock guard(mutex);
            auto it = std::find(std::begin(events), std::end(events), e);
            if (it == std::end(events)) throw std::invalid_argument(e.message + ", " + e.source);
            return *it;
        }

    private:
        std::recursive_mutex mutex;
        std::vector<Event> events;
    };

    mutable Events events;
    TheWeb() = default;

    auto get(std::string url) const
    {
        events.push({"get: "+url, "entry"});
        std::this_thread::sleep_for(1000_ms);
        events.push({"get: " + url, "exit" });
        return "results for " + url;
    }

    auto post(std::string url, Args args) const
    {
        events.push({ "post: " + url, "entry", std::move(args) });
        std::this_thread::sleep_for(1000_ms);
        events.push({ "post: " + url, "exit"});
        return "posted to " + url;
    }

    template<class Urls>
    auto get_parallel(const Urls &urls) const
    {
        events.push({ "get_parallel: ", "entry" });
        for (const auto &url : urls)
        {
            get(url);
        }
        events.push({ "get_parallel: ", "exit" });
        return 0;
    }
};

const std::vector<std::string> urls{
    "http://google.com", "http://yahoo.com", "http://sioux.eu"
};

TheWeb theWeb;

TEST(AsyncTest, DISABLED_we_can_delegate_stuff)
{
    // TODO: tweak get_parallel in order to start retrieving all
    // urls simultaneously
    // PURPOSE: express parallelism, use std::async
    EXPECT_GT(2 * 1000_ms, duration([&] {theWeb.get_parallel(urls); }, 1));
}

TEST(AsyncTest, DISABLED_we_can_wait_for_delegated_stuff)
{
    // TODO: make sure the `post` call uses the results received from the `get` call
    // HINT: `get` should return a future, `post` should get an overload to
    // consume it, and forward to the regular `post`.
    // PURPOSE: control execution over interdependent tasks
    //
    auto google = theWeb.get("http://google.com");
    auto correct = theWeb.post("http://spell_checker.com", {{"text", google}});

    auto &events = theWeb.events;
    EXPECT_TRUE(events.ordered(
        { "get: http://google.com", "exit" },
        { "post: http://spell_checker.com", "entry" }));

    EXPECT_EQ("results for http://google.com",
              events.find({ "post: http://spell_checker.com", "entry" })
                    .arguments.at("text"));
}

TEST(AsyncTest, DISABLED_we_can_delay_execution_till_input_is_known)
{
    TheWeb::Events events;

    const auto task = [&](int size) {
        events.push({ "task: n received: " + std::to_string(size), "" });
        for (int i = 0; i != size; ++i) {
            std::this_thread::sleep_for(100_ms);
        }
        events.push({ "task returns " + std::to_string(size), "" });
        return size;
    };
    // TODO: redefine above `task` so that it can wait
    // for its argument, and that client code
    // can wait for its return value.
    // HINT: ... accept and return a future and store the result in a promise.

    int input = 0;
    auto result_fut = std::async(std::launch::async,
        task, input);

    auto input_defined = std::async(std::launch::async, [&] {
        events.push({ "input defined", "" });
        input = 10;
    });

    const auto result = result_fut.get();
    input_defined.wait();
    events.push({ "{return value known: " + std::to_string(result), "" });

    EXPECT_EQ(10, result);
    EXPECT_TRUE(events.ordered({ "input defined", "" }, { "task: n received: 10", "" }));
    EXPECT_TRUE(events.ordered({ "task returns 10", "" }, { "{return value known: 10", "" }));
}


struct AsyncForResult {
    void wait() {}
};
// F should be a function returning a std::future<void()>
template<typename F>
AsyncForResult async_for_n(int N, F f)
{
    for (auto i=0; i != N; ++i) f();
    return {};
};

TEST(AsyncTest, DISABLED_keep_a_loop_going)
{
    // TODO: change the `async_for_n` function to keep
    // repeating its argument N times, asynchronously
    // GOAL: allow the equivalent of a for-loop to be written asynchronously
    // LEVEL: ADVANCED
    // HINT: loop body and condition are now separated.
    // apparent recursion is going to be needed.
    std::atomic<int> counter{ 0 };
    auto task = [&] { return std::async(std::launch::async, [&] { ++counter; }); };

    bool task_done = false;
    auto value = async_for_n(10, task);
    value.wait();
    EXPECT_EQ(10, counter);
}