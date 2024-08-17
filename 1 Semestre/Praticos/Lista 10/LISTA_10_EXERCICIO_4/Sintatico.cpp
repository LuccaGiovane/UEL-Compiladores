#include <map>

#include "Sintatico.h"
#include "SintaticoException.h"

const int ID = 1, PLUS = 2, TIMES = 3, LPAREN = 4, RPAREN = 5, END = 6;
const std::map<int, std::string> tokens {
	{1, "id"},
	{2, "+"},
	{3, "*"},
	{4, "("},
	{5, ")"},
	{6, "$"},
};

struct {
    int token_recebido {};
    std::string tokens_esperados {};
} ERROR_CONTROLER;



Sintatico::Sintatico(Lexico lex) {
    this->lex = lex;
    this->token = lex.gerarToken();
    ERROR_CONTROLER.token_recebido = token;
}


void Sintatico::advance() {
    token = lex.gerarToken();
    ERROR_CONTROLER.token_recebido = token;
}


std::string getTokenStringValue(int tk) {
    std::map<int, std::string>::const_iterator it = tokens.find(tk);

    return it->second;
}


void Sintatico::eat(int t) {
    if(token == t) advance();
    else {
        ERROR_CONTROLER.tokens_esperados = getTokenStringValue(t);
        error();
    }
}


void Sintatico::setInput(std::string input) {
    lex.setInput(input);
    advance();
}


void Sintatico::error() {
    throw SintaticoException(getTokenStringValue(ERROR_CONTROLER.token_recebido), ERROR_CONTROLER.tokens_esperados);
}


void Sintatico::S() {
    ERROR_CONTROLER.tokens_esperados = "id, (";

    switch (token) {
        case ID:
        case LPAREN:
            E(); eat(END);
            break;
        default:
            error();
            break;
    }
}


void Sintatico::E() {
    ERROR_CONTROLER.tokens_esperados = "id, (";

    switch (token) {
        case ID:
        case LPAREN:
            T(); El();
            break;
        default:
            error();
            break;
    }
}


void Sintatico::El() {
    ERROR_CONTROLER.tokens_esperados = "+, ), $";

    switch (token) {
        case PLUS:
            eat(PLUS); T(); El();
            break;
        case RPAREN:
        case END:
            break;
        default:
            error();
            break;
    }
}


void Sintatico::T() {
    ERROR_CONTROLER.tokens_esperados = "id, (";

    switch (token) {
        case ID:
        case LPAREN:
            F(); Tl();
            break;
        default:
            error();
            break;
    }
}


void Sintatico::Tl() {
    ERROR_CONTROLER.tokens_esperados = "+, *, ), $";

    switch (token) {
        case PLUS:
        case RPAREN:
        case END:
            break;
        case TIMES:
            eat(TIMES); F(); Tl();
            break;
        default:
            error();
            break;
    }
}


void Sintatico::F() {
    ERROR_CONTROLER.tokens_esperados = "id, (";

    switch (token) {
        case ID:
            eat(ID);
            break;
        case LPAREN:
            eat(LPAREN); E(); eat(RPAREN);
            break;
        default:
            error();
            break;
    }
}
