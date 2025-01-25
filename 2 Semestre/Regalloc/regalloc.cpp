#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>

#include "Utilitarios_string.h"
#include "Grafo.h"
#include "Algoritmos.h"
#include "Auxiliares.h"

int main() {
    Grafo grafo;
    std::string linha;
    int controle = 0;
    int numero_de_cores = 0;
    std::vector<std::string> comando_dividido;

    auto processarEntrada = [&](const std::string& texto) {
        if(controle == 0) {
            comando_dividido = dividir(texto, " ");
            grafo = Grafo(std::atoi(comando_dividido[1].c_str()));
        } else if (controle == 1) {
            comando_dividido = dividir(texto, "=");
            numero_de_cores = std::atoi(comando_dividido[1].c_str());
        } else {
            comando_dividido = dividir(texto, " --> ");
            grafo.inserirNo(std::atoi(comando_dividido[0].c_str()), comando_dividido[1]);
        }
        controle++;
    };

    while(std::getline(std::cin, linha)) {
        processarEntrada(linha);
    }

    std::string linhas_separadoras = "----------------------------------------";
    std::cout << "Graph " << grafo.obterIdentificador();
    std::cout << " -> Physical Registers: " << numero_de_cores << std::endl;
    std::cout << linhas_separadoras << std::endl;
    
    std::vector<int> pilhaNos;
    bool concluido;
    std::vector<bool> alocacoes;

    for(int k = numero_de_cores; k > 1; k--) {
        std::cout << linhas_separadoras << std::endl;
        std::cout << "K = " << k << std::endl;
        std::cout << std::endl;

        pilhaNos = simplificar(grafo, k);
        concluido = selecionar(grafo, pilhaNos, k);
        
        alocacoes.push_back(concluido);
    }

    std::cout << linhas_separadoras << std::endl;
    std::cout << linhas_separadoras << std::endl;

    int k_atual = numero_de_cores;
    for(bool sucesso : alocacoes) {
        std::cout << "Graph " << grafo.obterIdentificador() << " -> K = ";
        std::cout << std::setw(std::to_string(numero_de_cores).size()) << k_atual;
        std::cout << ": ";

        if(sucesso) {
            std::cout << "Successful Allocation";
        } else {
            std::cout << "SPILL";
        }

        if(k_atual != 2) {
            std::cout << std::endl;
        }

        k_atual--;
    }

    return 0;
}
