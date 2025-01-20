#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "NoGrafo.h"
#include "Utilitarios_string.h"  // Mantendo a referência ao utilitário de strings

// Função auxiliar para converter um vetor de strings em inteiros.
static std::vector<int> converterStringsParaInts(const std::vector<std::string>& listaStr) {
    std::vector<int> valores;
    valores.reserve(listaStr.size());
    for (const auto& token : listaStr) {
        valores.push_back(std::atoi(token.c_str()));
    }
    return valores;
}

// Construtor de NoGrafo usando lista de inicialização
NoGrafo::NoGrafo(int id, std::string vizinhosStr)
    : identificador(id)
{
    vizinhos = definirVizinhos(vizinhosStr);
    conexoes = static_cast<int>(vizinhos.size());
}

// Retorna o número de conexões do nó
int NoGrafo::obterConexoes() const {
    return conexoes;
}

// Ajusta o número de conexões
void NoGrafo::ajustarConexoes(int novasConexoes) {
    conexoes = novasConexoes;
}

// Define os vizinhos a partir de uma string
std::vector<int> NoGrafo::definirVizinhos(std::string vizinhosStr) {
    std::vector<std::string> tokensVizinhos = dividir(vizinhosStr, " ");
    return converterStringsParaInts(tokensVizinhos);
}

// Retorna o identificador do nó
int NoGrafo::obterIdentificador() const {
    return identificador;
}

// Retorna a lista de vizinhos
std::vector<int> NoGrafo::obterVizinhos() {
    return vizinhos;
}
