#ifndef LEXICOEXCEPTION
#define LEXICOEXCEPTION

#include <exception>
#include <string>

class LexicoException : public std::exception {
    public:
        LexicoException(std::string text);

        std::string what();

    private:
        std::string text;
};

#endif