#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <vector>

/**
 * Holds the information about one link between two nodes.
 */
class Edge {
    private:
        int a, b;

    public:
        /**
         * Creates a new edge between provided vertices.
         *
         * @param a One end of the edge.
         * @param b Other end of the edge.
         */
        Edge(int a, int b) : a(a), b(b) {}

        int getA() const {
            return a;
        }

        int getB() const {
            return b;
        }
};

#endif // EDGE_HPP
