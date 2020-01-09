#include "stdafx.h"
#include "HeavyObject.h"

Consumer::Consumer(std::array<Heavy, size> prototype)
    : member(std::move(prototype))
{}

void Consumer::access(std::array<Heavy, size> &)
{
}
