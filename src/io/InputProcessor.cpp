#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cctype>
#include "../modules.hpp"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;

Edge InputProcessor::parseLine(const string & line) const {
    string currentValue;
    int a = INT_MAX;
    int b = INT_MAX;
    bool aDone = false;

    string::const_iterator startPosition = line.begin();

    // Ignoring leading spaces.
    for (string::const_iterator it = startPosition; it != line.end(); it++) {
        if (!isspace(*it)) {
            startPosition = it;
            break;
        }

        if (it + 1 == line.end()) {
            throw InputException("Expected two values.");
        }
    }

    for (string::const_iterator it = startPosition; it != line.end(); it++) {
        if (!isdigit(*it) && !isspace(*it)) {
            throw InputException("Only digits are allowed.");
        }

        currentValue += *it;

        // Space indicates the next vertex, A reading is done.
        if (!aDone && isspace(*it)) {
            a = atoi(currentValue.c_str());
            currentValue.erase();
            aDone = true;
            // Trims multiple spaces.
            while (isspace(*(it + 1))) it++;
            // Current position can still be space -> skip.
            continue;
        }

        // B reading done, ignoring everything else (e.g. third value).
        if (aDone && isspace(*it)) {
            break;
        }
    }

    b = atoi(currentValue.c_str());

    if (a == INT_MAX || b == INT_MAX) {
        throw InputException("Expected two values.");
    }

    return Edge(a, b);
}

vector<Edge> InputProcessor::readEdgesFromStdIn() const {
    string line;
    vector<Edge> edges;

    if (!silentMode) {
        cout << "Insert graph edges by typing in numeric IDs of vertices ";
        cout << "residing on both ends of the edge, separated by space." << endl;
        cout << "e.g. 1 2" << endl;
        cout << "Terminate by <CTRL> + D" << endl;
        cout << "Edge: ";
    }

    while (getline(cin, line)) {
        try {
            edges.push_back(parseLine(line));
        } catch (InputException e) {
            if (!silentMode) {
                cerr << e.what();
                cerr << " Ignoring last line." << endl;
            }
        }

        if (!silentMode) {
            cout << "Edge: ";
        }
    }

    if (edges.empty()) {
        throw InputException("Graph is empty.");
    }

    return edges;
}

vector<Edge> InputProcessor::readEdgesFromFile(const string & filename) const {
    string line;
    vector<Edge> edges;
    ifstream inputFile(filename.c_str());

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            // Can throw exception. Handled by caller instead of here,
            // since this is not an interactive input that could utilize error hints.
            edges.push_back(parseLine(line));
        }

        inputFile.close();
    } else {
        throw FileInputException("Could not read the input file '" + filename + "'.");
    }

    if (edges.empty()) {
        throw InputException("Graph is empty.");
    }

    return edges;
}
