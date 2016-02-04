#pragma once

#include <vector>
#include <algorithm>

struct Heavy {
    int * data = nullptr;
    size_t size = 0;
    Heavy() {}
    explicit Heavy(int size)
        : data(new int[size])
        , size(size)
    {}
    Heavy(const Heavy &other)
        : data(new int[other.size])
        , size(other.size)
    {}
    ~Heavy() { delete[] data; }
};

class Consumer {
public:
    Consumer(std::vector<Heavy> prototype);
    std::vector<Heavy> member;
};
