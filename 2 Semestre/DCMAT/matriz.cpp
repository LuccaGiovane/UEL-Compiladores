#include "matriz.h"

Matriz::Matriz(int rows_no, int cols_no) {
    this->rows_no = rows_no;
    this->cols_no = cols_no;
    this->celulas = new float*[rows_no];
    for(int i = 0; i < rows_no; i++) {
        this->celulas[i] = new float[cols_no];
    }
}

Matriz::Matriz(std::vector <std::vector<float>> *celulas) {
    int biggestCol = 0;

    this->rows_no = celulas->size();

    for(int i = 0; i < celulas->size(); i++) {
        if(celulas->at(i).size() > biggestCol) {
            biggestCol = celulas->at(i).size();
        }
    }

    this->cols_no = biggestCol;

    this->celulas = new float*[this->rows_no];
    for(int i = 0; i < this->rows_no; i++) {
        this->celulas[i] = new float[this->cols_no];
    }

    for(int i = 0; i < this->rows_no; i++) {
        for(int j = 0; j < this->cols_no; j++) {
            if(j < celulas->at(i).size()) {
                this->celulas[i][j] = celulas->at(i).at(j);
            }
            else {
                this->celulas[i][j] = 0;
            }
        }
    }

}

Matriz * Matriz::add(Matriz *m) {
    Matriz *result = new Matriz(this->rows_no, this->cols_no);

    if(this->rows_no != m->Matriz::getRows()|| this->cols_no != m->cols_no) {
        std::cout << "Incorrect dimensions for operator \'+\' - have MATRIX [" << this->rows_no << "][" << this->cols_no << "] and MATRIX [" << m->Matriz::getRows()<< "][" << m->Matriz::getCols()<< "]" << std::endl;
        return NULL;
    }

    for(int i = 0; i < this->rows_no; i++) {
        for(int j = 0; j < this->cols_no; j++) {
            result->celulas[i][j] = this->celulas[i][j] + m->celulas[i][j];
        }
    }

    return result;
}

Matriz* Matriz::sub(Matriz *m) {
    Matriz *result = new Matriz(this->rows_no, this->cols_no);

    if(this->rows_no != m->Matriz::getRows()|| this->cols_no != m->cols_no) {
        std::cout << "Incorrect dimensions for operator \'-\' - have MATRIX [" << this->rows_no << "][" << this->cols_no << "] and MATRIX [" << m->Matriz::getRows()<< "][" << m->Matriz::getCols()<< "]" << std::endl;
        return NULL;
    }

    for(int i = 0; i < this->rows_no; i++) {
        for(int j = 0; j < this->cols_no; j++) {
            result->celulas[i][j] = this->celulas[i][j] - m->celulas[i][j];
        }
    }

    return result;
}

Matriz* Matriz::mul(Matriz *m) {
    Matriz *result = new Matriz(this->rows_no, m->cols_no);

    if(this->cols_no != m->rows_no) {
        std::cout << "Incorrect dimensions for operator \'*\' - have MATRIX [" << this->rows_no << "][" << this->cols_no << "] and MATRIX [" << m->Matriz::getRows()<< "][" << m->Matriz::getCols()<< "]" << std::endl;
        return NULL;
    }

    for(int i = 0; i < this->rows_no; i++) {
        for(int j = 0; j < m->cols_no; j++) {
            result->celulas[i][j] = 0;
            for(int k = 0; k < this->cols_no; k++) {
                result->celulas[i][j] += this->celulas[i][k] * m->celulas[k][j];
            }
        }
    }

    return result;
}

Matriz* Matriz::mul(float value) {
    Matriz *result = new Matriz(this->rows_no, this->cols_no);

    for(int i = 0; i < this->rows_no; i++) {
        for(int j = 0; j < this->cols_no; j++) {
            result->celulas[i][j] = this->celulas[i][j] * value;
        }
    }

    return result;

}

void Matriz:: printarMatrizFormatada(int precisao) {
    int printFormatado[this->cols_no], soma = 0;
    for(int i = 0; i < this->cols_no; i++) {
        int tamanho = 0;

        for (int j = 0; j < this->rows_no; j++) {
            int len = std::to_string((int)this->celulas[j][i]).length();
            if (precisao > 0) {
                len += precisao + 1;
            }
            if (len > tamanho) {
                tamanho = len;
            }
        }

        printFormatado[i] = tamanho;
        soma += tamanho + 1;
    }

    std::cout << "+-" << std::string(soma - 1, ' ') << "-+" << std::endl;

    for (int i = 0; i < this->rows_no; i++) {
        std::cout << "| ";
        for (int j = 0; j < this->cols_no; j++) {
            std::cout << std::fixed << std::setprecision(precisao) << std::setw(printFormatado[j]) << this->celulas[i][j];
            if(j < this->cols_no - 1) {
                std::cout << " ";
            }
        }
        std::cout << " |" << std::endl;
    }

    std::cout << "+-" << std::string(soma - 1, ' ') << "-+" << std::endl;
}

int Matriz::getRows() {
    return this->rows_no;
}

int Matriz::getCols() {
    return this->cols_no;
}

float Matriz::determinante() {
    Matriz *l = inicializarMatrizL();
    Matriz *u = copiarMatrizParaU();

    int swaps = realizarDecomposicaoLU(l, u);

    float det = calcularDeterminanteU(u) * (swaps % 2 == 1 ? -1 : 1);

    delete l;
    delete u;

    return det;
}

Matriz* Matriz::inicializarMatrizL() {
    Matriz *l = new Matriz(this->rows_no, this->cols_no);
    for (int i = 0; i < this->rows_no; i++) {
        for (int j = 0; j < this->cols_no; j++) {
            l->celulas[i][j] = 0;
        }
        l->celulas[i][i] = 1;
    }
    return l;
}

Matriz* Matriz::copiarMatrizParaU() {
    Matriz *u = new Matriz(this->rows_no, this->cols_no);
    for (int i = 0; i < this->rows_no; i++) {
        for (int j = 0; j < this->cols_no; j++) {
            u->celulas[i][j] = this->celulas[i][j];
        }
    }
    return u;
}

int Matriz::realizarDecomposicaoLU(Matriz *l, Matriz *u) {
    int swaps = 0;
    for (int i = 0; i < this->rows_no; i++) {
        for (int j = i + 1; j < this->rows_no; j++) {
            if (u->celulas[i][i] == 0) {
                swaps += trocarLinhasSeNecessario(u, i);
            }
            if (u->celulas[i][i] == 0) {
                return 0;  // Determinante é 0
            }
            float m = u->celulas[j][i] / u->celulas[i][i];
            l->celulas[j][i] = m;
            for (int k = i; k < this->cols_no; k++) {
                u->celulas[j][k] -= m * u->celulas[i][k];
            }
        }
    }
    return swaps;
}

int Matriz::trocarLinhasSeNecessario(Matriz *u, int linhaAtual) {
    for (int k = linhaAtual + 1; k < this->rows_no; k++) {
        if (u->celulas[k][linhaAtual] != 0) {
            for (int l = 0; l < this->cols_no; l++) {
                std::swap(u->celulas[linhaAtual][l], u->celulas[k][l]);
            }
            return 1;
        }
    }
    return 0;
}

float Matriz::calcularDeterminanteU(Matriz *u) {
    float det = 1;
    for (int i = 0; i < this->rows_no; i++) {
        det *= u->celulas[i][i];
    }
    return det;
}


void Matriz::sistemaLinear(int precisao) {
    Matriz *sistema = criarMatrizAumentada();
    realizarEliminacaoGaussiana(sistema);
    
    if (verificarDeterminanteESolucao(sistema)) {
        Matriz *solucao = resolverMatrizTriangularSuperior(sistema);
        imprimirSolucao(solucao);
        delete solucao;
    }

    delete sistema;
}

Matriz* Matriz::criarMatrizAumentada() {
    Matriz *sistema = new Matriz(this->rows_no, this->cols_no);
    for (int i = 0; i < this->rows_no; i++) {
        for (int j = 0; j < this->cols_no; j++) {
            sistema->celulas[i][j] = this->celulas[i][j];
        }
    }
    return sistema;
}

void Matriz::realizarEliminacaoGaussiana(Matriz *sistema) {
    for (int i = 0; i < sistema->rows_no; i++) {
        int linhaPivo = encontrarLinhaPivo(sistema, i);
        if (linhaPivo == -1) break;

        if (linhaPivo != i) {
            trocarLinhas(sistema, i, linhaPivo);
        }

        eliminarColuna(sistema, i);
    }
}

int Matriz::encontrarLinhaPivo(Matriz *sistema, int coluna) {
    for (int j = coluna; j < sistema->rows_no; j++) {
        if (sistema->celulas[j][coluna] != 0) {
            return j;
        }
    }
    return -1;
}

void Matriz::trocarLinhas(Matriz *sistema, int linha1, int linha2) {
    for (int j = 0; j < sistema->cols_no; j++) {
        std::swap(sistema->celulas[linha1][j], sistema->celulas[linha2][j]);
    }
}

void Matriz::eliminarColuna(Matriz *sistema, int coluna) {
    for (int j = coluna + 1; j < sistema->rows_no; j++) {
        float escalar = sistema->celulas[j][coluna] / sistema->celulas[coluna][coluna];
        for (int k = coluna; k < sistema->cols_no; k++) {
            sistema->celulas[j][k] -= escalar * sistema->celulas[coluna][k];
        }
    }
}

bool Matriz::verificarDeterminanteESolucao(Matriz *sistema) {
    Matriz *temp = criarMatrizAumentada();
    float determinante = temp->determinante();
    delete temp;

    if (determinante == 0) {
        if (sistema->celulas[sistema->rows_no - 1][sistema->cols_no - 1] != 0) {
            std::cout << "SI - The Linear System has no solution" << std::endl;
        } else {
            std::cout << "SPI - The Linear System has infinitely many solutions" << std::endl;
        }
        return false;
    }
    return true;
}

Matriz* Matriz::resolverMatrizTriangularSuperior(Matriz *sistema) {
    Matriz *solucao = new Matriz(sistema->rows_no, 1);
    for (int i = sistema->rows_no - 1; i >= 0; i--) {
        float soma = 0;
        for (int j = i + 1; j < sistema->cols_no - 1; j++) {
            soma += sistema->celulas[i][j] * solucao->celulas[j][0];
        }
        solucao->celulas[i][0] = (sistema->celulas[i][sistema->cols_no - 1] - soma) / sistema->celulas[i][i];
    }
    return solucao;
}

void Matriz::imprimirSolucao(Matriz *solucao) {
    std::cout << "Matrix x:" << std::endl << std::endl;
    for (int i = 0; i < solucao->rows_no; i++) {
        std::cout << solucao->celulas[i][0] << std::endl;
    }
}