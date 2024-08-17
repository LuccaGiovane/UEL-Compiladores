/* Não usar a biblioteca do Flex */
%option noyywrap

%{
#include <stdio.h>

int lines = 1;
int blankLines = 0;
int linesWithComments = 0;
int nbNcLines = 0;
int semicolons = 0;
int preprocessingDirectives = 0;

int totalLines = 0;
int totalBlankLines = 0;
int totalLinesWithComments = 0;
int totalNbNcLines = 0;
int totalSemicolons = 0;
int totalPreprocessingDirectives = 0;

/*
A macro INCREMENTA_LINES tem as seguintes funcionalidades:
    - Incrementa a variável global 'lines'.
*/
#define INCREMENTA_LINES() \
    do { \
        lines++; \
    } while (0)

/*
A macro INCREMENTA_BLANK_LINES tem as seguintes funcionalidades:
    - Incrementa a variável global 'blankLines'.
    - Incrementa a variável global 'lines'.
*/
#define INCREMENTA_BLANK_LINES() \
    do { \
        blankLines++; \
        lines++; \
    } while (0)

/*
A macro INCREMENTA_LINES_WITH_COMMENTS tem as seguintes funcionalidades:
    - Incrementa a variável global 'linesWithComments'.
    - Incrementa a variável global 'lines'.
*/
#define INCREMENTA_LINES_WITH_COMMENTS() \
    do { \
        linesWithComments++; \
        lines++; \
    } while (0)

/*
A macro INCREMENTA_SEMICOLONS tem as seguintes funcionalidades:
    - Incrementa a variável global 'semicolons'.
*/
#define INCREMENTA_SEMICOLONS() \
    do { \
        semicolons++; \
    } while (0)

/*
A macro INCREMENTA_PREPROCESSING_DIRECTIVES tem as seguintes funcionalidades:
    - Incrementa a variável global 'preprocessingDirectives'.
*/
#define INCREMENTA_PREPROCESSING_DIRECTIVES() \
    do { \
        preprocessingDirectives++; \
    } while (0)

%}

%x N_LINE_COMMENT

%%

"/*"                        {BEGIN(N_LINE_COMMENT);}
<N_LINE_COMMENT>[^*\n]+     {/* Do nothing */}
<N_LINE_COMMENT>\n          {INCREMENTA_LINES_WITH_COMMENTS();}
<N_LINE_COMMENT>"*/"        {INCREMENTA_LINES_WITH_COMMENTS(); BEGIN(INITIAL);}

\/\/.*\n                    {INCREMENTA_LINES_WITH_COMMENTS();}
^[ \t]*[\n]                 {INCREMENTA_BLANK_LINES();}
[\n]                        {INCREMENTA_LINES();}
";"                         {INCREMENTA_SEMICOLONS();}
"#include"                  {INCREMENTA_PREPROCESSING_DIRECTIVES();}
"#define"                   {INCREMENTA_PREPROCESSING_DIRECTIVES();}
.                           {/* Do nothing */}

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "No input file provided.\n");
        return 1;
    }

    printf("%6s%9s%9s%9s%9s%9s%5s\n", "total", "blank", "lines w/", "nb, nc", "semi-", "prepoc.", "file");
    printf("%6s%9s%9s%9s%9s%9s\n", "lines", "lines", "comments", "lines", "colons", "direct.");
    printf("------+--------+--------+--------+--------+--------+----\n");

    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            return 1;
        }

        yyrestart(f);
        yylex();
        fclose(f);

        nbNcLines = lines - (blankLines + linesWithComments);

        printf("%6d%9d%9d%9d%9d%9d %s\n", lines, blankLines, linesWithComments, nbNcLines, semicolons, preprocessingDirectives, argv[i]);
        totalLines += lines; lines = 1;
        totalBlankLines += blankLines; blankLines = 0;
        totalLinesWithComments += linesWithComments; linesWithComments = 0;
        totalNbNcLines += nbNcLines;
        totalSemicolons += semicolons; semicolons = 0;
        totalPreprocessingDirectives += preprocessingDirectives; preprocessingDirectives = 0;
    }

    printf("%6d%9d%9d%9d%9d%9d %s\n", totalLines, totalBlankLines, totalLinesWithComments, totalNbNcLines, totalSemicolons, totalPreprocessingDirectives, "total");

    return 0;
}
