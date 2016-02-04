#include "stdafx.h"
#include "HeavyObject.h"

Consumer::Consumer(std::vector<Heavy> prototype)
    : member(std::move(prototype))
{}
