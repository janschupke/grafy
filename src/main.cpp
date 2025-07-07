#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include "modules.hpp"

using std::vector;
using std::cerr;
using std::endl;
using std::runtime_error;

vector<Edge> readEdges(const Util & util) {
    InputProcessor inputProcessor(util.isSilentMode());
    vector<Edge> edges;

    if (util.getInputFilename().empty()) {
        edges = inputProcessor.readEdgesFromStdIn();
    } else {
        edges = inputProcessor.readEdgesFromFile(util.getInputFilename());
    }

    return edges;
}

void printOutput(const Util & util, const Graph & graph) {
    OutputProcessor * outputProcessor = NULL;

    if (util.getOutputDirectory().empty()) {
        outputProcessor = new TerminalOutputProcessor(graph, util.isSilentMode());
    } else {
        outputProcessor = new FileOutputProcessor(graph,
                util.getOutputDirectory(), util.isSilentMode());
    }

    outputProcessor->printAll();
    delete outputProcessor;
    outputProcessor = NULL;
}

int main(int argc, char ** argv) {
    Util util;

    if (!util.parseOptions(argc, argv)) {
        return EXIT_FAILURE;
    }

    try {
        vector<Edge> edges = readEdges(util);
        Graph graph(edges);
        printOutput(util, graph);
    } catch (runtime_error e) {
        if (!util.isSilentMode()) {
            cerr << e.what();
            cerr << " Exiting." << endl;
        }

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
