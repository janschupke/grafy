#ifndef FILEINPUTEXCEPTION_HPP
#define FILEINPUTEXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

/**
 * Thrown when the input file cannot be successfully read.
 */
class FileInputException : public runtime_error {
    private:
        string _what;

    public:
        explicit FileInputException(const string & error_message) :
                runtime_error(error_message), _what(error_message) {}

        virtual ~FileInputException() throw () {}

        virtual const char * what() const throw () {
            return _what.c_str();
        }
};

#endif // FILEINPUTEXCEPTION_HPP
