#include "SintaticoException.h"

SintaticoException::SintaticoException(std::string token_recebido, std::string tokens_esperados) {
    this->token_recebido = token_recebido;
    this->tokens_esperados = tokens_esperados;
    this->type = 1;
}

SintaticoException::SintaticoException() {
    this->type = 2;
}

std::string SintaticoException::what() {
    std::string retorno;
    switch (type)
    {
        case 1:
            return ("ERRO SINTATICO EM: "
                + token_recebido + " ESPERADO: " 
                + tokens_esperados);
        case 2:
            return "ERRO SINTATICO: CADEIA INCOMPLETA";
        default:
            return "ERRO SINTATICO: ERRO INESPERADO";
    }
}
