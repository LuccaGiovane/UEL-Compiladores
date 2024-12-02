#ifndef AST_H
#define AST_H

#include <string>
#include <map>
#include <cmath>
#include <iostream>
#include "matriz.h"

typedef struct structResultado {
    bool isFloat, isDefined;
    float floatValue;
    Matriz *matrixValue;
} structResultado;

class ArvoreSintatica {
protected:
    // 1 = float
    // 2 = matriz
    // 3 = operador binario
    // 4 = variavel
    // 5 = operador unario
    int type;
    std::string var;
    std::string opr;
    float value;
    Matriz *matrix;
    ArvoreSintatica *left, *right, *expr;

    void handleLiteral(structResultado *result);
    void handleMatrix(structResultado *result);
    void handleVariable(
        structResultado *result, 
        std::map<std::string, float> *dicionarioVariaveis,
        std::map<std::string, Matriz *> *dicionarioMatrizes,
        std::map<std::string, std::string> *variaveisNaoEncontradas
    );
    void handleUnaryOperation(
        structResultado *result, 
        std::map<std::string, float> *dicionarioVariaveis,
        std::map<std::string, Matriz *> *dicionarioMatrizes,
        std::map<std::string, std::string> *variaveisNaoEncontradas
    );
    void handleUnaryFloat(structResultado *result, structResultado *expr);
    void handleUnaryMatrix(structResultado *result, structResultado *expr);
    void handleBinaryOperation(
        structResultado *result, 
        std::map<std::string, float> *dicionarioVariaveis, 
        std::map<std::string, Matriz *> *dicionarioMatrizes, 
        std::map<std::string, std::string> *variaveisNaoEncontradas
    );
    void handleBinaryFloat(structResultado *result, structResultado *left, structResultado *right);
    void handleBinaryMatrix(structResultado *result, structResultado *left, structResultado *right);
    void handleMixedOperands(structResultado *result, structResultado *left, structResultado *right);

public:
    ArvoreSintatica(std::string var);

    ArvoreSintatica(float value);

    ArvoreSintatica(std::string opr, ArvoreSintatica *expr);

    ArvoreSintatica(ArvoreSintatica *left, std::string opr, ArvoreSintatica *right);

    structResultado* evaluate(
        std::map<std::string, float> *dicionarioVariaveis, 
        std::map<std::string, Matriz*> *dicionarioMatrizes, 
        std::map<std::string, std::string> *variaveisNaoEncontradas
    );

    std::string rpn();
};


#endif
