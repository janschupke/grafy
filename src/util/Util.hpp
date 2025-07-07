#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

using std::string;

/**
 * Takes care of miscellaneous functionality, such as command line parameter parsing.
 */
class Util {
    private:
        /**
         * If true, interactive prompt messages are suppressed.
         */
        bool silentMode;

        /**
         * Output directory for results.
         */
        string outputDirectory;

        /**
         * Input file containing edge information.
         */
        string inputFilename;

    public:
        Util() {
            silentMode = false;
        };

        /**
         * Returns parameter and argument explanation.
         *
         * @return Parameter and argument explanation.
         */
        const string getHelp() const;

        /**
         * Parses command line parameters and arguments and sets variables' values accordingly.
         */
        bool parseOptions(int argc, char ** argv);

        bool isSilentMode() const;
        const string & getOutputDirectory() const;
        const string & getInputFilename() const;
};

#endif // UTIL_HPP
