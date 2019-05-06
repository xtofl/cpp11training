#include "graph.hpp"

Node *Graph::addNode(Node n) {
    nodes.push_back(std::make_unique<Node>(std::move(n)));
    return nodes.back().get();
}

Edge *Graph::connect(Node *a, Node *b) {
    std::unique_ptr<Edge> edge{new Edge{"", a, b}};
    edges.push_back(std::move(edge));
    return edges.back().get();
}

std::ostream &Graph::dump_to(std::ostream &o) const {
    o << "Graph: " << "\n";
    for(const auto &n: nodes){
        o << "node " << n->name << ":\n";
        for(const auto &e: edges) {
            if(e->a == n.get()) {
                o << " -> " << e->b->name << "(" << e->name << ")\n";
            }
        }
    }
    return o;
}