#ifndef LEXICOEXCEPTION
#define LEXICOEXCEPTION

#include <exception>
#include <string>

class LexicoException : public std::exception {
    public:
        LexicoException(std::string text, int linha, int coluna);

        std::string what();

    private:
        std::string text;
        int linha, coluna;
};

#endif