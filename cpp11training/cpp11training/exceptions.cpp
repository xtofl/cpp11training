#include "stdafx.h"
#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

namespace dont_touch {
    class Resource {
    public:
        Resource(int i){
            if (i % 4 == 0) {
                throw std::runtime_error("not enough space for resource");
            }
        }
    };
}
using namespace dont_touch;

namespace {

    struct Destructible {
        std::function<void()> destructed = []{};
        ~Destructible(){ destructed(); }
    };

    struct ResourceBuilder {
        void addResources(const std::vector<int> &resource_ids)
        {
            for (auto i: resource_ids)
            {
                resources.emplace_back(i);
            }
        }
        std::vector<Resource> resources;
    };
}

TEST(exceptions, DISABLED_we_can_guarantee_strong_exception_safety)
{
    // TODO: design the ResourceBuilder so that it has
    // strong exception safety guarantee
    // HINT: guard your invariants!
    ResourceBuilder builder;

    try {
        std::vector<int> resource_ids{{1, 2, 3, 4, 5, 6, 7, 8}};
        builder.addResources(resource_ids);
    } catch(const std::runtime_error &){
        EXPECT_TRUE(builder.resources.empty());
        return;
    }
    FAIL() << "test must exit through exceptional path";
}

TEST(exceptions, DISABLED_objects_dont_leak)
{
    bool destructed = false;
    try {
        {
            // TODO: adapt this block so that
            // a doesn't leak
            // HINT: use a value type
            auto a = new Destructible();
            a->destructed = [&]{ destructed = true;};
        }

        throw std::runtime_error("");
    } catch(const std::runtime_error &) {
        EXPECT_TRUE(destructed);
    }
}


namespace dont_touch {

    double divide(double a, double b) {
        if (b == 0.0) throw std::runtime_error("div by zero");
        return a/b;
    }
    class Median {
    public:
        Median(double sum, double count)
            : value(divide(sum, count))
        {
        }
        double value;
    };
    class Variance {
    public:
        Variance(double sum_squares, double sum, double count)
            : value(divide(sum_squares - divide(sum*sum, count)
                           , count - 1))
        {}
        double value;
    };
    using Value = double;
    using Sample = std::vector<Value>;
    class Distribution {
    public:
        Distribution(Sample sample)
            : sum(std::accumulate(begin(sample), end(sample), Value{}))
            , count(sample.size())
            , m(sum, count)
        {}
        int sum;
        int count;

        Median m;
    };
    template<typename Iterator>
    auto make_distributions(Iterator b, Iterator e)
    {
        std::vector<Distribution> result;
        for(auto it = b; it != e; ++it){
            result.emplace_back(*it);
        }
        return result;
    }
}
using namespace dont_touch;

