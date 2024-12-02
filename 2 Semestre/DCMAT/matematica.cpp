#include "matematica.h"

using namespace std;

void printId(string id, map<string, float>& dicionarioVariaveis, map<string, Matriz*>& dicionarioMatrizes, int precision) {
    if (dicionarioVariaveis.find(id) != dicionarioVariaveis.end()) {
       cout << id << " = " << dicionarioVariaveis[id] << endl;
    }
    else if (dicionarioMatrizes.find(id) != dicionarioMatrizes.end()) {
        dicionarioMatrizes[id]->Matriz::printarMatrizFormatada(precision);
    }
    else {
        cout << "Undefined symbol" << endl;
    }
}

void printSimbolos(map<string, float>& dicionarioVariaveis, map<string, Matriz*>& dicionarioMatrizes) {
    for (auto it = dicionarioVariaveis.begin(); it != dicionarioVariaveis.end(); ++it) {
        const string& key = it->first;
        cout << key << " - FLOAT" << endl;
    }

    for (auto it2 = dicionarioMatrizes.begin(); it2 != dicionarioMatrizes.end(); ++it2) {
        int rows_no = it2->second->Matriz::getRows();
        int cols_no = it2->second->Matriz::getCols();
        const string& key = it2->first;
        cout << key << " - MATRIX [" << rows_no << "][" << cols_no << "]" << endl;
    }
}

void printMatriz(Matriz* matriz, int FLOAT_PRECISION) {
    if(matriz == NULL){
        cout << "No Matrix defined!" << endl;
    }
    else {
        matriz->Matriz::printarMatrizFormatada(FLOAT_PRECISION);
    }
}

float integral(
    float lowerLimit,
    float upperLimit,
    int steps,
    int floatPrecision,
    ArvoreSintatica* expression, 
    map<string, float>& dicionarioVariaveis,
    map<string, Matriz*>& dicionarioMatrizes
) {
    float diff = (upperLimit - lowerLimit) / steps;
    float sum = 0;

    cout << fixed << setprecision(floatPrecision) << endl;

    if (lowerLimit > upperLimit) {
        cout << "ERROR: lower limit must be smaller than upper limit" << endl;
        return 0;
    }

    for (int i = 0; i < steps; i++) {
        float x = ((2 * lowerLimit) + (2 * i * diff) + diff) / 2;
        dicionarioVariaveis["x"] = x; 
        map<string, string> variaveisNaoEncontradas;
        structResultado* result = expression->ArvoreSintatica::evaluate(&dicionarioVariaveis, &dicionarioMatrizes, &variaveisNaoEncontradas);

        if (!result->isFloat || !result->isDefined) {
            printVariaveisNaoEncontradas(&variaveisNaoEncontradas);
            return 0;
        }

        sum += result->floatValue;
    }

    dicionarioVariaveis.erase("x");

    float integralResult = sum * diff;
    cout << integralResult << endl;

    return integralResult;
}

void somatorio(
    const string& identifier,
    int lowerBound,
    int upperBound,
    int floatPrecision,
    ArvoreSintatica* expression,
    map<string, float>& dicionarioVariaveis,
    map<string, Matriz*>& dicionarioMatrizes
) {
    float sum = 0;

    cout << fixed << setprecision(floatPrecision) << endl;

    for (int i = lowerBound; i <= upperBound; i++) {
        dicionarioVariaveis[identifier] = i; 

        map<string, string> variaveisNaoEncontradas;
        structResultado* result = expression->ArvoreSintatica::evaluate(&dicionarioVariaveis, &dicionarioMatrizes, &variaveisNaoEncontradas);

        if (!result->isFloat || !result->isDefined) {
            printVariaveisNaoEncontradas(&variaveisNaoEncontradas);
            return;
        }

        sum += result->floatValue;
    }

    dicionarioVariaveis.erase(identifier);

    cout << sum << endl;
}

void printVariaveisNaoEncontradas(map<string, string> *variaveisNaoEncontradas){
    map<string, string>::iterator it;
    for(it = variaveisNaoEncontradas->begin(); it != variaveisNaoEncontradas->end(); it++){
        if(it->first == "x"){
            cout << "The x variable cannot be present on expressions." << endl;
        }
        else {
            cout << "Undefined symbol [" << it->first << "]" << endl;
        }
    }
}

/*
    Plot
*/

string criarLinha(int tamanho, char caractere = ' ') {
    return string(tamanho, caractere);
}

int calcularPosicao(float valor, float min, float max, int escala) {
    return escala - 1 - (int)(((valor - min) / (max - min)) * (escala - 1));
}

void adicionarEixos(vector<string>& area, int posX, int posY) {
    int linhas = area.size();
    int colunas = area[0].size();

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == posX && j == posY) {
                area[i][j] = '+';
            } else if (i == posX) {
                area[i][j] = '-';
            } else if (j == posY) {
                area[i][j] = '|';
            }
        }
    }
}

vector<string> construirArea(
    bool setAxis,
    float x0, 
    float y0, 
    float x1, 
    float y1
) {
    int linhas = 25, colunas = 80;
    vector<string> area;

    for (int i = 0; i < linhas; i++) {
        area.push_back(criarLinha(colunas));
    }

    if (setAxis) {
        int posX = calcularPosicao(0, y0, y1, linhas);
        int posY = calcularPosicao(0, x0, x1, colunas);
        adicionarEixos(area, posX, posY);
    }

    return area;
}

int calcularPosicaoY(float y, float y0, float y1, int linhas) {
    return calcularPosicao(y, y0, y1, linhas);
}

void adicionarPonto(vector<string>& area, int x, int y) {
    if (y >= 0 && y < area.size()) {
        area[y][x] = '*';
    }
}

void plot(
    vector<ArvoreSintatica*> *listaPlots, 
    map<string, float> *dicionarioVariaveis,
    map<string, Matriz*> *dicionarioMatrizes, 
    map<string, string> *variaveisNaoEncontradas, 
    bool setAxis,
    float x0, 
    float y0, 
    float x1, 
    float y1
) {
    vector<string> area = construirArea(setAxis, x0, y0, x1, y1);

    float diferencaX = (x1 - x0) / 80;

    for (ArvoreSintatica* expressao : *listaPlots) {
        for (int x = 0; x < 80; x++) {
            float posX = x0 + x * diferencaX;
            dicionarioVariaveis->insert({"x", posX});

            structResultado* resultado = expressao->evaluate(dicionarioVariaveis, dicionarioMatrizes, variaveisNaoEncontradas);
            if (!resultado->isFloat || !resultado->isDefined) {
                return;
            }

            float posYValor = resultado->floatValue;
            int posY = calcularPosicaoY(posYValor, y0, y1, 25);

            adicionarPonto(area, x, posY);

            dicionarioVariaveis->erase("x");
        }
    }

    for (const string& linha : area) {
        cout << linha << "\n";
    }
}