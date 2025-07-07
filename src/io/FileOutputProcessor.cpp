#include <fstream>
#include "../modules.hpp"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

FileOutputProcessor::FileOutputProcessor(const Graph & graph,
        const string & outputDirectory, bool silentMode) : OutputProcessor(graph, silentMode) {
    this->outputDirectory = outputDirectory;

    if (!silentMode) {
        cout << endl << "Writing into '" << outputDirectory << "' folder." << endl;
    }
}

void FileOutputProcessor::writeData(const string & result, const string & filename) const {
    ofstream dataFile;

    string output = outputDirectory + "/" + filename;
    dataFile.open(output.c_str());

    if (dataFile.is_open()) {
        dataFile << result;

        dataFile.close();
    } else {
        throw FileOutputException("Cannot write into " + output +
                ". Make sure that the folder exists with write permissions.");
    }
}

void FileOutputProcessor::printSummary() const {
    writeData(OutputProcessor::getSummary(), "summary.txt");
}

void FileOutputProcessor::printDistances() const {
    writeData(OutputProcessor::getDistances(), "distances.txt");
}

void FileOutputProcessor::printMatrices() const {
    writeData(OutputProcessor::getMatrices(), "matrices.txt");
}

void FileOutputProcessor::printDot() const {
    writeData(OutputProcessor::getDot(), "graph.dot");
}
