#ifndef INPUTPROCESSOR_HPP
#define INPUTPROCESSOR_HPP

#include "../../modules.hpp"

/**
 * Takes care of all user input.
 */
class InputProcessor {
    private:
        /**
         * If true, some console outputs are suppressed.
         */
        const bool silentMode;

        /**
         * Parses a single input line into an edge instance.
         *
         * @param line Input file.
         * @return Parsed edge.
         * @throws InputException if the input line cannot be successfully parsed.
         */
        Edge parseLine(const string & line) const;

    public:
        explicit InputProcessor(bool silentMode) : silentMode(silentMode) {}

        /**
         * Reads edges from the standard input.
         *
         * @return List of edges.
         */
        vector<Edge> readEdgesFromStdIn() const;

        /**
         * Reads edges from the provided file.
         *
         * @param filename Name of the input file.
         * @return List of edges.
         * @throws FileInputException If the file reading fails.
         */
        vector<Edge> readEdgesFromFile(const string & filename) const;
};

#endif // INPUTPROCESSOR_HPP
