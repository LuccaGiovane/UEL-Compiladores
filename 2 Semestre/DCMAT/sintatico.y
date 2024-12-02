%code requires
{
    #include "ast.h"
    #include <vector>
}

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <iomanip>
    #include <string>
    #include <map>
    #include <vector>
    #include "ast.h"
    #include "matematica.h"
    #include "matriz.h"

    using namespace std;

    float H_VIEW_LO = -6.500000;
    float H_VIEW_HI = 6.500000;
    float V_VIEW_LO = -3.500000;
    float V_VIEW_HI = 3.500000;
    int FLOAT_PRECISION = 6;
    int STEPS = 1000;
    bool PLOT_AXIS = true;
    bool PLOT_ERASE = true;
    bool CONNECT = false;
    Matriz *matrizOperavel;
    vector<ArvoreSintatica*> listaPlots;
    map<string, float> dicionarioVariaveis;
    map<string, Matriz*> dicionarioMatrizes;

    int yylex();
    extern char* yytext;
    int yyerror(const char* s);
    extern int lexicalError;
    void scan_string(char * str);
    void delete_buffer();
%}

%token IDENTIFIER  
%token INTEGER_NUMBER  
%token FLOAT_NUMBER  
%token EOL  
%token LEXERROR  
%token LINEAR_SYSTEM  
%token RESET  
%token SYMBOLS  
%token DETERMINANT  
%token MATRIX  
%token RPN  
%token TAN  
%token CONST_E  
%token OFF  
%token SEN  
%token V_VIEW  
%token ERASE  
%token ON  
%token SET  
%token CONST_X  
%token ADD  
%token SUB  
%token MUL  
%token DIV  
%token POT  
%token MOD  
%token LPAREN  
%token RPAREN  
%token COLON  
%token EQUAL  
%token ASSIGN  
%token LBRACKET  
%token RBRACKET  
%token SEMICOLON  
%token COMMA  
%token ABOUT  
%token FLOAT  
%token CONST_PI  
%token SETTINGS  
%token ABS  
%token H_VIEW  
%token PLOT  
%token SHOW  
%token AXIS  
%token INTEGRAL_STEPS  
%token PRECISION  
%token SOLVE  
%token CONNECT_DOTS  
%token INTEGRATE  
%token QUIT  
%token SUM  
%token COS  

%union
{
    float retFloat;
    int retInteiro;
    char *retString;
    ArvoreSintatica* retAst;
    std::vector<float> *listaColunas;
    std::vector<std::vector<float>> *listaLinhas;
}

%type <retFloat> decimal 
%type <retFloat> FLOAT_NUMBER
%type <retInteiro> inteiro 
%type <retInteiro> INTEGER_NUMBER
%type <retString> IDENTIFIER
%type <retAst> exp_add 
%type <retAst> exp_mult 
%type <retAst> exp_unary 
%type <retAst> exp_prim 
%type <listaColunas> colunasMatriz
%type <listaLinhas> linhasMatriz 
%type <listaLinhas> lerMatriz

%start programaStart

%%

fimLinha: SEMICOLON EOL

programaStart: printConsts                       { return 0; }
    | sets fimLinha                  { return 0; }
    | atribuir fimLinha              { return 0; }
    | matrizOperavel fimLinha        { return 0; }
    | plot                  { return 0; }
    | printId              { return 0; }
    | avaliarExp                    { return 0; }
    | integral                     { return 0; }
    | somatorio                     { return 0; }
    | determinante               { return 0; }
    | sistemaLinear             { return 0; }
    | rpn                      { return 0; }
    | about                         { return 0; }
    | printMatriz                    { return 0; }
    | printSimbolos                   { return 0; }
    | EOL                           { return 0; }
    | QUIT                          { return 1; }
;

about: 
ABOUT {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "|                                              |" << endl;
    cout << "|                 201900560202                 |" << endl;
    cout << "|              Lucca Giovane Gomes             |" << endl;
    cout << "|                                              |" << endl;
    cout << "+----------------------------------------------+" << endl;
}
;

printId: 
IDENTIFIER fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    printId($1, dicionarioVariaveis, dicionarioMatrizes, FLOAT_PRECISION);
}

printMatriz: 
SHOW MATRIX fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    printMatriz(matrizOperavel, FLOAT_PRECISION);
}

printSimbolos: 
SHOW SYMBOLS fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    printSimbolos(dicionarioVariaveis, dicionarioMatrizes);
}

avaliarExp: 
exp_add EOL { 
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    map<string, string> variaveisNaoEncontradas;
    structResultado *v = $1->ArvoreSintatica::evaluate(&dicionarioVariaveis, &dicionarioMatrizes, &variaveisNaoEncontradas);
    if(v->isFloat == true && v->isDefined == true){
        cout << v->floatValue << endl;
    }
    else if(v->isDefined == true){
        v->matrixValue->Matriz::printarMatrizFormatada(FLOAT_PRECISION);
    } else {
        printVariaveisNaoEncontradas(&variaveisNaoEncontradas);
    }
}
;

atribuir:
IDENTIFIER ASSIGN exp_add {  
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    map<string, string> variaveisNaoEncontradas;
    structResultado *v = $3->ArvoreSintatica::evaluate(&dicionarioVariaveis, &dicionarioMatrizes, &variaveisNaoEncontradas);
    if(v->isFloat == true && v->isDefined == true){
        if(dicionarioMatrizes.find($1) != dicionarioMatrizes.end()){
            dicionarioMatrizes.erase($1);
        }
        dicionarioVariaveis[$1] = v->floatValue;
        cout << v->floatValue << endl;
    }
    else if(v->isDefined == true){
        if(dicionarioVariaveis.find($1) != dicionarioVariaveis.end()){
            dicionarioVariaveis.erase($1);
        }
        dicionarioMatrizes[$1] = v->matrixValue;
        v->matrixValue->Matriz::printarMatrizFormatada(FLOAT_PRECISION);
    } else {
        printVariaveisNaoEncontradas(&variaveisNaoEncontradas);
    }
}
    | 
IDENTIFIER ASSIGN lerMatriz { 
    vector<vector<float>> *v = $3;
    Matriz *m = new Matriz(v);
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    if(m->Matriz::getRows()> 10 || m->Matriz::getCols()> 10 || m->Matriz::getRows()< 1 || m->Matriz::getCols()< 1){
        cout << "ERROR: Matriz limits out of boundaries." << endl;
    }
    else {
        if(dicionarioVariaveis.find($1) != dicionarioVariaveis.end()){
            dicionarioVariaveis.erase($1);
        }
        dicionarioMatrizes[$1] = m;
        m->Matriz::printarMatrizFormatada(FLOAT_PRECISION);
    }
}
;

matrizOperavel: 
MATRIX EQUAL lerMatriz { 
    vector<vector<float>> *v = $3;
    Matriz *m = new Matriz(v);
    if(m->Matriz::getRows()> 10 || m->Matriz::getCols()> 10 || m->Matriz::getRows()< 1 || m->Matriz::getCols()< 1){
        cout << endl << "ERROR: Matriz limits out of boundaries." << endl;
    }
    else {
        matrizOperavel = m;
    }
}
;

sets: 
SET H_VIEW decimal COLON decimal { 
    if ($3 >= $5) {
        cout << endl << "ERROR: h_view_lo must be smaller than h_view_hi" << endl;
    }
    else {
        H_VIEW_LO = $3;
        H_VIEW_HI = $5;
    }
}
    | 
SET V_VIEW decimal COLON decimal { 
    if ($3 >= $5) {
        cout << endl << "ERROR: v_view_lo must be smaller than v_view_hi" << endl;
    }
    else {
        V_VIEW_LO = $3;
        V_VIEW_HI = $5;
    }
}
    | 
SET FLOAT PRECISION inteiro { 
    if($4 < 0 || $4 > 8) {
        cout << endl << "ERROR: float precision must be from 0 to 8" << endl;
    }
    else {
        FLOAT_PRECISION = $4;
    }
}
    | 
SET INTEGRAL_STEPS inteiro { 
    if($3 <= 0) {
    cout << endl << "ERROR: integral_steps must be a positive non-zero integer" << endl;
    }
    else {
        STEPS = $3;
    }
}
    | SET AXIS ON           { PLOT_AXIS = true; }
    | SET AXIS OFF          { PLOT_AXIS = false; }
    | SET ERASE PLOT ON     { PLOT_ERASE = true; }
    | SET ERASE PLOT OFF    { PLOT_ERASE = false; }
    | SET CONNECT_DOTS ON   { CONNECT = true; }
    | SET CONNECT_DOTS OFF  { CONNECT = false; }
;

printConsts: 
SHOW SETTINGS fimLinha {
    cout << fixed << setprecision(6) << endl;
    cout << "h_view_lo: " << H_VIEW_LO << endl;
    cout << "h_view_hi: " << H_VIEW_HI << endl;
    cout << "v_view_lo: " << V_VIEW_LO << endl;
    cout << "v_view_hi: " << V_VIEW_HI << endl;
    cout << "float_precision: " << FLOAT_PRECISION << endl;
    cout << "integral_steps: " << STEPS << endl << endl;

    if(PLOT_AXIS){
        cout << "Draw Axis: ON" << endl;
    } else {
        cout << "Draw Axis: OFF" << endl;
    }

    if(PLOT_ERASE){
        cout << "Erase Plot: ON" << endl;
    } else {
        cout << "Erase Plot: OFF" << endl;
    }

    if(CONNECT){
        cout << "Connect Dots: ON" << endl;
    } else {
        cout << "Connect Dots: OFF" << endl;
    }
}
    | 
RESET SETTINGS fimLinha { 
    H_VIEW_LO = -6.500000;
    H_VIEW_HI = 6.500000;
    V_VIEW_LO = -3.500000;
    V_VIEW_HI = 3.500000;
    FLOAT_PRECISION = 6;
    STEPS = 1000;
    PLOT_AXIS = true;
    PLOT_ERASE = true;
    CONNECT = false;
}
;

lerMatriz: LBRACKET linhasMatriz RBRACKET { vector<vector<float>> *v = $2; $$ = v; }
;

linhasMatriz: 
LBRACKET colunasMatriz RBRACKET { 
    vector<vector<float>> *v = new vector<vector<float>>;
    vector<float> *v2 = $2;
    v->insert(v->begin(), *v2);
    $$ = v; 
}
    | 
LBRACKET colunasMatriz RBRACKET COMMA linhasMatriz { 
    vector<vector<float>> *v = $5;
    vector<float> *v2 = $2;
    v->insert(v->begin(), *v2);
    $$ = v; 
}
;

colunasMatriz: 
decimal { 
    vector<float> *v = new vector<float>;
    v->insert(v->begin(), $1);
    $$ = v; 
}
    | 
decimal COMMA colunasMatriz { 
    vector<float> *v = $3;
    v->insert(v->begin(), $1);
    $$ = v; 
}
;

exp_add: exp_mult                           { $$ = $1; }
    | exp_add ADD exp_mult                  { ArvoreSintatica *e = new ArvoreSintatica($1, "add", $3); $$ = e; }
    | exp_add SUB exp_mult                  { ArvoreSintatica *e = new ArvoreSintatica($1, "sub", $3); $$ = e; }
;

exp_mult: exp_unary                         { $$ = $1; }
    | exp_mult MUL exp_unary                { ArvoreSintatica *e = new ArvoreSintatica($1, "mul", $3); $$ = e; }
    | exp_mult DIV exp_unary                { ArvoreSintatica *e = new ArvoreSintatica($1, "div", $3); $$ = e; }
    | exp_mult MOD exp_unary                { ArvoreSintatica *e = new ArvoreSintatica($1, "mod", $3); $$ = e; }
;

exp_unary: exp_prim                         { $$ = $1; }
    | exp_unary POT exp_prim                { ArvoreSintatica *e = new ArvoreSintatica($1, "pot", $3); $$ = e; }
    | ADD exp_prim                          { ArvoreSintatica *e = new ArvoreSintatica("pos", $2); $$ = e; }
    | SUB exp_prim                          { ArvoreSintatica *e = new ArvoreSintatica("neg", $2); $$ = e; }
;

exp_prim: FLOAT_NUMBER                      { ArvoreSintatica *e = new ArvoreSintatica($1); $$ = e; }
    | INTEGER_NUMBER                        { ArvoreSintatica *e = new ArvoreSintatica((float) $1); $$ = e; }
    | IDENTIFIER                            { ArvoreSintatica *e = new ArvoreSintatica($1); $$ = e; }
    | LPAREN exp_add RPAREN                 { $$ = $2; }
    | CONST_X                               { ArvoreSintatica *e = new ArvoreSintatica("x"); $$ = e; }
    | CONST_E                               { ArvoreSintatica *e = new ArvoreSintatica(EULER_CONST); $$ = e; }
    | CONST_PI                              { ArvoreSintatica *e = new ArvoreSintatica(PI_CONST); $$ = e; }
    | ABS LPAREN exp_add RPAREN             { ArvoreSintatica *e = new ArvoreSintatica("abs", $3); $$ = e; }
    | COS LPAREN exp_add RPAREN             { ArvoreSintatica *e = new ArvoreSintatica("cos", $3); $$ = e; }
    | SEN LPAREN exp_add RPAREN             { ArvoreSintatica *e = new ArvoreSintatica("sen", $3); $$ = e; }
    | TAN LPAREN exp_add RPAREN             { ArvoreSintatica *e = new ArvoreSintatica("tan", $3); $$ = e; }
;

integral: 
INTEGRATE LPAREN decimal COLON decimal COMMA exp_add RPAREN fimLinha {
    return integral($3, $5, STEPS, FLOAT_PRECISION, $7, dicionarioVariaveis, dicionarioMatrizes);
}

somatorio: 
SUM LPAREN IDENTIFIER COMMA INTEGER_NUMBER COLON INTEGER_NUMBER COMMA exp_add RPAREN fimLinha {
    somatorio($3, $5, $7, FLOAT_PRECISION, $9, dicionarioVariaveis, dicionarioMatrizes);
}

determinante: 
SOLVE DETERMINANT fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    if(matrizOperavel == NULL){
        cout << "No Matrix defined!" << endl;
        return 0;
    }
    else if(matrizOperavel->Matriz::getRows() != matrizOperavel->Matriz::getCols()){
        cout << "Matrix format incorrect!" << endl;
        return 0;
    }

    float det = matrizOperavel->Matriz::determinante();

    cout << det << endl;
}

sistemaLinear: 
SOLVE LINEAR_SYSTEM fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    if(matrizOperavel == NULL){
        cout << "No Matrix defined!" << endl;
        return 0;
    }
    else if(matrizOperavel->Matriz::getRows() != matrizOperavel->Matriz::getCols() - 1){
        cout << "Matrix format incorrect!" << endl;
        return 0;
    }

    matrizOperavel->Matriz::sistemaLinear(FLOAT_PRECISION);
}

rpn: 
RPN exp_add fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    string rpn = $2->ArvoreSintatica::rpn();
    cout << "Expression in RPN format:" << endl << endl << rpn << endl;
}

plot: 
PLOT LPAREN exp_add RPAREN fimLinha {
    if (PLOT_ERASE) {
        listaPlots.clear();
        listaPlots.push_back($3);
    } else {
        listaPlots.push_back($3);
    }

    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    map<string, string> variaveisNaoEncontradas;
    plot(&listaPlots, &dicionarioVariaveis, &dicionarioMatrizes, &variaveisNaoEncontradas, PLOT_AXIS, H_VIEW_LO, V_VIEW_LO, H_VIEW_HI, V_VIEW_HI);
    printVariaveisNaoEncontradas(&variaveisNaoEncontradas);
}
    | 
PLOT fimLinha {
    cout << fixed << setprecision(FLOAT_PRECISION) << endl;
    if(listaPlots.size() == 0){
        cout << "No Function defined!" << endl;
    }
    else {
        map<string, string> variaveisNaoEncontradas;
        plot(&listaPlots, &dicionarioVariaveis, &dicionarioMatrizes, &variaveisNaoEncontradas, PLOT_AXIS, H_VIEW_LO, V_VIEW_LO, H_VIEW_HI, V_VIEW_HI);
        printVariaveisNaoEncontradas(&variaveisNaoEncontradas);
    }
}
;

decimal: FLOAT_NUMBER           { $$ = $1; }
    | SUB FLOAT_NUMBER              { $$ = -$2; }
    | ADD FLOAT_NUMBER              { $$ = $2; }
    | inteiro                 { $$ = (float)$1; }
;

inteiro: INTEGER_NUMBER       { $$ = $1; }
    | SUB INTEGER_NUMBER            { $$ = -$2; }
    | ADD INTEGER_NUMBER            { $$ = $2; }
;

%%

int yyerror(const char *text){
    if (lexicalError == 1) {
        lexicalError = 0;
        return 1;
    }
    if(yytext[0] == '\0' || yytext[0] == '\n'){
        cout << "\nSYNTAX ERROR: Incomplete Command" << endl;
    }
    else {
        cout << "\nSYNTAX ERROR: [" << yytext << "]" << endl;
    }

    return 1;
}

int main() {
    while (true) {
        cout << ">";

        string input;
        getline(cin, input);

        scan_string(const_cast<char*>(input.c_str()));
        int quit = yyparse();
        delete_buffer();

        if (quit == 1) {
            break;
        }

        cout << endl;
    }

    return 0;
}