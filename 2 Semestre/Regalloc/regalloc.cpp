#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>

#include "Utilitarios_string.h"
#include "Grafo.h"

// Declarações de funções auxiliares com nomenclatura em português e tipos atualizados
std::vector<int> simplificar(Grafo grafo, int k);
bool selecionar(Grafo grafo, std::vector<int> pilhaNos, int k);
bool comparador_min(const NoGrafo& no1, const NoGrafo& no2);
bool comparador_max(const NoGrafo& no1, const NoGrafo& no2);
int obterNoMinimo(std::vector<NoGrafo> nos);
int obterNoMaximo(std::vector<NoGrafo> nos);
std::vector<NoGrafo> atualizarNos(std::vector<NoGrafo> nos, int id);

int main() {
    // BUILD - construção do grafo
    Grafo grafo;
    std::string linha;
    int controle = 0;
    int numero_de_cores = 0;
    std::vector<std::string> comando_dividido;

    // Função auxiliar para processar a linha de entrada
    auto processarEntrada = [&](const std::string& texto) {
        if(controle == 0) {
            // Nome do grafo
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

    // INICIAR RELATÓRIO com saída em inglês
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

        // INICIAR SIMPLIFY && POTENTIAL SPILL
        pilhaNos = simplificar(grafo, k);

        // INICIAR SELECT/ASSIGN && SPILL
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
}

// Implementações das funções auxiliares com nomes em português

std::vector<int> simplificar(Grafo grafo, int k) {
    std::vector<NoGrafo> nos = grafo.obterNos();
    std::vector<int> pilhaNos;

    while(!nos.empty()) {
        int posicaoMin = obterNoMinimo(nos);
        int idNo;

        std::cout << "Push: ";
        if(nos[posicaoMin].obterConexoes() >= k) {
            int posicaoMax = obterNoMaximo(nos);
            idNo = nos[posicaoMax].obterIdentificador();
            std::cout << idNo << " *" << std::endl;
        } else {
            idNo = nos[posicaoMin].obterIdentificador();
            std::cout << idNo << std::endl;
        }

        pilhaNos.insert(pilhaNos.begin(), idNo);
        nos = atualizarNos(nos, idNo);
    }

    return pilhaNos;
}

bool selecionar(Grafo grafo, std::vector<int> pilhaNos, int k) {
    std::map<int, int> cores;
    std::vector<bool> coresPossiveis(k, true);

    // Inicializar mapa de cores disponíveis
    for(int cor = 0; cor < k; ++cor) {
        cores[cor] = cor;
    }

    for(int id : pilhaNos) {
        NoGrafo no = grafo.obterNoPorId(id);

        // Verificar cores possíveis para o nó atual
        for(int vizinho : no.obterVizinhos()) {
            auto it = cores.find(vizinho);
            if(it != cores.end()) {
                if(it->second < static_cast<int>(coresPossiveis.size()))
                    coresPossiveis[it->second] = false;
            }
        }

        std::cout << "Pop: " << id << " -> ";
        auto itCor = std::find(coresPossiveis.begin(), coresPossiveis.end(), true);
        if(itCor == coresPossiveis.end()) {
            std::cout << "NO COLOR AVAILABLE" << std::endl;
            return false;
        }

        int corEscolhida = static_cast<int>(itCor - coresPossiveis.begin());
        cores[id] = corEscolhida;
        std::cout << corEscolhida << std::endl;

        // Resetar possibilidades para próximo nó
        std::fill(coresPossiveis.begin(), coresPossiveis.end(), true);
    }

    return true;
}

bool comparador_min(const NoGrafo& no1, const NoGrafo& no2) {
    if(no1.obterConexoes() == no2.obterConexoes())
        return no1.obterIdentificador() < no2.obterIdentificador();
    return no1.obterConexoes() < no2.obterConexoes();
}

bool comparador_max(const NoGrafo& no1, const NoGrafo& no2) {
    if(no1.obterConexoes() == no2.obterConexoes())
        return no1.obterIdentificador() > no2.obterIdentificador();
    return no1.obterConexoes() < no2.obterConexoes();
}

int obterNoMinimo(std::vector<NoGrafo> nos) {
    auto minimo = std::min_element(nos.begin(), nos.end(), comparador_min);
    return static_cast<int>(std::distance(nos.begin(), minimo));
}

int obterNoMaximo(std::vector<NoGrafo> nos) {
    auto maximo = std::max_element(nos.begin(), nos.end(), comparador_max);
    return static_cast<int>(std::distance(nos.begin(), maximo));
}

std::vector<NoGrafo> atualizarNos(std::vector<NoGrafo> nos, int id) {
    std::vector<NoGrafo> resultado;
    for(auto& no : nos) {
        std::vector<int> vizinhos = no.obterVizinhos();
        if(std::find(vizinhos.begin(), vizinhos.end(), id) != vizinhos.end()) {
            no.ajustarConexoes(no.obterConexoes() - 1);
        }
        if(no.obterIdentificador() != id) {
            resultado.push_back(no);
        }
    }
    return resultado;
}
