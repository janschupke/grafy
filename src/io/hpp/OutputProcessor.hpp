#ifndef OUTPUTPROCESSOR_HPP
#define OUTPUTPROCESSOR_HPP

#include <iostream>
#include "../../modules.hpp"

using std::string;

/**
 * Abstract output handler.
 */
class OutputProcessor {
    protected:
        const Graph & graph;

        /**
         * If true, some console outputs are suppressed.
         */
        const bool silentMode;

        /**
         * Formulates information about the graph's edges into a string.
         *
         * @return Requested information.
         */
        string getEdges() const;

        /**
         * Formulates information about the graph's vertices into a string.
         *
         * @return Requested information.
         */
        string getVertices() const;

        /**
         * Formulates summary graph information into a string.
         *
         * @return Requested information.
         */
        string getSummary() const;

        /**
         * Formulates information about the distances between every two edges into a string.
         *
         * @return Requested information.
         */
        string getDistances() const;

        /**
         * Formulates information about the graph's matrix and its powers into a string.
         *
         * @return Requested information.
         */
        string getMatrices() const;

        /**
         * Creates a .dot source file that visualises the whole graph.
         *
         * @return Requested information.
         */
        string getDot() const;

        /**
         * Prints a summary about this graph.
         */
        virtual void printSummary() const = 0;

        /**
         * Prints the shortest distance from every node to every node. Omits duplications and a->a paths.
         */
        virtual void printDistances() const = 0;

        /**
         * Prints a text representation of all matrix powers.
         */
        virtual void printMatrices() const = 0;

        /**
         * Prints the .dot source code.
         */
        virtual void printDot() const = 0;

    public:
        OutputProcessor(const Graph & graph, bool silentMode) : graph(graph), silentMode(silentMode) {}
        virtual ~OutputProcessor() = 0;

        /**
         * Calls all print methods.
         */
        void printAll() const;
};

#endif // OUTPUTPROCESSOR_HPP
