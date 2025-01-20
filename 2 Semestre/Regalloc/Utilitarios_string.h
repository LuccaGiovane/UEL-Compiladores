#ifndef UTILITARIOS_STRING_H
#define UTILITARIOS_STRING_H

#include <string>
#include <vector>

/**
 * Retorna o índice da primeira ocorrência de 'alvo' em 'str'.
 * 
 * 'str' e 'alvo' devem ter tamanho > 0 e str.size() > alvo.size().
 * 
 * Se 'alvo' não estiver em 'str', retorna -1.
 */
int contem(std::string str, std::string alvo);

/**
 * Retorna um vetor de strings com as substrings geradas ao separar 'str'
 * baseado nas ocorrências de 'separador'.
 * 
 * Exemplo 1: dividir("teste funcao split", " ") -> {"teste", "funcao", "split"}
 * Exemplo 2: dividir("teste", " ") -> {"teste"}
 */
std::vector<std::string> dividir(const std::string &str, const std::string &separador);

/**
 * Determina se a 'letra' está dentro do 'intervalo'.
 * 
 * 'intervalo' deve ser no formato a-z
 */
bool esta_no_intervalo(char letra, std::string intervalo);

#endif
