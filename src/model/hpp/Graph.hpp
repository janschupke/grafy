#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using std::vector;

/**
 * Main structure of the application.
 * Uses all the other structures and stores all the information within itself.
 * There is only 1 instance of graph.
 */
class Graph {
    private:
        /**
         * Amount of vertices the graph consists of.
         */
        int vertexCount;

        /**
         * Amount of components (separate subgraphs) in the graph.
         */
        int componentCount;

        /**
         * Basic graph matrix, holds information about existing edges.
         */
        Matrix matrix;

        /**
         * Holds information about the minimal distance between any two vertices.
         */
        Matrix distanceMatrix;

        /**
         * Array of all possible matrix powers excluding the first one, which is stored
         * in its own field.
         */
        Matrix * matrixPowers;

        /**
         * Array of all vertices.
         */
        Vertex * vertices;

        /**
         * List of all edges.
         */
        const vector<Edge> edges;

        /**
         * List of subgraph trees. There is a tree for every one subgraph in the graph.
         */
        vector<Tree> subgraphs;

        /**
         * Goes through the vertex list to check the value occurrence.
         *
         * @param v Provided vertex list.
         * @param value Searched value - vertex id.
         * @return true if vertex exists, false otherwise.
         */
        bool vertexExists(const vector<Vertex> * v, int value) const;

        /**
         * Extracts vertices from the edge list into vertex list.
         *
         * @return List of extracted vertices.
         */
        vector<Vertex> * extractVertices() const;

        /**
         * Parses vertex list into an array, sorting elements on the way.
         */
        void fillVertices();

        /**
         * Allocates the graph matrix and fills it with values. Vertices and edges are used for this.
         */
        void fillMatrix();

        /**
         * Goes through the vertex list in order to assign a subgraph value to each of them.
         * Creates a tree for each component.
         */
        void createTrees();

        /**
         * Calculates all the matrix powers from ^2 up to the vertexCount in the graph.
         */
        void calculateMatrixPowers();

        /**
         * Calculates node distances based on matrix powers.
         * Results is preserved in the distanceMatrix field.
         */
        void createDistanceMatrix();

        /**
         * Aggregate method that calls all the calculations and fills all fields with correct values.
         */
        void calculate();

    public:
        /**
         * Reads edge values from input and copies them into a member vector.
         *
         * @param edges Provided list of edges.
         */
        explicit Graph(const vector<Edge> & edges);
        ~Graph();

        /**
         * Retrieves the list of all edges.
         *
         * @return List of edges.
         */
        const vector<Edge> & getEdges() const;

        /**
         * Retrieves vertex residing on provided array index.
         *
         * @param i Vertex array index.
         * @return Vertex instance.
         * @throws InvalidIndexException When index is higher that the array size.
         */
        const Vertex & getVertex(int i) const;

        /**
         * Retrieves the graph's edge matrix.
         *
         * @return Edge matrix.
         */
        const Matrix & getMatrix() const;

        /**
         * Retrieves the graph's distance matrix.
         *
         * @return Distance matrix.
         */
        const Matrix & getDistanceMatrix() const;

        /**
         * Retrieves matrix power of the provided value.
         *
         * @param power Requested matrix power.
         * @return Matrix power instance.
         * @throws InvalidIndexException When the requested power is higher than the amount of vertices or lower than 1.
         */
        const Matrix & getMatrixPower(int power) const;

        /**
         * Calculates the distance from vertex a to vertex b.
         *
         * @param a Starting vertex.
         * @param b Destination vertex.
         * @return Minimum amount of steps, or infinity (INT_MAX) if unreachable.
         * @throws UnreachableVertexException If vertices are in different subgraphs.
         */
        int getDistance(const Vertex & a, const Vertex & b) const;

        /**
         * Retrieves the amount of components (discontinuous subgraphs).
         *
         * @return Amount of components.
         */
        int getComponentCount() const;

        /**
         * Retrieves the amount of vertices in the graph.
         *
         * @return Amount of vertices.
         */
        int getVertexCount() const;

        /**
         * Retrieves the amount of edges in the graph.
         *
         * @return Amount of edges.
         */
        int getEdgeCount() const;

        /**
         * Retrieves the amount of triangles in the graph.
         *
         * @return Amount of triangles.
         */
        int getTriangleCount() const;

        /**
         * Returns the information about the continuity of this graph.
         *
         * @return True if this graph only has one component, false otherwise.
         */
        bool isContinuous() const;
};

#endif // GRAPH_HPP
