#include "Auxiliares.h"
#include <algorithm>

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