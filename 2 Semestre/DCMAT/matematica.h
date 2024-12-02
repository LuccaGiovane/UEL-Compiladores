#ifndef MATEMATICA_H
#define MATEMATICA_H

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include "matriz.h"
#include "ast.h"

#define PI_CONST 3.14159265
#define EULER_CONST 2.71828182

void plot(
    std::vector<ArvoreSintatica*> *listaPlots, 
    std::map<std::string, float> *dicionarioVariaveis,
    std::map<std::string, Matriz*> *dicionarioMatrizes, 
    std::map<std::string, std::string> *variaveisNaoEncontradas, 
    bool setAxis,
    float x0, 
    float y0, 
    float x1, 
    float y1
);

void printVariaveisNaoEncontradas(std::map<std::string, std::string> *variaveisNaoEncontradas);

void printId(
    std::string id, 
    std::map<std::string, float>& dicionarioVariaveis, 
    std::map<std::string, Matriz*>& dicionarioMatrizes, 
    int precision
);

void printSimbolos(
    std::map<std::string, float>& dicionarioVariaveis, 
    std::map<std::string, Matriz*>& dicionarioMatrizes
);

void printMatriz(Matriz* matriz, int FLOAT_PRECISION);

float integral(
    float lowerLimit,
    float upperLimit,
    int steps,
    int floatPrecision,
    ArvoreSintatica* expression, 
    std::map<std::string, float>& dicionarioVariaveis,
    std::map<std::string, Matriz*>& dicionarioMatrizes
);

void somatorio(
    const std::string& identifier,
    int lowerBound,
    int upperBound,
    int floatPrecision,
    ArvoreSintatica* expression,
    std::map<std::string, float>& dicionarioVariaveis,
    std::map<std::string, Matriz*>& dicionarioMatrizes
);



#endif