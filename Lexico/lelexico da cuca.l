%option noyywrap
%{
    int cont = -1;
    int linha = 1;
    int coluna = 1;
    int max_size = 255;
%}

%%

void    {if(++cont) printf("\n"); printf("VOID"); coluna += yyleng;}
int     {if(++cont) printf("\n"); printf("INT"); coluna += yyleng;}
char    {if(++cont) printf("\n"); printf("CHAR"); coluna += yyleng;}
return  {if(++cont) printf("\n"); printf("RETURN"); coluna += yyleng;}
break   {if(++cont) printf("\n"); printf("BREAK"); coluna += yyleng;}
switch  {if(++cont) printf("\n"); printf("SWITCH"); coluna += yyleng;}
case    {if(++cont) printf("\n"); printf("CASE"); coluna += yyleng;}
default {if(++cont) printf("\n"); printf("DEFAULT"); coluna += yyleng;}
do      {if(++cont) printf("\n"); printf("DO"); coluna += yyleng;}
while   {if(++cont) printf("\n"); printf("WHILE"); coluna += yyleng;}
for     {if(++cont) printf("\n"); printf("FOR"); coluna += yyleng;}
if      {if(++cont) printf("\n"); printf("IF"); coluna += yyleng;}
else    {if(++cont) printf("\n"); printf("ELSE"); coluna += yyleng;}
typedef {if(++cont) printf("\n"); printf("TYPEDEF"); coluna += yyleng;}
struct  {if(++cont) printf("\n"); printf("STRUCT"); coluna += yyleng;}
"+"     {if(++cont) printf("\n"); printf("PLUS"); coluna += yyleng;}
"-"     {if(++cont) printf("\n"); printf("MINUS"); coluna += yyleng;}
"*"     {if(++cont) printf("\n"); printf("MULTIPLY"); coluna += yyleng;}
("//".*\n) { linha++; coluna = 1;}
"/*" {
    int lin = linha;
    int col = coluna;

    coluna += 2;

    int asterisk = 0;
    int slash = 0;

    char c;

    while(1) {
        c = input();
        coluna++;

        if(c == '/') {
            // Checar se */
            if(asterisk) break;

            slash = 1;
        } else if(c == '*') {
            asterisk = 1;
        } else if(c == '\0') {
            if(++cont) printf("\n");
            printf("error:lexical:%d:%d: unterminated comment", lin, col);
            break;
        } else {
            if(asterisk && slash) {
                if(++cont) printf("\n");
                printf("warning:%d:%d: '/*' within block comment", linha, coluna-3);
            }

            if(c == '\n') {
                linha++;
                coluna = 1;
            }

            asterisk = 0;
            slash = 0;
        }
    }
}
"/"         {if(++cont) printf("\n"); printf("DIV"); coluna += yyleng;}
%           {if(++cont) printf("\n"); printf("REMAINDER"); coluna += yyleng;}
"++"        {if(++cont) printf("\n"); printf("INC"); coluna += yyleng;}
"--"        {if(++cont) printf("\n"); printf("DEC"); coluna += yyleng;}
"&"         {if(++cont) printf("\n"); printf("BITWISE_AND"); coluna += yyleng;}
"|"         {if(++cont) printf("\n"); printf("BITWISE_OR"); coluna += yyleng;}
"~"         {if(++cont) printf("\n"); printf("BITWISE_NOT"); coluna += yyleng;}
"^"         {if(++cont) printf("\n"); printf("BITWISE_XOR"); coluna += yyleng;}
"!"         {if(++cont) printf("\n"); printf("NOT"); coluna += yyleng;}
"&&"        {if(++cont) printf("\n"); printf("LOGICAL_AND"); coluna += yyleng;}
"||"        {if(++cont) printf("\n"); printf("LOGICAL_OR"); coluna += yyleng;}
"=="        {if(++cont) printf("\n"); printf("EQUAL"); coluna += yyleng;}
"!="        {if(++cont) printf("\n"); printf("NOT_EQUAL"); coluna += yyleng;}
"<"         {if(++cont) printf("\n"); printf("LESS_THAN"); coluna += yyleng;}
">"         {if(++cont) printf("\n"); printf("GREATER_THAN"); coluna += yyleng;}
"<="        {if(++cont) printf("\n"); printf("LESS_EQUAL"); coluna += yyleng;}
">="        {if(++cont) printf("\n"); printf("GREATER_EQUAL"); coluna += yyleng;}
">>"        {if(++cont) printf("\n"); printf("R_SHIFT"); coluna += yyleng;}
"<<"        {if(++cont) printf("\n"); printf("L_SHIFT"); coluna += yyleng;}
"="         {if(++cont) printf("\n"); printf("ASSIGN"); coluna += yyleng;}
"+="        {if(++cont) printf("\n"); printf("ADD_ASSIGN"); coluna += yyleng;}
"-="        {if(++cont) printf("\n"); printf("MINUS_ASSIGN"); coluna += yyleng;}
";"         {if(++cont) printf("\n"); printf("SEMICOLON"); coluna += yyleng;}
","         {if(++cont) printf("\n"); printf("COMMA"); coluna += yyleng;}
":"         {if(++cont) printf("\n"); printf("COLON"); coluna += yyleng;}
"("         {if(++cont) printf("\n"); printf("L_PAREN"); coluna += yyleng;}
")"         {if(++cont) printf("\n"); printf("R_PAREN"); coluna += yyleng;}
"{"         {if(++cont) printf("\n"); printf("L_CURLY_BRACKET"); coluna += yyleng;}
"}"         {if(++cont) printf("\n"); printf("R_CURLY_BRACKET"); coluna += yyleng;}
"["         {if(++cont) printf("\n"); printf("L_SQUARE_BRACKET"); coluna += yyleng;}
"]"         {if(++cont) printf("\n"); printf("R_SQUARE_BRACKET"); coluna += yyleng;}
"?"         {if(++cont) printf("\n"); printf("TERNARY_CONDITIONAL"); coluna += yyleng;}
"#"         {if(++cont) printf("\n"); printf("NUMBER_SIGN"); coluna += yyleng;}
->          {if(++cont) printf("\n"); printf("POINTER"); coluna += yyleng;}
printf      {if(++cont) printf("\n"); printf("PRINTF"); coluna += yyleng;}
scanf       {if(++cont) printf("\n"); printf("SCANF"); coluna += yyleng;}
define      {if(++cont) printf("\n"); printf("DEFINE"); coluna += yyleng;}
exit        {if(++cont) printf("\n"); printf("EXIT"); coluna += yyleng;}
0[1-7][0-7]*        {if(++cont) printf("\n"); printf("NUM_OCTAL(%s)", yytext); coluna += yyleng;}
0[xX][0-9A-Fa-f]+   {if(++cont) printf("\n"); printf("NUM_HEXA(%s)", yytext); coluna += yyleng;}
[0-9]+              {if(++cont) printf("\n"); printf("NUM_INTEGER(%s)", yytext); coluna += yyleng;}
\'(\\.|.)\' {
    int size = yyleng;
    char *str = yytext + 1;
    str[size-2] = '\0';

    if(++cont) printf("\n");
    printf("CHARACTER(%s)", str);

    coluna += yyleng;
}
\"(\\.|[^\"])*\" {
    int size = yyleng;
    char *str = yytext + 1;
    str[size-2] = '\0';

    if(++cont) printf("\n");
    printf("STRING(%s)", str);

    coluna += yyleng;
}
[_a-zA-Z][a-zA-Z0-9_]* {
    if(++cont) printf("\n"); 

    if(yyleng > max_size) printf("error:lexical:%d:%d: identifier too long", linha, coluna);
    else printf("IDENTIFIER(%s)", yytext);

    coluna += yyleng;
}
[ ]+ { coluna+= yyleng; }
\n { linha++; coluna = 1; }
. {
    if(++cont) printf("\n"); 
    
    printf("error:lexical:%d:%d: %s", linha, coluna, yytext);

    coluna += yyleng;    
}

%%

int main() {
    yylex();

    return 0;
}
