/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SINTATICO_TAB_H_INCLUDED
# define YY_YY_SINTATICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VOID = 258,                    /* VOID  */
    INT = 259,                     /* INT  */
    CHAR = 260,                    /* CHAR  */
    RETURN = 261,                  /* RETURN  */
    BREAK = 262,                   /* BREAK  */
    SWITCH = 263,                  /* SWITCH  */
    CASE = 264,                    /* CASE  */
    DEFAULT = 265,                 /* DEFAULT  */
    DO = 266,                      /* DO  */
    WHILE = 267,                   /* WHILE  */
    FOR = 268,                     /* FOR  */
    IF = 269,                      /* IF  */
    ELSE = 270,                    /* ELSE  */
    TYPEDEF = 271,                 /* TYPEDEF  */
    STRUCT = 272,                  /* STRUCT  */
    PLUS = 273,                    /* PLUS  */
    MINUS = 274,                   /* MINUS  */
    MULTIPLY = 275,                /* MULTIPLY  */
    DIV = 276,                     /* DIV  */
    REMAINDER = 277,               /* REMAINDER  */
    INC = 278,                     /* INC  */
    DEC = 279,                     /* DEC  */
    BITWISE_AND = 280,             /* BITWISE_AND  */
    BITWISE_OR = 281,              /* BITWISE_OR  */
    BITWISE_NOT = 282,             /* BITWISE_NOT  */
    BITWISE_XOR = 283,             /* BITWISE_XOR  */
    NOT = 284,                     /* NOT  */
    LOGICAL_AND = 285,             /* LOGICAL_AND  */
    LOGICAL_OR = 286,              /* LOGICAL_OR  */
    EQUAL = 287,                   /* EQUAL  */
    NOT_EQUAL = 288,               /* NOT_EQUAL  */
    LESS_THAN = 289,               /* LESS_THAN  */
    GREATER_THAN = 290,            /* GREATER_THAN  */
    LESS_EQUAL = 291,              /* LESS_EQUAL  */
    GREATER_EQUAL = 292,           /* GREATER_EQUAL  */
    R_SHIFT = 293,                 /* R_SHIFT  */
    L_SHIFT = 294,                 /* L_SHIFT  */
    ASSIGN = 295,                  /* ASSIGN  */
    ADD_ASSIGN = 296,              /* ADD_ASSIGN  */
    MINUS_ASSIGN = 297,            /* MINUS_ASSIGN  */
    SEMICOLON = 298,               /* SEMICOLON  */
    COMMA = 299,                   /* COMMA  */
    COLON = 300,                   /* COLON  */
    L_PAREN = 301,                 /* L_PAREN  */
    R_PAREN = 302,                 /* R_PAREN  */
    L_CURLY_BRACKET = 303,         /* L_CURLY_BRACKET  */
    L_SQUARE_BRACKET = 304,        /* L_SQUARE_BRACKET  */
    R_SQUARE_BRACKET = 305,        /* R_SQUARE_BRACKET  */
    TERNARY_CONDITIONAL = 306,     /* TERNARY_CONDITIONAL  */
    NUMBER_SIGN = 307,             /* NUMBER_SIGN  */
    POINTER = 308,                 /* POINTER  */
    PRINTF = 309,                  /* PRINTF  */
    SCANF = 310,                   /* SCANF  */
    DEFINE = 311,                  /* DEFINE  */
    EXIT = 312,                    /* EXIT  */
    IDENTIFIER = 313,              /* IDENTIFIER  */
    NUM_OCTAL = 314,               /* NUM_OCTAL  */
    NUM_INTEGER = 315,             /* NUM_INTEGER  */
    NUM_HEXA = 316,                /* NUM_HEXA  */
    STRING = 317,                  /* STRING  */
    CHARACTER = 318,               /* CHARACTER  */
    R_CURLY_BRACKET = 319,         /* R_CURLY_BRACKET  */
    LONG_IDENTIFIER = 320,         /* LONG_IDENTIFIER  */
    UNKNOWN_CHARACTER = 321,       /* UNKNOWN_CHARACTER  */
    UNTERMINATED_COMMENT = 322,    /* UNTERMINATED_COMMENT  */
    END_OF_FILE = 323              /* END_OF_FILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SINTATICO_TAB_H_INCLUDED  */
