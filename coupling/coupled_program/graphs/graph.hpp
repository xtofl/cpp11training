#pragma once

#include <vector>
#include <string>
#include <memory>
#include <ostream>

struct Node {
    std::string name;
};

struct Edge {
    std::string name;
    Node *a;
    Node *b;
};

// TODO:
//
// install a compilation firewall around
// the graph representation.
//
// In other words, client does not see
// the actual representation of the contained
// members.
//
// Nor does it need to know what a `vector` is
// or a `unique_ptr`.
//
// This removes the coupling to the STL of this class,
// and to the std::unique_ptr C++11 addition.
//
// ADVANCED:
// You may attempt to even use this class
// from a C program.
//
struct Graph {
    Node * addNode(Node n);
    Edge * connect(Node *, Node *);
    std::ostream & dump_to(std::ostream &o) const;
private:
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Edge>> edges;
};
