#ifndef UTILITARIOS_STRING_H
#define UTILITARIOS_STRING_H

#include <string>
#include <vector>

/**
 * Determina se 'letra' está dentro do intervalo.
 * 
 * 'intervalo' deve ser no formato a-z
 */
bool esta_no_intervalo(char letra, std::string intervalo);

/**
 * Retorna um vetor de strings com as substrings geradas pela separação de 'texto'
 * com base nas ocorrências de 'separador'.
 * 
 * Exemplo 1: separar("teste função separar", " ") -> {"teste", "função", "separar"}
 * Exemplo 2: separar("teste", " ") -> {"teste"}
 */
std::vector<std::string> separar(const std::string &texto, const std::string &separador);

/**
 * Retorna o índice da primeira ocorrência de 'alvo' em 'texto'.
 * 
 * 'texto' e 'alvo' devem ter tamanho > 0 e texto.size() > alvo.size().
 * 
 * Se 'alvo' não está em 'texto', retorna -1.
 */
int contem(std::string texto, std::string alvo);

#endif
