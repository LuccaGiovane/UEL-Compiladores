#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "Grafo.h"
#include <vector>

std::vector<int> simplificar(Grafo grafo, int k);
bool selecionar(Grafo grafo, std::vector<int> pilhaNos, int k);

#endif