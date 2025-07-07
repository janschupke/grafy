#include <fstream>
#include <climits>
#include "../modules.hpp"

using std::vector;
using std::cerr;
using std::endl;

Graph::Graph(const vector<Edge> & edges) : edges(edges) {
    vertexCount = 0;
    componentCount = 0;
    matrixPowers = NULL;
    vertices = NULL;

    calculate();
}

Graph::~Graph() {
    if (vertices) {
        delete [] vertices;
        vertices = NULL;
    }

    if (matrixPowers) {
        delete [] matrixPowers;
        matrixPowers = NULL;
    }
}

bool Graph::vertexExists(const vector<Vertex> * v, int value) const {
    for (vector<Vertex>::const_iterator it = v->begin(); it != v->end(); it++) {
        if (it->getId() == value) {
            return true;
        }
    }

    return false;
}

vector<Vertex> * Graph::extractVertices() const {
    vector<Vertex> * vertexList = new vector<Vertex>();

    // Iterates through provided nodes.
    for (vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); it++) {
        int leftValue = it->getA();
        int rightValue = it->getB();

        // Adds the first value to enable iteration.
        if (vertexList->empty()) {
            vertexList->push_back(Vertex(leftValue, 0));
            if (!vertexExists(vertexList, rightValue)) {
                vertexList->push_back(Vertex(rightValue, 0));
            }
            continue;
        }

        if (!vertexExists(vertexList, leftValue)) {
            vertexList->push_back(Vertex(leftValue, 0));
        }

        if (!vertexExists(vertexList, rightValue)) {
            vertexList->push_back(Vertex(rightValue, 0));
        }
    }

    return vertexList;
}

void Graph::fillVertices() {
    vector<Vertex> * vertexList = extractVertices();

    vertices = new Vertex[vertexList->size()];

    vector<Vertex>::iterator min;
    int index = 0;

    while (!vertexList->empty()) {
        min = vertexList->begin();

        for (vector<Vertex>::iterator it = vertexList->begin(); it != vertexList->end(); it++) {
            if (min->getId() > it->getId()) {
                min = it;
            }
        }

        vertices[index++] = *min;
        vertexList->erase(min);
        vertexCount++;
    }

    delete vertexList;
    vertexList = NULL;
}

void Graph::fillMatrix() {
    matrix.allocate(vertexCount);
    matrix.fill(edges, vertices);
}

void Graph::createTrees() {
    for (int i = 0; i < vertexCount; i++) {
        // First unparsed vertex found in the list.
        if (vertices[i].getSubgraph() == 0) {
            componentCount++;
            vertices[i].setSubgraph(componentCount);
            // Adds to the list of subgraph trees.
            subgraphs.push_back(Tree(vertices[i]));
            // Fills branches.
            (subgraphs.end() - 1)->fill(matrix, vertices);
        }
    }
}

void Graph::calculateMatrixPowers() {
    matrixPowers = new Matrix[vertexCount - 1];

    matrixPowers[0] = matrix * matrix;

    for (int i = 1; i < vertexCount - 1; i++) {
        matrixPowers[i] = matrixPowers[i - 1] * matrix;
    }
}

void Graph::createDistanceMatrix() {
    distanceMatrix.allocate(vertexCount);

    // Number of unreachable nodes - breaks loop is this value gets to 0.
    // ((n * n) - diagonal)
    int infinities = vertexCount * vertexCount - vertexCount;

    // Unreachable by default.
    distanceMatrix.fillWith(-1);

    // Zero distance to itself.
    for (int i = 0; i < vertexCount; i++) {
        distanceMatrix.setValue(i, i, 0);
    }

    // Iterates through matrices (i == (power - 2)).
    for (int i = -1; i < vertexCount - 1; i++) {
        // Iterates through distance matrix cells and updates reachable nodes.
        for (int j = 0; j < vertexCount; j++) {
            for (int k = 0; k < vertexCount; k++) {
                // Adding adjacencies.
                if ((i == -1) && (distanceMatrix.getValue(j, k) == -1) &&
                        (matrix.getValue(j, k) == 1)) {
                    distanceMatrix.setValue(j, k, 1);
                    infinities--;
                }

                // matrixPowers[0] == A^2.
                if ((i >= 0) && (distanceMatrix.getValue(j, k) == -1) &&
                        (matrixPowers[i].getValue(j, k) > 0)) {
                    // Sets the value of the current power.
                    distanceMatrix.setValue(j, k, i + 2);
                    infinities--;
                }

                // All nodes were evaluated.
                if (infinities == 0) return;
            }
        }
    }
}

void Graph::calculate() {
    try {
        fillVertices();
        fillMatrix();
        createTrees();
        calculateMatrixPowers();
        createDistanceMatrix();
    } catch (InvalidIndexException e) {
        cerr << e.what() << endl;
    } catch (InvalidSizeException e) {
        cerr << e.what() << endl;
    }
}

const vector<Edge> & Graph::getEdges() const {
    return edges;
}

const Vertex & Graph::getVertex(int i) const {
    if (i >= vertexCount) {
        throw InvalidIndexException("Vertex with requested index does not exist.");
    }

    return vertices[i];
}

const Matrix & Graph::getMatrix() const {
    return matrix;
}

const Matrix & Graph::getDistanceMatrix() const {
    return distanceMatrix;
}

const Matrix & Graph::getMatrixPower(int power) const {
    if (power == 1) return matrix;
    if (power < 1) {
        throw InvalidIndexException("Requested matrix power is too low.");
    }
    if ((power - 2) > vertexCount) {
        throw InvalidIndexException("Requested matrix power is too high.");
    }

    return matrixPowers[power - 2];
}

int Graph::getDistance(const Vertex & a, const Vertex & b) const {
    if (a.getSubgraph() != b.getSubgraph()) {
        throw UnreachableVertexException("Unreachable.");
    }

    if (a.getId() == b.getId()) return 0;

    int distance = -1;

    // Tree approach:
    // Tree distanceTree(a);
    // distanceTree.fill(matrix, vertices);
    // distance = distanceTree.getDistance(b.getId());

    // Matrix approach:
    int x = 0;
    int y = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (x > 0 && y > 0) {
            break;
        }
        if (vertices[i].getId() == a.getId()) {
            x = i;
        }
        if (vertices[i].getId() == b.getId()) {
            y = i;
        }
    }

    distance = distanceMatrix.getValue(x, y);

    if (distance == INT_MAX || distance == -1) {
        throw UnreachableVertexException("Unreachable.");
    }

    return distance;
}

int Graph::getComponentCount() const {
    return componentCount;
}

int Graph::getVertexCount() const {
    return vertexCount;
}

int Graph::getEdgeCount() const {
    return edges.size();
}

int Graph::getTriangleCount() const {
    // No triangle possible.
    if (this->vertexCount < 3) return 0;

    // Sum of diagonal values.
    int trace = 0;

    try {
        for (int i = 0; i < vertexCount; i++) {
            // Third matrix power.
            trace += matrixPowers[1].getValue(i, i);
        }
    // Should not ever happen.
    } catch (InvalidIndexException & e) {
        cerr << "Triangle calculation: " << e.what() << endl;
    }

    return (trace / 6);
}

bool Graph::isContinuous() const {
    if (componentCount == 1) return true;

    return false;
}
