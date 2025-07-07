#ifndef FILEOUTPUTPROCESSOR_HPP
#define FILEOUTPUTPROCESSOR_HPP

#include "../../modules.hpp"

using std::string;

/**
 * Takes care of all file related output.
 */
class FileOutputProcessor : public OutputProcessor {
    private:
        string outputDirectory;

    protected:
        /**
         * Writes data into a file.
         *
         * @param result Data to be written.
         * @param filename Name of the file in the output directory.
         */
        void writeData(const string & result, const string & filename) const;

        void printSummary() const;
        void printDistances() const;
        void printMatrices() const;
        void printDot() const;

    public:
        FileOutputProcessor(const Graph & graph, const string & outputDirectory, bool silentMode);
};

#endif // FILEOUTPUTPROCESSOR_HPP
