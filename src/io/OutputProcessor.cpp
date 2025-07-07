#include <sstream>
#include "../modules.hpp"

using std::endl;
using std::ostringstream;
using std::string;
using std::vector;
using std::cerr;
using std::cout;

OutputProcessor::~OutputProcessor() {
    if (!silentMode) {
        cout << "Success." << endl;
    }
}

string OutputProcessor::getEdges() const {
    ostringstream oss;

    for (vector<Edge>::const_iterator it = graph.getEdges().begin();
            it != graph.getEdges().end(); it++) {
        oss << "[ " << it->getA() << " , " << it->getB() << " ]" << endl;
    }

    return oss.str();
}

string OutputProcessor::getVertices() const {
    ostringstream oss;

    for (int i = 0; i < graph.getVertexCount(); i++) {
        oss << "[ vertex: " << graph.getVertex(i).getId() << " , component: ";
        oss << graph.getVertex(i).getSubgraph() << " ]" << endl;
    }

    return oss.str();
}

string OutputProcessor::getSummary() const {
    ostringstream oss;

    oss << "Full adjacency matrix:";
    oss << graph.getMatrix() << endl;
    oss << "Distance matrix:";
    oss << graph.getDistanceMatrix() << endl;
    oss << "Main edge list:" << endl;
    oss << getEdges() << endl;
    oss << "Vertex list and component flag:" << endl;
    oss << getVertices() << endl;
    oss << "Summary:" << endl;
    oss << "\tIs continuous: " << (graph.isContinuous() ? "Yes." : "No.") << endl;
    oss << "\tComponent count: " << graph.getComponentCount() << endl;
    oss << "\tVertex count: " << graph.getVertexCount() << endl;
    oss << "\tEdges: " << graph.getEdgeCount() << endl;
    oss << "\tTriangles: " << graph.getTriangleCount() << endl;
    oss << endl;

    return oss.str();
}

string OutputProcessor::getDistances() const {
    ostringstream oss;

    int distance;
    for (int i = 0; i < graph.getVertexCount(); i++) {
        oss << "Distance from " << graph.getVertex(i).getId() << " to:" << endl;

        for (int j = 0; j < graph.getVertexCount(); j++) {
            oss << "\t" << graph.getVertex(j).getId() << ": ";

            try {
                distance = graph.getDistance(graph.getVertex(i), graph.getVertex(j));

                oss << distance << endl;
            } catch (UnreachableVertexException e) {
                oss << e.what() << endl;
            }
        }

        oss << endl;
    }

    return oss.str();
}

string OutputProcessor::getMatrices() const {
    ostringstream oss;

    oss << "Matrix powers:" << endl << endl;

    try {
        for (int i = 1; i <= graph.getVertexCount(); i++) {
            oss << "A^" << i << ":" << graph.getMatrixPower(i) << endl;
        }
    } catch (InvalidIndexException & e) {
        cerr << e.what() << endl;
    }

    return oss.str();
}

string OutputProcessor::getDot() const {
    ostringstream oss;

    oss << "digraph math {" << endl;
    oss << "\tlabelloc=\"t\";" << endl;
    oss << "\tlabel=\"Graph\";" << endl;
    oss << endl;

    // Declares nodes.
    for (int i = 0; i < graph.getVertexCount(); i++) {
        oss << "\t" << graph.getVertex(i).getId() << ";" << endl;
    }

    oss << endl;

    // Links nodes.
    for (vector<Edge>::const_iterator it = graph.getEdges().begin();
            it != graph.getEdges().end(); it++) {
        oss << "\t" << it->getA() << "->" << it->getB() << ";" << endl;
    }

    oss << "}" << endl;

    return oss.str();
}

void OutputProcessor::printAll() const {
    printSummary();
    printDistances();
    printMatrices();
    printDot();
}
