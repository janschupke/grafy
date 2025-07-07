#ifndef FILEOUTPUTEXCEPTION_HPP
#define FILEOUTPUTEXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

/**
 * Thrown in case of any file output error.
 */
class FileOutputException : public runtime_error {
    private:
        string _what;

    public:
        explicit FileOutputException(const string & error_message) :
                runtime_error(error_message), _what(error_message) {}

        virtual ~FileOutputException() throw () {}

        virtual const char * what() const throw () {
            return _what.c_str();
        }
};

#endif // FILEOUTPUTEXCEPTION_HPP
