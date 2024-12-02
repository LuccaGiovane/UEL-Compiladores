#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <iostream>
#include <iomanip>

class Matriz {
public:
    Matriz(int rows_no, int cols_no);
    Matriz(std::vector <std::vector<float>> *celulas);
    Matriz *add(Matriz *m);
    Matriz *sub(Matriz *m);
    Matriz *mul(Matriz *m);
    Matriz *mul(float value);
    int getRows();
    int getCols();
    float determinante();
    void printarMatrizFormatada(int precisao);
    void sistemaLinear(int precisao);
private:
    int rows_no, cols_no;
    float **celulas;
    Matriz* criarMatrizAumentada();
    void realizarEliminacaoGaussiana(Matriz *sistema);
    int encontrarLinhaPivo(Matriz *sistema, int coluna);
    void trocarLinhas(Matriz *sistema, int linha1, int linha2);
    void eliminarColuna(Matriz *sistema, int coluna);
    bool verificarDeterminanteESolucao(Matriz *sistema);
    Matriz* resolverMatrizTriangularSuperior(Matriz *sistema);
    void imprimirSolucao(Matriz *solucao);
    Matriz* inicializarMatrizL();
    Matriz* copiarMatrizParaU();
    int realizarDecomposicaoLU(Matriz *l, Matriz *u);
    int trocarLinhasSeNecessario(Matriz *u, int linhaAtual);
    float calcularDeterminanteU(Matriz *u);

};

#endif
