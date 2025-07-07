#ifndef UNREACHABLEVERTEXEXCEPTION_HPP
#define UNREACHABLEVERTEXEXCEPTION_HPP

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

/**
 * Thrown if two vertices are in different subgraph during path or distance calculations.
 */
class UnreachableVertexException : public runtime_error {
    private:
        string _what;

    public:
        explicit UnreachableVertexException(const string & error_message) :
                runtime_error(error_message), _what(error_message) {}

        virtual ~UnreachableVertexException() throw () {}

        virtual const char * what() const throw () {
            return _what.c_str();
        }
};

#endif // UNREACHABLEVERTEXEXCEPTION_HPP
