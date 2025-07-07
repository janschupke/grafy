#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

/**
 * Holds the information about one particular vertex and it's subgraph membership.
 */
class Vertex {
    private:
        /**
         * Vertex numeric id used for calculations.
         */
        int id;

        /**
         * Numeric value representing a subgraph id.
         */
        int subgraph;

    public:
        /**
         * Creates new vertex.
         *
         * @param id Numeric id of the vertex.
         * @rapam subgraph Id representing subgraph.
         */
        Vertex(int id, int subgraph) : id(id), subgraph(subgraph) {}

        /**
         * Creates a new vertex with id = 0 and subgraph id = 0.
         */
        Vertex() {
            id = 0;
            subgraph = 0;
        }

        int getId() const {
            return id;
        }

        void setId(int id) {
            this->id = id;
        }

        int getSubgraph() const {
            return subgraph;
        }

        void setSubgraph(int subgraph) {
            this->subgraph = subgraph;
        }
};

#endif // VERTEX_HPP
