#include <iostream>
#include "graphs/graph.hpp"

int main(int argc, const char **args) {
    Graph graph;

    auto n1 = graph.addNode({"A"});
    auto n2 = graph.addNode({"B"});
    auto n3 = graph.addNode({"C"});

    graph.connect(n1, n2)->name = "a-b";
    graph.connect(n1, n3)->name = "a-c";

    graph.dump_to(std::cout);
    return 0;
}