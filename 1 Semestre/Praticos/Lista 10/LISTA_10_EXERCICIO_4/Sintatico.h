#ifndef SINTATICO_H
#define SINTATICO_H

#include <string>
#include "Lexico.h"

class Sintatico {
    public:
        Sintatico(Lexico lex);

        void advance();

        void eat(int t);

        void setInput(std::string input);

        void error();

        // FUNÇÕES ESPECÍFICAS PARA ESSE PROBLEMA
        void S();

        void E();

        void El();

        void T();

        void Tl();

        void F();

    private:
        int token {};
        Lexico lex {};

        struct ErrorControler {
            int token_recebido;
            std::string tokens_esperados;
        } ERROR_CONTROLER;
};

#endif