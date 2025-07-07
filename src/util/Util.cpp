#ifndef UTIL_CPP
#define UTIL_CPP

#include <iostream>
#include <sstream>
#include <unistd.h>
#include "../modules.hpp"

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

const string Util::getHelp() const {
    ostringstream oss;

    oss << "Grafy - Usage:" << endl;
    oss << "grafy [-s] [-o directory] [-i file]" << endl;
    oss << "\t-s: Silent mode. Suppresses all interactive printouts." << endl;
    oss << "\t-o: Output directory. Uses standard out, if not specified." << endl;
    oss << "\t-i: Input file. Uses standard in, if not specified." << endl;
    oss << endl;

    return oss.str();
}

bool Util::parseOptions(int argc, char ** argv) {
    int option;

    while ((option = getopt(argc, argv, "so:i:h")) != -1) {
        switch (option) {
            case 's':
                silentMode = true;
                break;

            case 'o':
                outputDirectory = optarg;
                break;

            case 'i':
                inputFilename = optarg;
                break;

            case 'h':
                cout << getHelp();
                return false;

            default:
                cout << getHelp();
                return false;
        }
    }

    for (int index = optind; index < argc; index++) {
        cout << "Unknown argument " << argv[index] << endl;
        cout << getHelp();
        return false;
    }

    return true;
}

bool Util::isSilentMode() const {
    return silentMode;
}

const string & Util::getOutputDirectory() const {
    return outputDirectory;
}

const string & Util::getInputFilename() const {
    return inputFilename;
}

#endif // UTIL_CPP
