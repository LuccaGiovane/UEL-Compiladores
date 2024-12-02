#include "ast.h"

using namespace std;

ArvoreSintatica::ArvoreSintatica(float value) {
    this->type = 1;
    this->value = value;
}

ArvoreSintatica::ArvoreSintatica(ArvoreSintatica *left, string opr, ArvoreSintatica *right) {
    this->type = 3;
    this->opr = opr;
    this->left = left;
    this->right = right;
}

ArvoreSintatica::ArvoreSintatica(string var) {
    this->type = 4;
    this->var = var;
}

ArvoreSintatica::ArvoreSintatica(string opr, ArvoreSintatica *expr) {
    this->type = 5;
    this->opr = opr;
    this->expr = expr;
}

void ArvoreSintatica::handleLiteral(structResultado *result) {
    result->floatValue = this->value;
}

void ArvoreSintatica::handleMatrix(structResultado *result) {
    result->matrixValue = this->matrix;
    result->isFloat = false;
}

void ArvoreSintatica::handleVariable(
    structResultado *result, map<string, float> *dicionarioVariaveis,
    map<string, Matriz *> *dicionarioMatrizes,
    map<string, string> *variaveisNaoEncontradas
) {
    if (dicionarioVariaveis->find(this->var) != dicionarioVariaveis->end()) {
        result->floatValue = dicionarioVariaveis->at(this->var);
    } else if (dicionarioMatrizes->find(this->var) != dicionarioMatrizes->end()) {
        result->matrixValue = dicionarioMatrizes->at(this->var);
        result->isFloat = false;
    } else {
        result->isDefined = false;
        if (variaveisNaoEncontradas->find(this->var) == variaveisNaoEncontradas->end()) {
            variaveisNaoEncontradas->insert(pair<string, string>(this->var, this->var));
        }
    }
}

void ArvoreSintatica::handleUnaryOperation(
    structResultado *result, map<string, float> *dicionarioVariaveis,
    map<string, Matriz *> *dicionarioMatrizes,
    map<string, string> *variaveisNaoEncontradas
) {
    structResultado *expr = this->expr->evaluate(dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);

    if (!expr->isDefined) {
        result->isDefined = false;
        return;
    }

    if (expr->isFloat) {
        handleUnaryFloat(result, expr);
    } else {
        handleUnaryMatrix(result, expr);
    }
}

void ArvoreSintatica::handleUnaryFloat(structResultado *result, structResultado *expr) {
    if (this->opr == "neg") {
        result->floatValue = expr->floatValue * -1;
    } else if (this->opr == "pos") {
        result->floatValue = expr->floatValue;
    } else if (this->opr == "sen") {
        result->floatValue = sin(expr->floatValue);
    } else if (this->opr == "cos") {
        result->floatValue = cos(expr->floatValue);
    } else if (this->opr == "tan") {
        result->floatValue = tan(expr->floatValue);
    } else if (this->opr == "abs") {
        result->floatValue = fabs(expr->floatValue);
    }
}

void ArvoreSintatica::handleUnaryMatrix(structResultado *result, structResultado *expr) {
    if (this->opr == "neg") {
        result->matrixValue = expr->matrixValue->mul(-1);
        result->isFloat = false;
        result->isDefined = result->matrixValue != NULL;
    } else if (this->opr == "pos") {
        result->matrixValue = expr->matrixValue;
        result->isFloat = false;
        result->isDefined = result->matrixValue != NULL;
    } else {
        result->isDefined = false;
        cout << "Incorrect type for operator '" << this->opr << "' - have MATRIX" << endl;
    }
}

void ArvoreSintatica::handleBinaryOperation(
    structResultado *result, 
    map<string, float> *dicionarioVariaveis, 
    map<string, Matriz *> *dicionarioMatrizes, 
    map<string, string> *variaveisNaoEncontradas
) {
    structResultado *left = this->left->evaluate(dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);
    structResultado *right = this->right->evaluate(dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);

    if (!left->isDefined || !right->isDefined) {
        result->isDefined = false;
        return;
    }

    if (left->isFloat && right->isFloat) {
        handleBinaryFloat(result, left, right);
    } else if (!left->isFloat && !right->isFloat) {
        handleBinaryMatrix(result, left, right);
    } else {
        handleMixedOperands(result, left, right);
    }
}

void ArvoreSintatica::handleBinaryFloat(structResultado *result, structResultado *left, structResultado *right) {
    if (this->opr == "add") {
        result->floatValue = left->floatValue + right->floatValue;
    } else if (this->opr == "sub") {
        result->floatValue = left->floatValue - right->floatValue;
    } else if (this->opr == "mul") {
        result->floatValue = left->floatValue * right->floatValue;
    } else if (this->opr == "div") {
        result->floatValue = left->floatValue / right->floatValue;
    } else if (this->opr == "pot") {
        result->floatValue = pow(left->floatValue, right->floatValue);
    } else if (this->opr == "mod") {
        result->floatValue = fmod(left->floatValue, right->floatValue);
    }
}

void ArvoreSintatica::handleBinaryMatrix(structResultado *result, structResultado *left, structResultado *right) {
    result->isFloat = false;

    if (this->opr == "add") {
        result->matrixValue = left->matrixValue->add(right->matrixValue);
    } else if (this->opr == "sub") {
        result->matrixValue = left->matrixValue->sub(right->matrixValue);
    } else if (this->opr == "mul") {
        result->matrixValue = left->matrixValue->mul(right->matrixValue);
    } else {
        result->isDefined = false;
        cout << "Incorrect operator for MATRIX: " << this->opr << endl;
    }

    result->isDefined = result->matrixValue != NULL;
}

void ArvoreSintatica::handleMixedOperands(structResultado *result, structResultado *left, structResultado *right) {
    structResultado *floatExpr = left->isFloat ? left : right;
    structResultado *matrixExpr = left->isFloat ? right : left;

    if (this->opr == "mul") {
        result->matrixValue = matrixExpr->matrixValue->mul(floatExpr->floatValue);
        result->isFloat = false;
        result->isDefined = result->matrixValue != NULL;
    } else {
        result->isDefined = false;
        cout << "Incorrect type for operator '" << this->opr << "' - have "
                  << (left->isFloat ? "FLOAT and MATRIX" : "MATRIX and FLOAT") << endl;
    }
}

structResultado *ArvoreSintatica::evaluate(
    map<string, float> *dicionarioVariaveis, 
    map<string, Matriz *> *dicionarioMatrizes,
    map<string, string> *variaveisNaoEncontradas
) {
    structResultado *result = new structResultado();
    result->isFloat = true;
    result->isDefined = true;

    if (this->type == 1) {
        handleLiteral(result);
    } else if (this->type == 2) {
        handleMatrix(result);
    } else if (this->type == 3) {
        handleBinaryOperation(result, dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);
    } else if (this->type == 4) {
        handleVariable(result, dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);
    } else if (this->type == 5) {
        handleUnaryOperation(result, dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);
    }

    return result;
}

string ArvoreSintatica::rpn() {
    string rpn = "";
    if (this->type == 1) {
        rpn += to_string(this->value);
    } else if (this->type == 2) {
    } else if (this->type == 3) {
        string opr;
        if (this->opr == "add") {
            opr = "+";
        } else if (this->opr == "sub") {
            opr = "-";
        } else if (this->opr == "mul") {
            opr = "*";
        } else if (this->opr == "div") {
            opr = "/";
        } else if (this->opr == "pot") {
            opr = "^";
        } else if (this->opr == "mod") {
            opr = "%";
        }
        rpn += this->left->rpn() + " " + this->right->rpn() + " " + opr;
    } else if (this->type == 4) {
        rpn += this->var;
    } else if (this->type == 5) {
        string opr;
        if (this->opr == "neg") {
            opr = "-";
        } else if (this->opr == "pos") {
            opr = "+";
        } else if (this->opr == "sen") {
            opr = "SEN";
        } else if (this->opr == "cos") {
            opr = "COS";
        } else if (this->opr == "tan") {
            opr = "TAN";
        } else if (this->opr == "abs") {
            opr = "ABS";
        }
        rpn += this->expr->rpn() + " " + opr;
    }

    return rpn;

}