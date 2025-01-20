#include <iostream>
#include "Grafo.h"

// Construtor usando lista de inicialização
Grafo::Grafo(int identificador)
    : identificador(identificador), nos()
{}

// Retorna todos os nós do grafo
std::vector<NoGrafo> Grafo::obterNos() {
    return nos;
}

// Insere um novo nó com o identificador e vizinhos fornecidos
void Grafo::inserirNo(int idNo, std::string vizinhos) {
    nos.push_back(NoGrafo(idNo, vizinhos));
}

// Itera sobre os nós para encontrar o nó com o id especificado
NoGrafo Grafo::obterNoPorId(int buscaId) {
    for (size_t idx = 0; idx < nos.size(); ++idx) {
        NoGrafo& noAtual = nos[idx];
        if(noAtual.obterIdentificador() == buscaId) {
            return noAtual;
        }
    }
    // Retorna um NoGrafo padrão se não encontrar
    return NoGrafo();
}

// Retorna o identificador do grafo
int Grafo::obterIdentificador() {
    return identificador;
}
