#include "SintaticoException.h"

SintaticoException::SintaticoException(std::string token_recebido, std::string tokens_esperados) {
    this->token_recebido = token_recebido;
    this->tokens_esperados = tokens_esperados;
}

std::string SintaticoException::what() {
    if(token_recebido.compare("")) token_recebido += " "; 
    return ("ERRO SINTATICO EM: "
            + token_recebido + "ESPERADO: " 
            + tokens_esperados);
}
