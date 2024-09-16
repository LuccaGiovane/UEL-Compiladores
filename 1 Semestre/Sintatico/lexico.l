/* Nao usar a biblioteca do flex*/
%option noyywrap

%x lineComment


%{
#include <sintatico.tab.h>
#include <stdio.h>
#include <string.h>

    /* Globais */
int L_lastCommentStart = 0;
int C_lastCommentStart = 0;
int totalLines = 1;
int totalChars = 1;
int encounteredSyntaxError = 0;     // Flag para indicar se houve algum erro de sintaxe
char lineError[1024] = "";          // Buffer para armazenar o conteúdo do comentário de linha (inicializado vazio)


    /* Constantes */
#define EOL 10  // Código ASCII para nova linha (line feed)


    /* Macros */
#define INCREMENT_CHARS() { totalChars++; }
#define RETURN_TOKEN(token) { totalChars++; return token; }
#define RETURN_TOKEN_WITH_INCREMENT(token, increment) { totalChars += increment; return token; }
#define RETURN_TOKEN_WITH_LENGTH(token) { totalChars += strlen(yytext); return token; }
#define HANDLE_NEWLINE() { totalLines++; totalChars = 1; }

%}
%x COMMENT

%%

"void"		RETURN_TOKEN_WITH_INCREMENT(VOID, 4)
"int"		RETURN_TOKEN_WITH_INCREMENT(INT, 3)
"char"		RETURN_TOKEN_WITH_INCREMENT(CHAR, 4)
"return"	RETURN_TOKEN_WITH_INCREMENT(RETURN, 6)
"break"		RETURN_TOKEN_WITH_INCREMENT(BREAK, 5)
"switch"	RETURN_TOKEN_WITH_INCREMENT(SWITCH, 6)
"case"		RETURN_TOKEN_WITH_INCREMENT(CASE, 4)
"default"	RETURN_TOKEN_WITH_INCREMENT(DEFAULT, 7)
"do"		RETURN_TOKEN_WITH_INCREMENT(DO, 2)
"while"		RETURN_TOKEN_WITH_INCREMENT(WHILE, 5)
"for"		RETURN_TOKEN_WITH_INCREMENT(FOR, 3)
"if"		RETURN_TOKEN_WITH_INCREMENT(IF, 2)
"else"		RETURN_TOKEN_WITH_INCREMENT(ELSE, 4)
"typedef"	RETURN_TOKEN_WITH_INCREMENT(TYPEDEF, 7)
"struct"	RETURN_TOKEN_WITH_INCREMENT(STRUCT, 6)
"+"		    RETURN_TOKEN(ADD)
"-"		    RETURN_TOKEN(SUB)
"*"		    RETURN_TOKEN(MULT)
"/"		    RETURN_TOKEN(DIV)
"%"		    RETURN_TOKEN(MOD)
"++"	    RETURN_TOKEN_WITH_INCREMENT(INC, 2)
"--"	    RETURN_TOKEN_WITH_INCREMENT(DEC, 2)
"&"		    RETURN_TOKEN(BIT_AND)
"|"		    RETURN_TOKEN(BIT_OR)
"~"		    RETURN_TOKEN(BIT_NOT)
"^"		    RETURN_TOKEN(BIT_XOR)
"&&"	    RETURN_TOKEN_WITH_INCREMENT(LOG_AND, 2)
"||"	    RETURN_TOKEN_WITH_INCREMENT(LOG_OR, 2)
"!"		    RETURN_TOKEN(LOG_NOT)
"=="	    RETURN_TOKEN_WITH_INCREMENT(EQUALS, 2)
"!="	    RETURN_TOKEN_WITH_INCREMENT(NOT_EQUALS, 2)
"<"		    RETURN_TOKEN(LESS)
">"		    RETURN_TOKEN(GREAT)
"<="	    RETURN_TOKEN_WITH_INCREMENT(LEQ, 2)
">="	    RETURN_TOKEN_WITH_INCREMENT(GEQ, 2)
">>"	    RETURN_TOKEN_WITH_INCREMENT(RSHIFT, 2)
"<<"	    RETURN_TOKEN_WITH_INCREMENT(LSHIFT, 2)
"="		    RETURN_TOKEN(ASSIGN)
"+="	    RETURN_TOKEN_WITH_INCREMENT(ADD_ASSIGN, 2)
"-="	    RETURN_TOKEN_WITH_INCREMENT(SUB_ASSIGN, 2)
"printf"	RETURN_TOKEN_WITH_INCREMENT(PRINTF_T, 6)
"scanf"		RETURN_TOKEN_WITH_INCREMENT(SCANF_T, 5)
"exit"		RETURN_TOKEN_WITH_INCREMENT(EXIT_T, 4)
"#"			RETURN_TOKEN(NUMBER_SIGN)
"define"	RETURN_TOKEN_WITH_INCREMENT(DEFINE_T, 6)
";"		    RETURN_TOKEN(SEMICOLON)
","		    RETURN_TOKEN(COMMA)
":"		    RETURN_TOKEN(COLON)
"("		    RETURN_TOKEN(LPAREN)
")"		    RETURN_TOKEN(RPAREN)
"{"		    RETURN_TOKEN(LCBRACK)
"}"		    RETURN_TOKEN(RCBRACK)
"["		    RETURN_TOKEN(LBRACK)
"]"		    RETURN_TOKEN(RBRACK)
"?"		    RETURN_TOKEN(QUEST_MARK)
"->"	    RETURN_TOKEN_WITH_INCREMENT(POINTER_DEFERENCE, 2)
"0"("x"|"X")([a-fA-F0-9])+		 RETURN_TOKEN_WITH_LENGTH(NUM_HEXA)
"0"[1-7][0-7]*					 RETURN_TOKEN_WITH_LENGTH(NUM_OCTA)
[0-9]+							 RETURN_TOKEN_WITH_LENGTH(NUM_INT)
"\'""\\"?."\'"					 RETURN_TOKEN_WITH_LENGTH(CHARACTER)
\"(\\.|[^"\\])*\"				 RETURN_TOKEN_WITH_LENGTH(STRING)
([a-zA-Z]|"_")([a-zA-Z0-9]|"_")* {
    if (strlen(yytext) > 255) {
        printf("error:lexical:%d:%d: identifier too long", totalLines, totalChars);
        exit(1);  // Indica erro e interrompe o processamento

    } else {
        RETURN_TOKEN_WITH_LENGTH(IDENTIFIER)
    }
}

   /* Tratamento de comentarios em bloco, quase fiquei careca de raiva */
"/*"                             {
    totalChars +=2; 
    L_lastCommentStart=totalLines; 
    C_lastCommentStart=totalChars; 
    BEGIN(COMMENT);
    }
<COMMENT>"*/"                    {
    totalChars +=2; 
    BEGIN(INITIAL);
    }
<COMMENT>"/*/"                   {
    totalChars +=3; 
    BEGIN(INITIAL);
    }
<COMMENT>"//"                    {
    totalChars +=2;
    }
<COMMENT>"/*"                    {
    printf("warning:%d:%d: '/*' within block comment\n", totalLines, totalChars+1); 
    totalChars +=2;
    }
<COMMENT>[\n]                    {
    totalLines += 1; 
    totalChars = 0;
    }
<COMMENT>[^*/[\n]]+|.            {
    totalChars += strlen(yytext);
    }
<COMMENT><<EOF>>                 { 
    printf("error:lexical:%d:%d: unterminated comment", L_lastCommentStart, C_lastCommentStart - 2);
    fflush(stdout);  // Força o descarregamento do buffer
    exit(1);  
    }

    /* Tratamento de comentarios em linha, God Bless foi de primeira */
"//".*                           { 
    totalChars = totalChars; 
    strcat(lineError, yytext); 
    
    BEGIN(lineComment); 
    }
<lineComment>\n                  {
    totalLines += 1;
    totalChars = 1; 
    
    BEGIN(INITIAL);

    if (!encounteredSyntaxError) 
    {
        memset(lineError, 0, sizeof(lineError));
    
    } else {
        return EOL;  // Retorna o fim de linha
    }
}

[ \r\t\f]						 INCREMENT_CHARS()
[\n]				   			 HANDLE_NEWLINE()
<<EOF>>		                     {return END_OF_FILE;}
.								 RETURN_TOKEN(OTHER)

%%
