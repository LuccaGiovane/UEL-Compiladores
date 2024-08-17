#include "LexicoException.h"

LexicoException::LexicoException(std::string text) {
    this->text = text;
}

std::string LexicoException::what() {
    return ("ERRO LEXICO: " + text);
}
