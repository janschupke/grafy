#include <climits>
#include <vector>
#include <deque>
#include "../modules.hpp"

using std::vector;
using std::deque;
using std::min;

Tree::Tree(const Vertex & vertex) {
    this->parent = NULL;
    this->depth = 1;
    this->vertex = vertex;
}

Tree::Tree(Tree * parent, const Vertex & vertex) {
    this->parent = parent;

    if (parent) {
        this->depth = (parent->depth) + 1;
    } else {
        this->depth = 1;
    }

    this->vertex = vertex;
}

void Tree::fill(const Matrix & matrix, Vertex * vertices) {
    int position = 0;

    // Finds relevant line.
    for (int i = 0; i < matrix.getSize(); i++) {
        if (vertices[i].getId() == vertex.getId()) {
            position = i;
            break;
        }
    }

    // Lists through matrix line.
    for (int i = 0; i < matrix.getSize(); i++) {
        // Finds edge flag in the main matrix && iterates up the branch to look for the edge.
        if (matrix.getValue(position, i) == 1 && !isDuplicate(vertices[i])) {
            // Adds node.
            nodes.push_back(Tree(this, vertices[i]));

            // Updates subgraph flag in the new node.
            (nodes.end() - 1)->setSubgraph(vertex.getSubgraph());

            // Update subgraph flag in the vertex list.
            vertices[i].setSubgraph(vertex.getSubgraph());

            // Calls itself for the new node.
            (nodes.end() - 1)->fill(matrix, vertices);
        }

        // Finds edge flag in the main matrix && iterates up the branch to look for the edge.
        if (matrix.getValue(i, position) == 1 && !isDuplicate(vertices[i])) {
            // Adds node.
            nodes.push_back(Tree(this, vertices[i]));

            // Updates subgraph flag in the new node.
            (nodes.end() - 1)->setSubgraph(vertex.getSubgraph());

            // Update subgraph flag in the vertex list.
            vertices[i].setSubgraph(vertex.getSubgraph());

            // Calls itself for the new node.
            (nodes.end() - 1)->fill(matrix, vertices);
        }
    }
}

int Tree::getDistance(int id) const {
    // Found - returns current depth.
    if (this->vertex.getId() == id) return (this->depth - 1);

    // No more branches - not found.
    if (nodes.size() == 0) return INT_MAX;

    int distance = INT_MAX;

    // Goes through the branches, saves the lowest value.
    for (vector<Tree>::const_iterator it = nodes.begin(); it < nodes.end(); it++) {
        distance = min(it->getDistance(id), distance);
    }

    return distance;
}

const Vertex & Tree::getVertex() const {
    return vertex;
}

const vector<Tree> & Tree::getNodes() const {
    return nodes;
}

const Tree * Tree::getParent() const {
    return parent;
}

void Tree::setSubgraph(int subgraph) {
    vertex.setSubgraph(subgraph);
}

bool Tree::isDuplicate(const Vertex & vertex) const {
    // Found.
    if (this->vertex.getId() == vertex.getId()) return true;

    // Root - not found.
    if (this->depth == 1) return false;

    bool result = false;
    result = parent->isDuplicate(vertex);

    return result;
}
