#include <map>

#include "Lexico.h"
#include "LexicoException.h"


const int INVALID_STATE {-1};
const int START_STATE {0};
const std::map<std::string, int> tokens {
	{"ID", 1},
	{"PLUS", 2},
	{"TIMES", 3},
	{"LPAREN", 4},
	{"RPAREN", 5},
	{"END", 6},
};



Lexico::Lexico() { 
	this->start_token = 0;
	this->last_final_pos = 0;
}


void Lexico::setInput(std::string input_str) {
	input = input_str;
	start_token = 0;
	last_final_pos = 0;
}


std::string Lexico::getText() {
	return text;
}


int Lexico::gerarToken() {
	int current_state {START_STATE};
	int last_final {INVALID_STATE};

	int palavra_index;

	for(int i {start_token}; i <= input.size(); ) {
		try {
			palavra_index = Automato::get_index_palavra(input[i]);
			if(palavra_index == -1) throw -1;

			current_state = Automato::get_index_estado(Automato::get_transicao(current_state, palavra_index));
			if(current_state == -1) throw 0;

			if(Automato::is_final(current_state)) {
				last_final = current_state;
				last_final_pos = i;
			}

			i++;
		} catch(int erro) {
			int cod_token;
			text = input.substr(start_token, last_final_pos - start_token + 1);
			// Se um estado final não foi atingido
			if(last_final == -1) {
				if(i == start_token) {
					if(input[i] == ' ') {
						cod_token = -1;
					} else if(input[i] == '\n') {
						cod_token = -1;
					} else if(input[i] == 0) { 
						cod_token = 0;
					} else {
						cod_token = -2;
					}
				}
				else {
					cod_token = -2;
				}
			}
			else {
				std::string classificacao_token = Automato::get_classificacao_token(last_final);

				std::map<std::string, int>::const_iterator it = tokens.find(classificacao_token);

    			cod_token = it->second;
			}

			// Resetar parâmetros
			current_state = START_STATE;
			last_final = INVALID_STATE;
			last_final_pos++;
			i = last_final_pos;
			start_token = last_final_pos;

			if(cod_token == -2) error();
			if(cod_token != -1) return cod_token;
		}
	}
	return 0;
}


void Lexico::error() {
	throw LexicoException(text);
}
