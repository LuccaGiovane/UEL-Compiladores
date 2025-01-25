#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "NoGrafo.h"
#include <vector>

bool comparador_min(const NoGrafo& no1, const NoGrafo& no2);
bool comparador_max(const NoGrafo& no1, const NoGrafo& no2);
int obterNoMinimo(std::vector<NoGrafo> nos);
int obterNoMaximo(std::vector<NoGrafo> nos);
std::vector<NoGrafo> atualizarNos(std::vector<NoGrafo> nos, int id);

#endif