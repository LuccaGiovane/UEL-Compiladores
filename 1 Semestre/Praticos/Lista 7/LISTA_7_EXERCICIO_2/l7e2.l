/* Não usar a biblioteca do Flex */
%option noyywrap

%{
    #include <stdio.h>
    #include <string.h>

    /*
    A macro PRINTA_TOKEN_E_NOVA_LINHA tem as seguintes funcionalidades:
        - Imprime o token fornecido como parâmetro seguido de uma nova linha.
    
    Parâmetro:
        - token: string do token que você quer imprimir
    */
    #define PRINTA_TOKEN_E_NOVA_LINHA(token) \
        do { \
            printf(token "\n"); \
        } while (0)

    /*
    A macro PRINTA_YYTEXT_COM_SUFIXO tem as seguintes funcionalidades:
        - Imprime o valor de yytext seguido de um sufixo e uma nova linha.
    
    Parâmetro:
        - sufixo: string que você quer imprimir após o valor de yytext
    */
    #define PRINTA_YYTEXT_COM_SUFIXO(sufixo) \
        do { \
            printf("%s " sufixo "\n", yytext); \
        } while (0)

    /*
    A macro PRINTA_COMMENT tem as seguintes funcionalidades:
        - Remove o último caractere de yytext (assumido como uma nova linha).
        - Imprime o valor de yytext seguido da palavra "comment" e uma nova linha.
    */
    #define PRINTA_COMMENT() \
        do { \
            int len = strlen(yytext); \
            yytext[len-1] = '\0'; \
            printf("%s comment\n", yytext); \
        } while (0)

    /*
    A macro PRINTA_ERRO tem as seguintes funcionalidades:
        - Imprime o valor de yytext seguido da palavra "error" e uma nova linha.
    */
    #define PRINTA_ERRO() \
        do { \
            printf("%s error\n", yytext); \
        } while (0)

%}

%%

"if"                            { PRINTA_TOKEN_E_NOVA_LINHA("IF"); }
[a-z][a-z0-9]*                  { PRINTA_YYTEXT_COM_SUFIXO("ID"); }
[0-9]+                          { PRINTA_YYTEXT_COM_SUFIXO("NUM"); }
("."[0-9]+)|([0-9]+"."[0-9]*)   { PRINTA_YYTEXT_COM_SUFIXO("REAL"); }
"--"[a-z]*[\n]                  { PRINTA_COMMENT(); }
" "+                            { PRINTA_TOKEN_E_NOVA_LINHA("white space"); }
[\n]                            { /* Não faz nada */ }
.                               { PRINTA_ERRO(); }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
