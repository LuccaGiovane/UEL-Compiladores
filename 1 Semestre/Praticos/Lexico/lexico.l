%option noyywrap
%{
    #define TAMANHO_MAXIMO 255

    int cont   = -1;
    int linha  = 1;
    int coluna = 1;
%}

%{

    /*
    A macro PRINTA_E_INCREMENTA tem as seguintes funcionalidades:
        - incrementa a global cont
        - se cont != 0 imprime uma nova linha
        - imprime o TOKEN fornecido como parametro
        - incrementa a global coluna
    
    A macro e encapsulada por um do{}while(0) para dar
    maior segurança de uso e para ela funcionar como uma
    unica instruçao

    Parametro:
        - token: string do token que você quer imprimir
    */
    #define PRINTA_E_INCREMENTA(token) \
    do \
    { \
        if ( (++cont) > 0)\
        {\
            printf("\n"); \
        }\
        \
        printf(token);\
        coluna += yyleng; \
    } while (0)


    /*
    A macro PRINTA_E_INCREMENTA_NUMERICO tem as seguintes funcionalidades:
        - incrementa a global cont
        - se cont != 0, imprime uma nova linha
        - imprime o TOKEN fornecido como parâmetro, seguido do valor numérico entre parênteses
        - incrementa a global coluna
    
    A macro é encapsulada por um do{}while(0) para dar
    maior segurança de uso e para ela funcionar como uma
    única instrução

    Parâmetro:
        - token: string do token que você quer imprimir
    */
    #define PRINTA_E_INCREMENTA_NUMERICO(token) \
    do { \
        if ((++cont) != 0)\
        { \
            printf("\n"); \
        } \
        \
        printf(token "(%s)", yytext); \
        coluna += yyleng; \
    } while (0)

    /*
    A macro INCREMENTA_LINHA tem as seguintes funcionalidades:
        - incrementa a global linha
        - reseta a global coluna para 1
    
    A macro é encapsulada por um do{}while(0) para dar
    maior segurança de uso e para ela funcionar como uma
    única instrução
    */
    #define INCREMENTA_LINHA() \
    do \
    { \
        linha++; \
        coluna = 1; \
    } while (0)


    /*
    A macro PRINTA_CARACTERE_ENTRE_ASPAS_SIMPLES tem as seguintes funcionalidades:
        - armazena o comprimento do token em 'tamanho'.
        - define um ponteiro 'texto' para o texto do token, começando logo após a primeira aspa simples.
        - substitui a aspa simples de fechamento por um caractere nulo para terminar a string.
        - incrementa a global 'cont' e, se 'cont' não for zero, imprime uma nova linha.
        - imprime o token "CHARACTER" seguido pelo caractere reconhecido.
        - incrementa a global 'coluna' com o comprimento do token reconhecido.

    A macro é encapsulada por um do{}while(0) para dar
    maior segurança de uso e para ela funcionar como uma
    única instrução.
    */
    #define PRINTA_CARACTERE_ENTRE_ASPAS_SIMPLES() \
    do \
    { \
        int tamanho = yyleng; \
        char *texto = yytext + 1; \
        texto[tamanho - 2] = '\0'; \
        \
        if ((++cont) != 0) \
        { \
            printf("\n"); \
        } \
        \
        printf("CHARACTER(%s)", texto); \
        coluna += yyleng; \
    } while (0)

    /*
    A macro PRINTA_STRING tem as seguintes funcionalidades:
        - Armazena o comprimento do token em 'tamanho'.
        - Define um ponteiro 'str' para o texto do token, começando logo após a primeira aspa dupla.
        - Substitui a última aspa dupla por um caractere nulo para terminar a string.
        - Incrementa a global 'cont' e, se 'cont' não for zero, imprime uma nova linha.
        - Imprime o token "STRING" seguido pela string reconhecida entre parênteses.
        - Incrementa a global 'coluna' com o comprimento do token reconhecido.
    
    A macro é encapsulada por um do{}while(0) para dar
    maior segurança de uso e para ela funcionar como uma
    única instrução.
    */
    #define PRINTA_STRING() \
    do \
    { \
        int tamanho = yyleng; \
        char *texto = yytext + 1; \
        texto[tamanho - 2] = '\0'; \
        \
        if ((++cont) != 0) \
        { \
            printf("\n"); \
        } \
        \
        printf("STRING(%s)", texto); \
        coluna += yyleng; \
    } while (0)

    /*
    A macro PRINTA_ID tem as seguintes funcionalidades:
        - Incrementa a variável global 'cont'
        - Se 'cont' não for zero, imprime uma nova linha
        - Verifica se o comprimento do identificador ('yyleng') é maior que o tamanho máximo permitido ('TAMANHO_MAXIMO')
        - Se o identificador for muito longo, imprime uma mensagem de erro lexical contendo a linha e coluna atuais
        - Se o identificador estiver dentro do tamanho permitido, imprime "IDENTIFIER" seguido do texto do identificador ('yytext')
        - Incrementa a variável global 'coluna' pelo comprimento do texto reconhecido ('yyleng')
    
        A macro é encapsulada por um do{}while(0) para dar maior segurança de uso e para ela funcionar como uma única instrução
    */
    #define PRINTA_ID() \
    do { \
        if ((++cont) != 0) \
            printf("\n"); \
        if (yyleng > TAMANHO_MAXIMO) \
            printf("error:lexical:%d:%d: identifier too long", linha, coluna); \
        else \
            printf("IDENTIFIER(%s)", yytext); \
        coluna += yyleng; \
    } while (0)

    /*
    A macro IMPRIME_ERRO_LEXICAL tem as seguintes funcionalidades:
        - Incrementa a variável global 'cont'
        - Se 'cont' não for zero, imprime uma nova linha
        - Imprime uma mensagem de erro lexical contendo a linha, coluna e o texto correspondente
        - Incrementa a variável global 'coluna' pelo comprimento do texto reconhecido
    
        A macro é encapsulada por um do{}while(0) para dar maior segurança de uso e para ela funcionar como uma única instrução
    */
    #define IMPRIME_ERRO_LEXICAL(){} \
    do \
    { \
        if ((++cont) != 0)\
        {\
            printf("\n"); \
        }\
        \
        printf("error:lexical:%d:%d: %s", linha, coluna, yytext); \
        coluna += yyleng; \
    } while (0)


    /*
    A macro INCREMENTA_COLUNA_ESPACOS tem as seguintes funcionalidades:
        - Incrementa a variável global 'coluna' pelo comprimento do texto reconhecido (espaços em branco)
        - A macro é encapsulada por um do{}while(0) para dar maior segurança de uso e para ela funcionar como uma única instrução
    */
    #define INCREMENTA_COLUNA_ESPACOS() \
    do { \
        coluna += yyleng; \
    } while (0)

%}

%%

void        {PRINTA_E_INCREMENTA("VOID");}
int         {PRINTA_E_INCREMENTA("INT");}
char        {PRINTA_E_INCREMENTA("CHAR");}
return      {PRINTA_E_INCREMENTA("RETURN");}
break       {PRINTA_E_INCREMENTA("BREAK");}
switch      {PRINTA_E_INCREMENTA("SWITCH");}
case        {PRINTA_E_INCREMENTA("CASE");}
default     {PRINTA_E_INCREMENTA("DEFAULT");}
do          {PRINTA_E_INCREMENTA("DO");}
while       {PRINTA_E_INCREMENTA("WHILE");}
for         {PRINTA_E_INCREMENTA("FOR");}
if          {PRINTA_E_INCREMENTA("IF");}
else        {PRINTA_E_INCREMENTA("ELSE");}
typedef     {PRINTA_E_INCREMENTA("TYPEDEF");}
struct      {PRINTA_E_INCREMENTA("STRUCT");}
"+"         {PRINTA_E_INCREMENTA("PLUS");}
"-"         {PRINTA_E_INCREMENTA("MINUS");}
"*"         {PRINTA_E_INCREMENTA("MULTIPLY");}
("//".*\n)  {INCREMENTA_LINHA();}
"/*"        {
    int asterisco = 0;
    int barra = 0;
    int tmp_linha = linha;
    int tmp_coluna = coluna;
    char caractere;

    coluna += 2;

    for(;;) 
    {
        caractere = input();
        coluna++;

        if(caractere == '/') 
        {
            // Verificação se é o fim do bloco de comentarios: '*/'
            if(asterisco != 0)
            {
                break;
            }
            barra = 1;

        } 
        else if(caractere == '*')
        {
            asterisco = 1;
        }
        else if(caractere == '\0')
        {
            if((++cont) != 0)
            {
                printf("\n");
            }

            printf("error:lexical:%d:%d: unterminated comment", tmp_linha, tmp_coluna);
            break;
        }
        else
        {
            if(asterisco && barra) 
            {
                if(++cont) 
                {
                    printf("\n");
                }
                printf("warning:%d:%d: '/*' within block comment", linha, coluna-3);
            }

            if(caractere == '\n') 
            {
                linha++;
                coluna = 1;
            }

            asterisco = 0;
            barra = 0;
        }
    }
}
"/"         {PRINTA_E_INCREMENTA("DIV");}
%           {PRINTA_E_INCREMENTA("REMAINDER");}
"++"        {PRINTA_E_INCREMENTA("INC");}
"--"        {PRINTA_E_INCREMENTA("DEC");}
"&"         {PRINTA_E_INCREMENTA("BITWISE_AND");}
"|"         {PRINTA_E_INCREMENTA("BITWISE_OR");}
"~"         {PRINTA_E_INCREMENTA("BITWISE_NOT");}
"^"         {PRINTA_E_INCREMENTA("BITWISE_XOR");}
"!"         {PRINTA_E_INCREMENTA("NOT");}
"&&"        {PRINTA_E_INCREMENTA("LOGICAL_AND");}
"||"        {PRINTA_E_INCREMENTA("LOGICAL_OR");}
"=="        {PRINTA_E_INCREMENTA("EQUAL");}
"!="        {PRINTA_E_INCREMENTA("NOT_EQUAL");}
"<"         {PRINTA_E_INCREMENTA("LESS_THAN");}
">"         {PRINTA_E_INCREMENTA("GREATER_THAN");}
"<="        {PRINTA_E_INCREMENTA("LESS_EQUAL");}
">="        {PRINTA_E_INCREMENTA("GREATER_EQUAL");}
">>"        {PRINTA_E_INCREMENTA("R_SHIFT");}
"<<"        {PRINTA_E_INCREMENTA("L_SHIFT");}
"="         {PRINTA_E_INCREMENTA("ASSIGN");}
"+="        {PRINTA_E_INCREMENTA("ADD_ASSIGN");}
"-="        {PRINTA_E_INCREMENTA("MINUS_ASSIGN");}
";"         {PRINTA_E_INCREMENTA("SEMICOLON");}
","         {PRINTA_E_INCREMENTA("COMMA");}
":"         {PRINTA_E_INCREMENTA("COLON");}
"("         {PRINTA_E_INCREMENTA("L_PAREN");}
")"         {PRINTA_E_INCREMENTA("R_PAREN");}
"{"         {PRINTA_E_INCREMENTA("L_CURLY_BRACKET");}
"}"         {PRINTA_E_INCREMENTA("R_CURLY_BRACKET");}
"["         {PRINTA_E_INCREMENTA("L_SQUARE_BRACKET");}
"]"         {PRINTA_E_INCREMENTA("R_SQUARE_BRACKET");}
"?"         {PRINTA_E_INCREMENTA("TERNARY_CONDITIONAL");}
"#"         {PRINTA_E_INCREMENTA("NUMBER_SIGN");}
->          {PRINTA_E_INCREMENTA("POINTER");}
printf      {PRINTA_E_INCREMENTA("PRINTF");}
scanf       {PRINTA_E_INCREMENTA("SCANF");}
define      {PRINTA_E_INCREMENTA("DEFINE");}
exit        {PRINTA_E_INCREMENTA("EXIT");}
0[1-7][0-7]*           {PRINTA_E_INCREMENTA_NUMERICO("NUM_OCTAL");}
0[xX][0-9A-Fa-f]+      {PRINTA_E_INCREMENTA_NUMERICO("NUM_HEXA");}
[0-9]+                 {PRINTA_E_INCREMENTA_NUMERICO("NUM_INTEGER");}
\'(\\.|.)\'            {PRINTA_CARACTERE_ENTRE_ASPAS_SIMPLES();}
\"(\\.|[^\"])*\"       {PRINTA_STRING();}
[_a-zA-Z][a-zA-Z0-9_]* {PRINTA_ID();}
[ ]+        {INCREMENTA_COLUNA_ESPACOS();}
\n          {INCREMENTA_LINHA();}
.           {IMPRIME_ERRO_LEXICAL();}// caso ler um caractere obscuro ex: @

%%

int main() {
    yylex();

    return 0;
}