#ifndef NOGRAFO_H
#define NOGRAFO_H

#include <string>
#include <vector>

class NoGrafo {
    public:
        NoGrafo() = default;
        NoGrafo(int identificador, std::string vizinhos);

        int obterIdentificador() const;
        int obterConexoes() const;
        void ajustarConexoes(int conexoes);
        std::vector<int> obterVizinhos();

    private:
        int identificador;
        int conexoes;
        std::vector<int> vizinhos;

        std::vector<int> definirVizinhos(std::string vizinhos);
};

#endif
