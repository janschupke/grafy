#ifndef TERMINALOUTPUTPROCESSOR_HPP
#define TERMINALOUTPUTPROCESSOR_HPP

#include "../../modules.hpp"

/**
 * Takes care of all terminal / stdout related output.
 */
class TerminalOutputProcessor : public OutputProcessor {
    protected:
        void printSummary() const;
        void printDistances() const;
        void printMatrices() const;
        void printDot() const;

    public:
        TerminalOutputProcessor(const Graph & graph, bool silentMode) : OutputProcessor(graph, silentMode) {}
};

#endif // TERMINALOUTPUTPROCESSOR_HPP
