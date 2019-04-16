#include <thread>
#include <future>
#include <algorithm>
#include <vector>
#include <map>

using Args = std::map<std::string, std::string>;

class Events
{
    // a thread-safe event queue
  public:
    struct Event
    {
        std::string source;
        std::string message;
        bool operator==(const Event &other) const
        {
            return source == other.source && message == other.message;
        }
        Args arguments;
    };
    void push(Event s)
    {
        std::scoped_lock guard(mutex);
        events.emplace_back(std::move(s));
    }

    int index(const Event &e)
    {
        std::scoped_lock guard(mutex);
        auto it = std::find(std::begin(events), std::end(events), e);
        return distance(std::begin(events), it);
    }
    auto find_iterator(const Event &e)
    {
        std::scoped_lock guard(mutex);
        return std::find(std::begin(events), std::end(events), e);
    }
    bool ordered(const Event &e1, const Event &e2)
    {
        std::scoped_lock guard(mutex);
        return find_iterator(e1) < find_iterator(e2);
    }
    const Event &find(const Event &e)
    {
        std::scoped_lock guard(mutex);
        auto it = std::find(std::begin(events), std::end(events), e);
        if (it == std::end(events))
            throw std::invalid_argument(e.message + ", " + e.source);
        return *it;
    }

  private:
    std::recursive_mutex mutex;
    std::vector<Event> events;
};

class TheWeb
{
  public:
    // This is scaffolding to facilitate writing test cases
    // like "this function has been called before that function"

    mutable Events events;
    TheWeb() = default;

    auto get(std::string url) const
    {
        events.push({"get: " + url, "entry"});
        std::this_thread::sleep_for(1000_ms);
        events.push({"get: " + url, "exit"});
        return "results for " + url;
    }

    auto get(std::string url, Args args) const
    {
        events.push({"get: " + url, "entry", std::move(args)});
        std::this_thread::sleep_for(1000_ms);
        events.push({"get: " + url, "exit"});
        return "results for " + url + " with args";
    }
};
