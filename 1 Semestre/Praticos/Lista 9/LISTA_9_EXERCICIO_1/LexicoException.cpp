#include "LexicoException.h"

LexicoException::LexicoException(std::string text, int linha, int coluna) {
    this->text = text;
    this->linha = linha;
    this->coluna = coluna;
}

std::string LexicoException::what() {
    return ("ERRO LEXICO. Linha: " 
    + std::to_string(linha)
    + " Coluna: " + std::to_string(coluna)
    + " -> '" + text + "'");
}
