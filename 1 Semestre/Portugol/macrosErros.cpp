#include <iostream>
#include <cstdlib>

#define ERRO_SINTATICO                            \
    this->col_no = this->col_no - this->token_content.length();  \
    std::cout << "ERRO DE SINTAXE. Linha: " << this->line_no           \
         << " Coluna: " << this->col_no                           \
         << " -> \'" << this->token_content << "\'";              \
    std::exit(0);

#define ERRO_LEXICO                               \
    this->col_no = this->col_no - this->token_content.length();  \
    std::cout << "ERRO LEXICO. Linha: " << this->line_no              \
         << " Coluna: " << this->col_no                          \
         << " -> \'" << this->token_content << "\'";             \
    std::exit(0);
