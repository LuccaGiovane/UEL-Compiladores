/* Não usar a biblioteca do Flex */
%option noyywrap

%{
    #include <stdio.h>

    /*
    A macro PRINTA_ACTION tem as seguintes funcionalidades:
        - Imprime a ação fornecida como parâmetro seguida do valor de yytext entre parênteses e uma nova linha.
    
    Parâmetro:
        - action: string da ação que você quer imprimir
    */
    #define PRINTA_ACTION(action) \
        do { \
            printf(action "(%s)\n", yytext); \
        } while (0)

    /*
    A macro PRINTA_ERRO tem as seguintes funcionalidades:
        - Imprime "ERRO" seguido de uma nova linha.
    */
    #define PRINTA_ERRO() \
        do { \
            printf("ERRO\n"); \
        } while (0)
%}

%%

"aba"+             { PRINTA_ACTION("ACTION1"); }
"a"[b]*"a"         { PRINTA_ACTION("ACTION2"); }
"a"|"b"            { PRINTA_ACTION("ACTION3"); }
[\n]               { /* Não faz nada */ }
.                  { PRINTA_ERRO(); }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
