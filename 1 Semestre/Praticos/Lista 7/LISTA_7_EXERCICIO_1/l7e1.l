%option noyywrap

%{
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
    A macro PRINTA_YYTEXT_E_NOVA_LINHA tem as seguintes funcionalidades:
        - Imprime o valor do yytext seguido de uma nova linha.
    */
    #define PRINTA_YYTEXT_E_NOVA_LINHA() \
        do { \
            printf("%s\n", yytext); \
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

"+"                  { PRINTA_TOKEN_E_NOVA_LINHA("+"); }
"-"                  { PRINTA_TOKEN_E_NOVA_LINHA("-"); }
[a-z][a-z0-9]*       { PRINTA_YYTEXT_E_NOVA_LINHA(); }
[0-9]+               { PRINTA_YYTEXT_E_NOVA_LINHA(); }
[0-9]+e[+-]?[0-9]+   { PRINTA_YYTEXT_E_NOVA_LINHA(); }
[\n]                 { /* Não faz nada */ }
.                    { PRINTA_ERRO(); }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
