#ifndef INPUTEXCEPTION_HPP
#define INPUTEXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

/**
 * Thrown in case of an invalid data input.
 */
class InputException : public runtime_error {
    private:
        string _what;

    public:
        explicit InputException(const string & error_message) :
                runtime_error(error_message), _what(error_message) {}

        virtual ~InputException() throw () {}

        virtual const char * what() const throw () {
            return _what.c_str();
        }
};

#endif // INPUTEXCEPTION_HPP
