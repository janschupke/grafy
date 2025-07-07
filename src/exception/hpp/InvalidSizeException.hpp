#ifndef INVALIDSIZEEXCEPTION_HPP
#define INVALIDSIZEEXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

/**
 * Thrown when trying to create an object of unrealistic size (0x0 matrix).
 */
class InvalidSizeException : public runtime_error {
    private:
        string _what;

    public:
        explicit InvalidSizeException(const string & error_message) :
                runtime_error(error_message), _what(error_message) {}

        virtual ~InvalidSizeException() throw () {}

        virtual const char * what() const throw () {
            return _what.c_str();
        }
};

#endif // INVALIDSIZEEXCEPTION_HPP
