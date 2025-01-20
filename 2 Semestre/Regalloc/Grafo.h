#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include "NoGrafo.h"

class Grafo {
    public:
        Grafo() = default;
        Grafo(int identificador);

        int obterIdentificador();
        NoGrafo obterNoPorId(int id);

        /**
         * Adiciona ao grafo o nó com identificador `idNo` e seus vizinhos `vizinhos`.
         * 
         * Os vizinhos devem ser identificados por seus respectivos ids separados
         * por um espaço em branco.
         */
        void inserirNo(int idNo, std::string vizinhos);

        std::vector<NoGrafo> obterNos();

    private:
        int identificador;
        std::vector<NoGrafo> nos;
};

#endif
