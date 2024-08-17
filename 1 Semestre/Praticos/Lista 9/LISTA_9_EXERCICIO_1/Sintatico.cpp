#include <map>

#include "Sintatico.h"
#include "SintaticoException.h"

const int IF = 1, THEN = 2, ELSE = 3, BEGIN = 4, END = 5, PRINT = 6, NUM = 7, EQ = 8, SEMI = 9;

struct {
    int token_recebido {};
    std::string tokens_esperados {};
} ERROR_CONTROLER;

const std::map<int, std::string> tokens {
	{1, "if"},
	{2, "then"},
	{3, "else"},
	{4, "begin"},
	{5, "end"},
	{6, "print"},
	{7, "num"},
	{8, "="},
	{9, ";"},
};


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
    if(ERROR_CONTROLER.token_recebido == 0) throw SintaticoException();
    else throw SintaticoException(getTokenStringValue(ERROR_CONTROLER.token_recebido), ERROR_CONTROLER.tokens_esperados);
}


void Sintatico::S() {
    ERROR_CONTROLER.tokens_esperados = "if, begin, print";

    switch (token) {
        case IF:
            // S -> if E then S else S
            eat(IF); E(); eat(THEN); S(); eat(ELSE); S();
            break;
        case BEGIN:
            // S -> begin S L
            eat(BEGIN); S(); L();
            break;
        case PRINT:
            // S -> print E
            eat(PRINT); E();
            break;
        default:
            error();
            break;
    }
}


void Sintatico::L() {
    ERROR_CONTROLER.tokens_esperados = "end, ;";

    switch (token)
    {
        case END:
            // L -> end
            eat(END);
            break;
        case SEMI:
            // L -> ; S L
            eat(SEMI); S(); L();
            break;
        default:
            error();
            break;
    }
}


void Sintatico::E() {
    ERROR_CONTROLER.tokens_esperados = "num";

    switch (token)
    {
        case NUM:
            // E -> num = num
            eat(NUM); eat(EQ); eat(NUM);
            break;
        default:
            error();
            break;
    }
}
