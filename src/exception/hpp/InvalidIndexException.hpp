#ifndef INVALIDINDEXEXCEPTION_HPP
#define INVALIDINDEXEXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

/**
 * Thrown in case of accessing invalid matrix cell
 * or requesting any other out of range array index.
 */
class InvalidIndexException : public runtime_error {
    private:
        string _what;

    public:
        explicit InvalidIndexException(const string & error_message) :
                runtime_error(error_message), _what(error_message) {}

        virtual ~InvalidIndexException() throw () {}

        virtual const char * what() const throw () {
            return _what.c_str();
        }
};

#endif // INVALIDINDEXEXCEPTION_HPP
