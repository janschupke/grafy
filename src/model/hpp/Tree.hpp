#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>

using std::vector;

/**
 * Tree represents one node within a given tree, containing pointers to it's subtrees.
 */
class Tree {
    private:
        /**
         * Distance from the root.
         */
        int depth;

        /**
         * This node's vertex, containing id.
         */
        Vertex vertex;

        /**
         * Pointer to the parent node.
         */
        Tree * parent;

        /**
         * List of this node's descendants.
         */
        vector<Tree> nodes;

    public:
        /**
         * Creates 1 tree node without a parent.
         *
         * @param vertex Vertex contains relevant data, like id.
         */
        explicit Tree(const Vertex & vertex);

        /**
         * Creates 1 tree node with link to it's parent.
         *
         * @param parent Parent node.
         * @param vertex Vertex contains relevant data, like id.
         */
        Tree(Tree * parent, const Vertex & vertex);

        /**
         * Recursively adds nodes to the tree.
         */
        void fill(const Matrix & matrix, Vertex * vertices);

        /**
         * Recursively searches the whole tree to find the closest occurence of the given id.
         */
        int getDistance(int id) const;

        const Vertex & getVertex() const;
        const vector<Tree> & getNodes() const;
        const Tree * getParent() const;

        /**
         * This does not discard qualifiers, so you can stfu, thank you very much.
         */
        void setSubgraph(int subgraph);

        /**
         * Searches a tree branch towards the root to find the given vertex.
         *
         * @param vertex The vertex that is being searched for.
         * @return True if the vertex is found, false otherwise.
         */
        bool isDuplicate(const Vertex & vertex) const;
};

#endif // TREE_HPP
