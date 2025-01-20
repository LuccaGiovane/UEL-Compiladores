#include <list>
#include <iostream>
#include "Utilitarios_string.h"

// Função auxiliar para verificar validade de entrada em contem.
static bool entrada_valida(const std::string &str, const std::string &alvo) {
    return !str.empty() && !alvo.empty() && str.size() >= alvo.size();
}

// Função auxiliar para executar a lógica de comparação em contem.
static int procura_ocorrencia(const std::string &str, const std::string &alvo, size_t tamanhoStr, size_t tamanhoAlvo) {
    size_t j = 0;
    for (size_t i = 0; i < tamanhoStr; ++i) {
        if (str[i] == alvo[j]) {
            ++j;
        } else {
            j = 0;
        }
        if (j == tamanhoAlvo) {
            return static_cast<int>(i - j + 1);
        }
    }
    return -1;
}

int contem(std::string str, std::string alvo) {
    size_t tamanhoStr = str.size();
    size_t tamanhoAlvo = alvo.size();

    if (!entrada_valida(str, alvo)) {
        return -1;
    }
    return procura_ocorrencia(str, alvo, tamanhoStr, tamanhoAlvo);
}

bool esta_no_intervalo(char letra, std::string intervalo) {
    auto limites = dividir(intervalo, "-");

    // Funções auxiliares para extrair limites
    auto extrai_min = [&]() -> char {
        return limites.size() > 0 && !limites[0].empty() ? limites[0][0] : '\0';
    };

    auto extrai_max = [&]() -> char {
        return limites.size() > 1 && !limites[1].empty() ? limites[1][0] : '\0';
    };

    char minimo = extrai_min();
    char maximo = extrai_max();

    return (letra >= minimo && letra <= maximo);
}

std::vector<std::string> dividir(const std::string &str, const std::string &separador) {
    std::vector<std::string> partes;
    size_t inicio = 0;
    size_t pos_encontrada = 0;

    // Função auxiliar para adicionar um segmento à lista
    auto adiciona_segmento = [&](size_t start, size_t end) {
        partes.push_back(str.substr(start, end - start));
    };

    while ((pos_encontrada = str.find(separador, inicio)) != std::string::npos) {
        adiciona_segmento(inicio, pos_encontrada);
        inicio = pos_encontrada + separador.size();
    }

    partes.push_back(str.substr(inicio));
    return partes;
}
