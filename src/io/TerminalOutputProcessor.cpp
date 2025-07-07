#include <fstream>
#include "../modules.hpp"

using std::cout;

void TerminalOutputProcessor::printSummary() const {
    cout << OutputProcessor::getSummary();
}

void TerminalOutputProcessor::printDistances() const {
    cout << OutputProcessor::getDistances();
}

void TerminalOutputProcessor::printMatrices() const {
    cout << OutputProcessor::getMatrices();
}

void TerminalOutputProcessor::printDot() const {
    cout << OutputProcessor::getDot();
}
