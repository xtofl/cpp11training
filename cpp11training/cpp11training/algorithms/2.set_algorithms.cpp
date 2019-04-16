#include "stdafx.h"

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>

namespace {
    template<class Container>
    struct Contains {
        const Container &container;
        Contains(const Container &c) : container(c) {}

        template<class T>
        bool operator() (const T &value) const {
            return std::find(std::begin(container), std::end(container), value) != std::end(container);
        };
    };

    template<class Container>
    Contains<Container> contains(const Container &c) {
        return Contains<Container>(c);
    }

    template<class Container>
    struct ContainsIf {
        const Container &container;
        ContainsIf(const Container &c) : container(c) {}
        using value_type = typename Container::value_type;
        template<class F>
        bool operator() (const F &f) const {
            return std::find_if(std::begin(container), std::end(container), f) != std::end(container);
        };
    };

    template<class Container>
    ContainsIf<Container> contains_if(const Container &c) {
        return ContainsIf<Container>(c);
    }

    TEST(test_the_test, contains_works)
    {
        const std::vector<int> values{ 1, 2, 3, 4 };
        const auto check = contains(values);
        EXPECT_TRUE(check(2));
        EXPECT_TRUE(check(4));
        EXPECT_FALSE(check(5));
    }

    TEST(test_the_test, contains_if_works)
    {
        const std::vector<int> values{ 1, 2, 3, 4 };
        const auto check = contains_if(values);
        EXPECT_TRUE(check([](int v) { return v % 2 == 0; }));
        EXPECT_TRUE(check([](int v) { return v == 3; }));
        EXPECT_FALSE(check([](int v) { return v > 10; }));
    }
}

TEST(sets, DISABLED_remove_duplicates)
{
    std::vector<int> values{ 1, 2, 2, 3, 4, 5, 6, 6, 8, 8, 9 };
    // TODO: remove duplicates from `values`
    // HINT: only 'unique' values should be present
    for (const auto value : values) {
        EXPECT_EQ(1, std::count(std::begin(values), std::end(values), value));
    }
}

TEST(sets, DISABLED_remove_duplicates_2)
{
    std::vector<int> values{ 1, 2, 2, 3, 4, 5, 6, 6, 8, 8, 9 };
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(std::begin(values), end(values), g);
    // TODO: remove duplicates from `values`
    // HINT: read the preconditions for `unique`!

    for (const auto value : values) {
        EXPECT_EQ(1, std::count(std::begin(values), std::end(values), value));
    }
}

struct Person {
    std::string name;
    std::string surname;
};

bool operator==(const Person &p1, const Person &p2) {
    return std::tie(p1.name, p1.surname) == std::tie(p2.name, p2.surname);
}

class WithSomeData : public ::testing::Test {
public:

    std::vector<Person> classmates{
            { "Ton", "Lathauwers" },
            { "Filip", "Dickens" },
            { "Stephan", "De Schrijver" }
        };
    std::vector<Person> colleagues{
            { "Ton", "Sauerplum" },
            { "Filip", "Dickens" },
            { "Johan", "De Schrijver" }
        };
};


TEST_F(WithSomeData, DISABLED_find_common_elements)
{
    // TODO: implement `common_surnames` to make the tests succeed
    // GOAL: learn that you can use a Comparison function
    // to treat objects as 'same' or 'less'
    //
    auto common_surnames = [](const std::vector<Person> &first, const std::vector<Person> &second)
        -> std::vector<Person>
    {
        return{};
    };

    const auto common = common_surnames(classmates, colleagues);

    EXPECT_EQ(2u, common.size());

    const auto common_contains_if = contains_if(common);
    const auto contains_surname = [&](const std::string n) {
        return common_contains_if([&](const Person &p) { return p.surname == n; });
    };
    EXPECT_TRUE(contains_surname("Dickens"));
    EXPECT_TRUE(contains_surname("De Schrijver"));
    EXPECT_FALSE(contains_surname("Lathauwers"));
    EXPECT_FALSE(contains_surname("Sauerplum"));
}



TEST_F(WithSomeData, DISABLED_find_lost_classmates)
{
     // TODO: implement `in_second_but_not_in_first` to make the tests succeed
     // GOAL: get to know some set algorithms
    auto in_second_but_not_in_first = [](const std::vector<Person> &first, const std::vector<Person> &second)
        -> std::vector<Person>
    {
        return{};
    };

    const auto lost = in_second_but_not_in_first(classmates, colleagues);
    EXPECT_EQ(2u, lost.size());
    const auto lost_contains_if = contains_if(lost);
    const auto lost_person = [&](const Person &p) {
        return lost_contains_if([&](const Person &p2) { return p == p2; });
    };
    EXPECT_TRUE(lost_person({ "Ton", "Lathauwers" }));
    EXPECT_TRUE(lost_person({ "Stephen", "De Schrijver" }));
    EXPECT_FALSE(lost_person({ "Filip", "Dickens" }));
    EXPECT_FALSE(lost_person({ "Ton", "Sauerplum" }));
    EXPECT_FALSE(lost_person({ "Johan", "De Schrijver" }));
}
