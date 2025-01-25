#include "Algoritmos.h"
#include "Auxiliares.h"
#include <algorithm>
#include <iostream>
#include <map>

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

    for(int cor = 0; cor < k; ++cor) {
        cores[cor] = cor;
    }

    for(int id : pilhaNos) {
        NoGrafo no = grafo.obterNoPorId(id);

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

        std::fill(coresPossiveis.begin(), coresPossiveis.end(), true);
    }

    return true;
}