#include <list>
#include <iostream>
#include "utilitarios_string.h"

/**
 * Determina se 'letra' está dentro do intervalo especificado.
 * 
 * 'intervalo' deve ser no formato "a-z".
 */
bool esta_no_intervalo(char letra, std::string intervalo) {
    std::vector<std::string> partes = separar(intervalo, "-");
    char minimo = partes[0][0];
    char maximo = partes[1][0];

    bool esta = (letra >= minimo && letra <= maximo);
    
    return esta;
}

/**
 * Retorna um vetor de strings com as substrings geradas pela separação de 'texto'
 * com base nas ocorrências de 'separador'.
 * 
 * Exemplo: separar("teste função separar", " ") -> {"teste", "função", "separar"}
 */
std::vector<std::string> separar(const std::string &texto, const std::string &separador) {
    std::vector<std::string> resultado;
    size_t inicio = 0, fim;

    while ((fim = texto.find(separador, inicio)) != std::string::npos) {
        resultado.push_back(texto.substr(inicio, fim - inicio));
        inicio = fim + separador.size();
    }

    resultado.push_back(texto.substr(inicio));
    return resultado;
}

/**
 * Retorna o índice da primeira ocorrência de 'alvo' em 'texto'.
 * Se 'alvo' não estiver presente, retorna -1.
 */
int contem(std::string texto, std::string alvo) {
    size_t tamanho_texto = texto.size();
    size_t tamanho_alvo = alvo.size();

    // Verificando se a entrada é válida
    if(!tamanho_texto || !tamanho_alvo || tamanho_texto < tamanho_alvo) {
        return -1;
    }

    for(size_t i = 0, j = 0; i < tamanho_texto; i++) {
        // Se um char de 'texto' é igual ao char correspondente em 'alvo'
        if(texto[i] == alvo[j]) {
            j++;
        }
        else {
            j = 0;
        }

        // Se 'alvo' foi encontrado em 'texto'
        if(j == tamanho_alvo) {
            return static_cast<int>(i - j + 1);
        }
    }

    return -1;
}
