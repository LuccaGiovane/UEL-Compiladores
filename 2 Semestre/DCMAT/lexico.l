%option noyywrap

%{
    #include <string.h>
    #include "sintatico.tab.h"
    #include "ast.h"
    extern YYSTYPE yylval;
    int lexicalError = 0;

%}

%%

\n      { return EOL; }
\r      { }
" "
<<EOF>>     { return EOL; }

"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"^"     { return POT; }
"%"     { return MOD; }
"("     { return LPAREN; }
")"     { return RPAREN; }
":"     { return COLON; }
"="     { return EQUAL; }
":="    { return ASSIGN; }
"["     { return LBRACKET; }
"]"     { return RBRACKET; }
";"     { return SEMICOLON; }
","     { return COMMA; }

about                       { return ABOUT; }
abs                         { return ABS; }
axis                        { return AXIS; }
connect_dots                { return CONNECT_DOTS; }
cos                         { return COS; }
determinant                 { return DETERMINANT; }
[eE]                        { return CONST_E; }
erase                       { return ERASE; }
float                       { return FLOAT; }
h_view                      { return H_VIEW; }
("pi"|"pI"|"Pi"|"PI")       { return CONST_PI; }
integral_steps              { return INTEGRAL_STEPS; }
integrate                   { return INTEGRATE; }
linear_system               { return LINEAR_SYSTEM; }
matrix                      { return MATRIX; }
off                         { return OFF; }
on                          { return ON; }
plot                        { return PLOT; }
precision                   { return PRECISION; }
quit                        { return QUIT; }
reset                       { return RESET; }
rpn                         { return RPN; }
sen                         { return SEN; }
set                         { return SET; }
settings                    { return SETTINGS; }
show                        { return SHOW; }
solve                       { return SOLVE; }
sum                         { return SUM; }
symbols                     { return SYMBOLS; }
tan                         { return TAN; }
v_view                      { return V_VIEW; }
[xX]                        { return CONST_X; }


[0-9]+"."[0-9]+             { yylval.retFloat = atof(yytext); return FLOAT_NUMBER; }
[0-9]+                      { yylval.retInteiro = atoi(yytext); return INTEGER_NUMBER; }
[a-zA-Z]+[_0-9a-zA-Z]*      { yylval.retString = strdup(yytext); return IDENTIFIER; }
.                           { printf("\nInvalid Symbol: %s\n", yytext); lexicalError = 1; return LEXERROR; }

%%

void scan_string(char * str) {
    yy_scan_string(str);
}

void delete_buffer() {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}
