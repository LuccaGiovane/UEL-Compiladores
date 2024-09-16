%{
#include<stdio.h>
#include<string.h>

extern int totalLines;
extern int totalChars;
extern int yylex();
extern char* yytext;

void yyerror(char *s);

FILE* inputFile = NULL;

void seekAndPrintLine(FILE* auxFile, int aux)
{
	char character;
	int i;
	fseek(auxFile, 0, SEEK_SET);

	i = 1;

	while(i < aux)
	{
		character = fgetc(auxFile);
		
		if(character == '\n')
		{ 
            i++; 
        }
		if(character == EOF)
		{ 
            break; 
        }
	}

	character = fgetc(auxFile);
	
	while(character != '\n' && character != EOF)
	{
		printf("%c", character);
		character = fgetc(auxFile);
	}
	printf("\n");
}

void success()
{
	printf("SUCCESSFUL COMPILATION.");
}

%}

%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
%token ADD
%token SUB
%token MULT
%token DIV
%token MOD
%token INC
%token DEC
%token BIT_AND
%token BIT_OR
%token BIT_NOT
%token BIT_XOR
%token RSHIFT
%token LSHIFT
%token LOG_AND
%token LOG_OR
%token LOG_NOT
%token EQUALS
%token NOT_EQUALS
%token LESS
%token GREAT
%token LEQ
%token GEQ
%token ASSIGN
%token ADD_ASSIGN
%token SUB_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token LPAREN
%token RPAREN
%token LCBRACK
%token RCBRACK
%token LBRACK
%token RBRACK
%token QUEST_MARK
%token NUMBER_SIGN
%token POINTER_DEFERENCE
%token DEFINE_T
%token PRINTF_T
%token SCANF_T
%token EXIT_T
%token NUM_HEXA
%token NUM_OCTA
%token NUM_INT
%token CHARACTER
%token STRING
%token IDENTIFIER
%token LINE_COMMENT
%token BLOCK_COMMENT
%token UNTERMINATED_COMMENT
%token OTHER
%token END_OF_FILE

%start programaStart

%%

programaStart: prog programaStart END_OF_FILE																						{success(); return 0;}
		| prog END_OF_FILE		    																								{success(); return 0;}
;

prog: declaration 																													{}
    | function    																													{}
;

declaration: NUMBER_SIGN DEFINE_T IDENTIFIER expression  																			{}
          | var_declaration                              																			{}
          | prot_declaration                             																			{}
;

function: type pointer IDENTIFIER parameters LCBRACK function_var_declaration commands RCBRACK										{}
;

function_var_declaration: var_declaration function_var_declaration																	{}
		   |              				    																						{}
;

var_declaration: type dec_var SEMICOLON 																							{}
;

dec_var: pointer IDENTIFIER array ASSIGN assignment dec_var_aux 																	{}
       | pointer IDENTIFIER array dec_var_aux       																				{}
;

dec_var_aux: COMMA dec_var 																											{}
           |               																											{}
;

prot_declaration: type pointer IDENTIFIER parameters SEMICOLON																		{}
;

parameters: LPAREN param RPAREN																										{}
;

param: type pointer IDENTIFIER array param_aux																						{}
	 |	                                        																					{}
;

param_aux: COMMA param																												{}
		 |         																													{}
;

array: LBRACK expression RBRACK array																								{}
	 |              																												{}
;

type: INT																															{}
	| CHAR																															{}
	| VOID																															{}
;

block: LCBRACK commands RCBRACK	{}
;

commands: command_list commands	{}
		| command_list			{}
;

command_list: DO block WHILE LPAREN expression RPAREN SEMICOLON	                                									{}
			  | IF LPAREN expression RPAREN block else_exp				                                							{}
			  | WHILE LPAREN expression RPAREN block					                                							{}
			  | FOR LPAREN optional_expression SEMICOLON optional_expression SEMICOLON optional_expression RPAREN block				{}
			  | PRINTF_T LPAREN STRING printf_exp RPAREN SEMICOLON		                                							{}
			  | SCANF_T LPAREN STRING COMMA BIT_AND IDENTIFIER RPAREN SEMICOLON		                								{}
			  | EXIT_T LPAREN expression RPAREN SEMICOLON				                                							{}
			  | RETURN optional_expression SEMICOLON								                            					{}
			  | expression SEMICOLON										                                						{}
			  | SEMICOLON												                                							{}
			  | block													                                							{}
;

printf_exp: COMMA expression																										{}
		  |             																											{}
;

else_exp: ELSE block																												{}
		|               																											{}
;

optional_expression: expression																										{}
	   		|            																											{}
;

expression: assignment                 																								{}
         | assignment COMMA expression 																								{}
;

assignment: exp_cond                         																						{}
          | unary_expression ASSIGN assignment     																					{}
          | unary_expression ADD_ASSIGN assignment 																					{}
          | unary_expression SUB_ASSIGN assignment 																					{}
;

exp_cond: exp_or_log                                     																			{}
        | exp_or_log QUEST_MARK expression COLON exp_cond 																			{}
;

exp_or_log: exp_and_log                  																							{}
        | exp_and_log LOG_OR exp_and_log 																							{}
;

exp_and_log: exp_or                 																								{}
           | exp_or LOG_AND exp_or  																								{}
;

exp_or: exp_xor                																										{}
      | exp_xor BIT_OR exp_xor 																										{}
;

exp_xor: exp_and                 																									{}
       | exp_and BIT_XOR exp_and 																									{}
;

exp_and: exp_equals                         																						{}
       | exp_equals BIT_AND exp_equals 																								{}
;

exp_equals: exp_relational                           																				{}
             | exp_relational EQUALS exp_relational     																			{}
             | exp_relational NOT_EQUALS exp_relational 																			{}
;

exp_relational: exp_shift					    																					{}
		      | exp_shift LESS exp_relational   																					{}
		      | exp_shift LEQ exp_relational																						{}
		      | exp_shift GEQ exp_relational																						{}
		      | exp_shift GREAT exp_relational																						{}
;

exp_shift: exp_add																													{}
		 | exp_add LSHIFT exp_shift																									{}
		 | exp_add RSHIFT exp_shift																									{}
;

exp_add: exp_mult																													{}
	   | exp_mult ADD exp_add																										{}
	   | exp_mult SUB exp_add																										{}
;

exp_mult: exp_cast																													{}
		| exp_cast MULT exp_mult																									{}
		| exp_cast DIV exp_mult																										{}
		| exp_cast MOD exp_mult																										{}
;

exp_cast: unary_expression																											{}
		| LPAREN type pointer RPAREN exp_cast																						{}
;

unary_expression: exp_postfix																										{}
		  | INC unary_expression																									{}
		  | DEC unary_expression																									{}
		  | BIT_AND exp_cast																										{}
		  | MULT exp_cast																											{}
		  | ADD exp_cast																											{}
		  | SUB exp_cast																											{}
		  | BIT_NOT exp_cast																										{}
		  | LOG_NOT exp_cast																										{}
;

exp_postfix: exp_prim				                            																	{}
		   | exp_postfix INC		                            																	{}
		   | exp_postfix DEC		                            																	{}
		   | exp_postfix LBRACK expression RBRACK			    																	{}
		   | exp_postfix LPAREN RPAREN						    																	{}
		   | exp_postfix LPAREN assignment exp_pf_aux RPAREN																		{}
;

exp_pf_aux: COMMA assignment exp_pf_aux																								{}
		  |       					    																							{}
;

exp_prim: IDENTIFIER	            																								{}
		| num               																										{}
		| CHARACTER		            																								{}
		| STRING		            																								{}
		| LPAREN expression RPAREN																									{}
;

num: NUM_INT																														{}
   | NUM_HEXA																														{}
   | NUM_OCTA																														{}
;

pointer: MULT 																														{}
       |          																													{}
;

%%

	/* Função responsável por lidar com os tokens que representam erros */
void yyerror(char *s)
{
	int spaces;

	// Verificar se há um comentário de linha e um EOF
    if (yychar == END_OF_FILE && yytext[0] == '/') 
    { 
		totalChars -= strlen(yytext);
        printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", totalLines, totalChars);
    }
	else if(yychar == UNTERMINATED_COMMENT || yychar == OTHER)
	{// Verificar se o erro é de comentário não terminado ou outro erro léxico
		
		printf("error:lexical:%d:", totalLines);
		
		if(yychar == UNTERMINATED_COMMENT)
		{
			// Mensagem de erro específica para comentário não terminado
			printf("%d: unterminated comment", totalChars);
		}
		else
		{
			// Caso de erro léxico genérico
			totalChars -= strlen(yytext);
			printf("%d: %s", totalChars, yytext);
		}
	}
	else // Lidar com erros sintáticos genéricos
	{
		printf("error:syntax:%d:", totalLines);
		if(yychar == END_OF_FILE || yychar == LINE_COMMENT)
		{
			// Erro ao final do arquivo ou comentário de linha incompleto
			printf("%d: expected declaration or statement at end of input\n", totalChars);
		}
		else
		{
			// Erro de sintaxe genérico
			totalChars -= strlen(yytext);
			printf("%d: %s\n", totalChars, yytext);
		}
		// Imprimir a linha onde ocorreu o erro
		seekAndPrintLine(inputFile, totalLines);

		// Imprimir os espaços para posicionar o marcador "^"
		spaces = 1;
		while(spaces < totalChars)
		{ 
			printf(" "); 
			spaces++;
		}
		// Posicionar o marcador "^" para mostrar o local do erro
		printf("^");
	}
}

int main(int argc, char **argv)
{
	inputFile = stdin;
	yyparse();
    return 0;
}