#ifndef LEXICO_H
#define LEXICO_H

#include <string>

#include "Automato.h"

class Lexico {
    public:
        Lexico();

        /**
         * Informa qual o input que será utilizado para obtenção dos tokens
        */
        void setInput(std::string input_str);

        /**
         * Retorna o texto que gerou o último token obtido
        */
        std::string getText();

        /**
         * Retorna valores inteiros que correspondem aos tokens aceitos pelo léxico
         * 
         * Retornos especiais:
         *  -1 -> Indica fim do input sem '\0' encontrado
         *  0  -> Indica '\0'
         *  -2 -> Indica erro
        */
        int gerarToken();

        /**
         * Retorna o erro Léxico identificado
        */
        void error();
    
    private:
        std::string input {};
        std::string text {};
        int start_token;
        int last_final_pos;
};

#endif