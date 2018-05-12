#include "stdafx.h"
#include "gtest/gtest.h"

template<class T1, class T2, class TT = T1>
TT add(T1 t1, T2 t2) {
    TT result(t1);
    result += t2;
    return result;
}

// GOAL: learn to build 'compiler errors' for your users
// with static_assert
//
TEST(static_assert_, DISABLED_add_should_only_work_with_numbers)
{
    // this code should compile
    add(1, 2);
    add(.0, 10);

    // this code shouldn't
    add(std::string{ "a" }, std::string{ "b" });
}



