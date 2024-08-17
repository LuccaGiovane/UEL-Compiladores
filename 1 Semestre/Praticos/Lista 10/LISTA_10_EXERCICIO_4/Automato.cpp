#include "Automato.h"
#include "string_utils.h"


// Definição do Autômato
const std::string alfabeto [7] {"a-z", "0-9", "+", "*", "(", ")", "$"};

const std::string estados [7] {"1", "2", "3", "4", "5", "6", "7"};

const std::map<std::string, std::string> estados_finais {
	{"2", "ID"},
	{"3", "PLUS"},
	{"4", "TIMES"},
	{"5", "LPAREN"},
	{"6", "RPAREN"},
	{"7", "END"},
};

const std::string transicoes [7][7] {
//           a-z       0-9        +         *         (         )         $     
/*  1  */{   "2",      "0",      "3",      "4",      "5",      "6",      "7"    },
/*  2  */{   "2",      "2",      "0",      "0",      "0",      "0",      "0"    },
/*  3  */{   "0",      "0",      "0",      "0",      "0",      "0",      "0"    },
/*  4  */{   "0",      "0",      "0",      "0",      "0",      "0",      "0"    },
/*  5  */{   "0",      "0",      "0",      "0",      "0",      "0",      "0"    },
/*  6  */{   "0",      "0",      "0",      "0",      "0",      "0",      "0"    },
/*  7  */{   "0",      "0",      "0",      "0",      "0",      "0",      "0"    },
};


const int tam_alfabeto = sizeof(alfabeto) / sizeof(alfabeto[0]);
const int tam_estados = sizeof(estados) / sizeof(estados[0]);


int Automato::get_index_estado(std::string estado) {
    for(int i {0}; i < tam_estados; i++) {
        if(estados[i] == estado) return i;
    }

    return -1;
}


int Automato::get_index_palavra(char palavra) {
    for(int i {0}; i < tam_alfabeto; i++) {
        // Verificar se está dentro de um intervalo
        if(alfabeto[i].size() > 1 && contains(alfabeto[i], "-") != -1) {
            if(is_in_interval(palavra, alfabeto[i])) return i; 
        }
        else if(palavra == alfabeto[i][0]) {
            return i;
        }
    }

    return -1;
}


bool Automato::is_final(int index_estado) {
    std::map<std::string, std::string>::const_iterator it = estados_finais.find(estados[index_estado]);

    return it != estados_finais.end();
}


std::string Automato::get_classificacao_token(int index_estado) {
    if(index_estado == -1) return "";

    std::map<std::string, std::string>::const_iterator it = estados_finais.find(estados[index_estado]);

    return it->second;
}


std::string Automato::get_transicao(int index_estado, int index_palavra) {
    return transicoes[index_estado][index_palavra];
}
