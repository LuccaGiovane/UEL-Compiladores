#ifndef SINTATICOEXCEPTION_H
#define SINTATICOEXCEPTION_H

#include <exception>
#include <string>

class SintaticoException : std::exception {
    public:
        SintaticoException(std::string token_recebido, std::string tokens_esperados);

        SintaticoException();

        std::string what();

    private:
        std::string token_recebido, tokens_esperados;
        int type;
};


#endif