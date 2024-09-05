/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintatico.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int yylex();

    extern int yylineno;
    extern int yycolno;
    extern int yyleng;
    extern int comment_start_line;
    extern int comment_start_col;
    extern int last_token_line;
    extern int last_token_col;

    extern char *yytext;
    extern char nextline[1];

    void yyerror(char *s);


#line 93 "sintatico.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sintatico.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_CHAR = 5,                       /* CHAR  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_BREAK = 7,                      /* BREAK  */
  YYSYMBOL_SWITCH = 8,                     /* SWITCH  */
  YYSYMBOL_CASE = 9,                       /* CASE  */
  YYSYMBOL_DEFAULT = 10,                   /* DEFAULT  */
  YYSYMBOL_DO = 11,                        /* DO  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_TYPEDEF = 16,                   /* TYPEDEF  */
  YYSYMBOL_STRUCT = 17,                    /* STRUCT  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MINUS = 19,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 20,                  /* MULTIPLY  */
  YYSYMBOL_DIV = 21,                       /* DIV  */
  YYSYMBOL_REMAINDER = 22,                 /* REMAINDER  */
  YYSYMBOL_INC = 23,                       /* INC  */
  YYSYMBOL_DEC = 24,                       /* DEC  */
  YYSYMBOL_BITWISE_AND = 25,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 26,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_NOT = 27,               /* BITWISE_NOT  */
  YYSYMBOL_BITWISE_XOR = 28,               /* BITWISE_XOR  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_LOGICAL_AND = 30,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 31,                /* LOGICAL_OR  */
  YYSYMBOL_EQUAL = 32,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 33,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 34,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 35,              /* GREATER_THAN  */
  YYSYMBOL_LESS_EQUAL = 36,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 37,             /* GREATER_EQUAL  */
  YYSYMBOL_R_SHIFT = 38,                   /* R_SHIFT  */
  YYSYMBOL_L_SHIFT = 39,                   /* L_SHIFT  */
  YYSYMBOL_ASSIGN = 40,                    /* ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 41,                /* ADD_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 42,              /* MINUS_ASSIGN  */
  YYSYMBOL_SEMICOLON = 43,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 44,                     /* COMMA  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_L_PAREN = 46,                   /* L_PAREN  */
  YYSYMBOL_R_PAREN = 47,                   /* R_PAREN  */
  YYSYMBOL_L_CURLY_BRACKET = 48,           /* L_CURLY_BRACKET  */
  YYSYMBOL_L_SQUARE_BRACKET = 49,          /* L_SQUARE_BRACKET  */
  YYSYMBOL_R_SQUARE_BRACKET = 50,          /* R_SQUARE_BRACKET  */
  YYSYMBOL_TERNARY_CONDITIONAL = 51,       /* TERNARY_CONDITIONAL  */
  YYSYMBOL_NUMBER_SIGN = 52,               /* NUMBER_SIGN  */
  YYSYMBOL_POINTER = 53,                   /* POINTER  */
  YYSYMBOL_PRINTF = 54,                    /* PRINTF  */
  YYSYMBOL_SCANF = 55,                     /* SCANF  */
  YYSYMBOL_DEFINE = 56,                    /* DEFINE  */
  YYSYMBOL_EXIT = 57,                      /* EXIT  */
  YYSYMBOL_IDENTIFIER = 58,                /* IDENTIFIER  */
  YYSYMBOL_NUM_OCTAL = 59,                 /* NUM_OCTAL  */
  YYSYMBOL_NUM_INTEGER = 60,               /* NUM_INTEGER  */
  YYSYMBOL_NUM_HEXA = 61,                  /* NUM_HEXA  */
  YYSYMBOL_STRING = 62,                    /* STRING  */
  YYSYMBOL_CHARACTER = 63,                 /* CHARACTER  */
  YYSYMBOL_R_CURLY_BRACKET = 64,           /* R_CURLY_BRACKET  */
  YYSYMBOL_LONG_IDENTIFIER = 65,           /* LONG_IDENTIFIER  */
  YYSYMBOL_UNKNOWN_CHARACTER = 66,         /* UNKNOWN_CHARACTER  */
  YYSYMBOL_UNTERMINATED_COMMENT = 67,      /* UNTERMINATED_COMMENT  */
  YYSYMBOL_END_OF_FILE = 68,               /* END_OF_FILE  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_programa = 70,                  /* programa  */
  YYSYMBOL_asterisco = 71,                 /* asterisco  */
  YYSYMBOL_programa_loop = 72,             /* programa_loop  */
  YYSYMBOL_declaracoes = 73,               /* declaracoes  */
  YYSYMBOL_funcao = 74,                    /* funcao  */
  YYSYMBOL_funcao_declaracao_loop = 75,    /* funcao_declaracao_loop  */
  YYSYMBOL_declaracao_de_variaveis = 76,   /* declaracao_de_variaveis  */
  YYSYMBOL_declaracao_de_variaveis_exp_loop = 77, /* declaracao_de_variaveis_exp_loop  */
  YYSYMBOL_declaracao_de_variaveis_virg_loop = 78, /* declaracao_de_variaveis_virg_loop  */
  YYSYMBOL_declaracao_de_prototipos = 79,  /* declaracao_de_prototipos  */
  YYSYMBOL_parametros = 80,                /* parametros  */
  YYSYMBOL_parametros_exp_loop = 81,       /* parametros_exp_loop  */
  YYSYMBOL_parametros_virg_loop = 82,      /* parametros_virg_loop  */
  YYSYMBOL_tipo = 83,                      /* tipo  */
  YYSYMBOL_bloco = 84,                     /* bloco  */
  YYSYMBOL_comandos = 85,                  /* comandos  */
  YYSYMBOL_comandos_loop = 86,             /* comandos_loop  */
  YYSYMBOL_lista_de_comandos = 87,         /* lista_de_comandos  */
  YYSYMBOL_lista_de_comandos_jump_exp_1 = 88, /* lista_de_comandos_jump_exp_1  */
  YYSYMBOL_lista_de_comandos_jump_exp_2 = 89, /* lista_de_comandos_jump_exp_2  */
  YYSYMBOL_lista_de_comandos_jump_exp_3 = 90, /* lista_de_comandos_jump_exp_3  */
  YYSYMBOL_expressao = 91,                 /* expressao  */
  YYSYMBOL_expressao_de_atribuicao = 92,   /* expressao_de_atribuicao  */
  YYSYMBOL_expressao_condicional = 93,     /* expressao_condicional  */
  YYSYMBOL_expressao_or_logico = 94,       /* expressao_or_logico  */
  YYSYMBOL_expressao_and_logico = 95,      /* expressao_and_logico  */
  YYSYMBOL_expressao_or = 96,              /* expressao_or  */
  YYSYMBOL_expressao_xor = 97,             /* expressao_xor  */
  YYSYMBOL_expressao_and = 98,             /* expressao_and  */
  YYSYMBOL_expressao_de_igualdade = 99,    /* expressao_de_igualdade  */
  YYSYMBOL_expressao_relacional = 100,     /* expressao_relacional  */
  YYSYMBOL_expressao_shift = 101,          /* expressao_shift  */
  YYSYMBOL_expressao_aditiva = 102,        /* expressao_aditiva  */
  YYSYMBOL_expressao_multiplicativa = 103, /* expressao_multiplicativa  */
  YYSYMBOL_expressao_cast = 104,           /* expressao_cast  */
  YYSYMBOL_expressao_unaria = 105,         /* expressao_unaria  */
  YYSYMBOL_expressao_pos_fixa = 106,       /* expressao_pos_fixa  */
  YYSYMBOL_expressao_pos_fixa_loop = 107,  /* expressao_pos_fixa_loop  */
  YYSYMBOL_expressao_primaria = 108,       /* expressao_primaria  */
  YYSYMBOL_numero = 109                    /* numero  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   552

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  253

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    96,    96,    97,   100,   101,   104,   105,   108,   109,
     110,   113,   117,   118,   121,   122,   125,   126,   129,   130,
     131,   134,   137,   138,   141,   142,   145,   146,   148,   149,
     150,   153,   156,   159,   160,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   179,
     180,   183,   184,   187,   188,   190,   191,   194,   195,   196,
     197,   200,   201,   204,   205,   208,   209,   212,   213,   216,
     217,   220,   221,   224,   225,   226,   229,   230,   231,   232,
     233,   236,   237,   238,   241,   242,   243,   246,   247,   248,
     249,   252,   253,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   267,   268,   269,   270,   271,   272,   275,   276,
     279,   280,   281,   282,   283,   286,   287,   288
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "INT", "CHAR",
  "RETURN", "BREAK", "SWITCH", "CASE", "DEFAULT", "DO", "WHILE", "FOR",
  "IF", "ELSE", "TYPEDEF", "STRUCT", "PLUS", "MINUS", "MULTIPLY", "DIV",
  "REMAINDER", "INC", "DEC", "BITWISE_AND", "BITWISE_OR", "BITWISE_NOT",
  "BITWISE_XOR", "NOT", "LOGICAL_AND", "LOGICAL_OR", "EQUAL", "NOT_EQUAL",
  "LESS_THAN", "GREATER_THAN", "LESS_EQUAL", "GREATER_EQUAL", "R_SHIFT",
  "L_SHIFT", "ASSIGN", "ADD_ASSIGN", "MINUS_ASSIGN", "SEMICOLON", "COMMA",
  "COLON", "L_PAREN", "R_PAREN", "L_CURLY_BRACKET", "L_SQUARE_BRACKET",
  "R_SQUARE_BRACKET", "TERNARY_CONDITIONAL", "NUMBER_SIGN", "POINTER",
  "PRINTF", "SCANF", "DEFINE", "EXIT", "IDENTIFIER", "NUM_OCTAL",
  "NUM_INTEGER", "NUM_HEXA", "STRING", "CHARACTER", "R_CURLY_BRACKET",
  "LONG_IDENTIFIER", "UNKNOWN_CHARACTER", "UNTERMINATED_COMMENT",
  "END_OF_FILE", "$accept", "programa", "asterisco", "programa_loop",
  "declaracoes", "funcao", "funcao_declaracao_loop",
  "declaracao_de_variaveis", "declaracao_de_variaveis_exp_loop",
  "declaracao_de_variaveis_virg_loop", "declaracao_de_prototipos",
  "parametros", "parametros_exp_loop", "parametros_virg_loop", "tipo",
  "bloco", "comandos", "comandos_loop", "lista_de_comandos",
  "lista_de_comandos_jump_exp_1", "lista_de_comandos_jump_exp_2",
  "lista_de_comandos_jump_exp_3", "expressao", "expressao_de_atribuicao",
  "expressao_condicional", "expressao_or_logico", "expressao_and_logico",
  "expressao_or", "expressao_xor", "expressao_and",
  "expressao_de_igualdade", "expressao_relacional", "expressao_shift",
  "expressao_aditiva", "expressao_multiplicativa", "expressao_cast",
  "expressao_unaria", "expressao_pos_fixa", "expressao_pos_fixa_loop",
  "expressao_primaria", "numero", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-202)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,  -202,  -202,  -202,   -32,    44,     6,     6,  -202,  -202,
      42,    16,  -202,  -202,     1,     8,  -202,    22,   465,  -202,
    -202,    -7,   465,   465,   465,   489,   489,   465,   465,   465,
     207,  -202,  -202,  -202,  -202,  -202,  -202,    34,  -202,    13,
     -23,    54,    64,    69,    74,    86,    52,   110,   150,   123,
    -202,    97,    17,  -202,  -202,    18,   465,    28,   -11,  -202,
    -202,  -202,  -202,   465,  -202,  -202,  -202,  -202,  -202,    42,
      73,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   465,
     465,   465,   465,   465,  -202,  -202,   277,   465,  -202,    42,
     -19,   465,    42,    98,  -202,   159,    99,  -202,  -202,  -202,
    -202,    54,   148,    64,    69,    74,    86,    52,    52,   110,
     110,   110,   110,   150,   150,   123,   123,  -202,  -202,  -202,
    -202,  -202,   117,    20,    96,   127,   122,   129,  -202,   302,
     137,   144,   149,   162,  -202,   231,   169,   187,   189,  -202,
     159,    42,  -202,   182,   231,   154,   465,   465,   465,   200,
    -202,   157,  -202,   205,   127,  -202,   156,   240,   465,   348,
     465,   193,   139,   197,   465,  -202,   203,  -202,  -202,   231,
    -202,  -202,  -202,  -202,  -202,   465,   218,  -202,    31,  -202,
     217,    79,   394,  -202,   160,    81,  -202,    83,   220,    87,
     127,  -202,    23,   155,   224,   465,  -202,   465,   137,   440,
    -202,   180,   394,   137,   465,   229,   248,   232,   157,    42,
    -202,   122,    88,  -202,   137,  -202,    89,   440,  -202,   261,
      95,  -202,   222,  -202,  -202,   223,  -202,   235,  -202,   137,
    -202,   137,   239,   236,   157,  -202,  -202,  -202,  -202,   241,
     218,  -202,  -202
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    30,    28,    29,     0,     0,     7,     7,     9,    10,
       5,     0,     1,     6,     0,     0,     4,     0,     0,     2,
       3,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   115,   116,   117,   112,   113,     8,    55,    57,
      61,    63,    65,    67,    69,    71,    73,    76,    81,    84,
      87,    91,    93,   102,   111,     0,     0,    20,     0,    98,
      91,    99,    97,     0,    94,    95,    96,   101,   100,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   104,   105,     0,     0,    22,     5,
       0,     0,     5,     0,    21,     0,     0,   114,    56,    59,
      60,    64,     0,    66,    68,    70,    72,    74,    75,    77,
      78,    79,    80,    83,    82,    85,    86,    88,    89,    90,
      58,   106,   109,     0,     0,    17,    20,     0,    15,     0,
       0,     0,     0,     0,    47,     0,     0,     0,     0,    11,
       0,     5,    48,     0,    34,     0,     0,     0,     0,     0,
     103,    25,    16,     0,    17,    44,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,    13,    32,    34,
      46,    92,    62,   108,   107,     0,    27,    14,    20,    45,
       0,     0,     0,    39,     0,     0,    31,     0,     0,     0,
      17,    33,     0,     0,     0,     0,    19,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,    25,     5,
      23,    20,     0,    38,     0,    52,     0,     0,    49,    36,
       0,    40,     0,    43,    24,     0,    18,     0,    54,     0,
      51,     0,     0,     0,    25,    35,    53,    37,    41,     0,
      27,    42,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,   287,   -66,   291,  -202,  -202,   153,   -89,  -134,  -129,
    -202,  -202,  -201,    49,   -28,   -84,   163,   126,  -119,  -202,
     100,    80,   -18,   -67,   161,  -202,   237,   233,   238,   250,
     234,   158,    11,   142,   152,    -9,    24,  -202,  -202,  -202,
    -202
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    13,    17,    14,     6,     7,   149,     8,    57,   103,
       9,    58,   186,   204,    10,   152,   153,   178,   154,   193,
     210,   225,   155,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,   159,    53,
      54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,   162,    69,   106,   108,   109,   110,   163,    74,     1,
       2,     3,    70,    59,    61,    62,   150,   234,    66,    67,
      68,     1,     2,     3,    11,    71,   130,    99,    75,   132,
     188,   135,   104,   134,   136,   179,   137,   105,   100,    55,
      94,    95,    56,   250,    12,    70,    60,    60,    60,    64,
      65,    60,    60,    60,    72,    73,   167,   112,     4,   206,
     179,   150,    16,    96,    71,    98,    97,    71,   101,    19,
     160,   205,   102,   218,    18,   102,    20,   151,    71,   133,
      21,   127,   128,   129,    76,   176,    82,    83,    84,    85,
      77,   183,   236,   119,   120,   121,   122,    78,    60,    79,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    71,    80,    81,
     107,   166,   151,    71,   223,    71,   208,   214,   213,   229,
     215,    71,    71,    71,   217,   237,   239,    93,   221,    71,
     238,   138,   242,    90,    91,    92,   156,   181,    86,    87,
     191,   194,   195,   235,   161,   246,   199,   247,     1,     2,
       3,   158,     1,     2,     3,   139,   102,   202,    88,    89,
     140,   141,   142,   143,   211,   219,    56,    22,    23,    24,
      60,    60,    25,    26,    27,   145,    28,   164,    29,   222,
     168,   226,    71,   157,   211,   169,   230,   180,    71,   189,
      71,   197,   144,   212,    71,    30,   185,   145,   170,   226,
       1,     2,     3,   146,   147,   172,   148,    31,    32,    33,
      34,    35,    36,   227,    71,    22,    23,    24,   123,   124,
      25,    26,    27,   173,    28,   174,    29,   139,   117,   118,
     125,   126,   140,   141,   142,   143,   177,   184,   187,    22,
      23,    24,   190,    30,    25,    26,    27,   196,    28,   198,
      29,   200,   203,   207,   216,    31,    32,    33,    34,    35,
      36,   220,   231,   232,   144,   233,   241,    30,   245,   145,
     243,   244,   248,   249,   251,   146,   147,     5,   148,    31,
      32,    33,    34,    35,    36,    22,    23,    24,    15,   252,
      25,    26,    27,   175,    28,   201,    29,   240,   171,   113,
       0,   111,   228,   116,     0,   114,     0,     0,   182,     0,
      22,    23,    24,    30,   131,    25,    26,    27,   115,    28,
       0,    29,     0,     0,     0,    31,    32,    33,    34,    35,
      36,     0,     0,     0,     0,   165,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,    35,    36,    22,    23,    24,     0,
       0,    25,    26,    27,     0,    28,     0,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
      35,    36,    22,    23,    24,     0,     0,    25,    26,    27,
       0,    28,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   209,     0,     0,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,    34,    35,    36,    22,    23,
      24,     0,     0,    25,    26,    27,     0,    28,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,    24,    30,   224,    25,    26,
      27,     0,    28,     0,    29,     0,     0,     0,    31,    32,
      33,    34,    35,    36,     0,     0,     0,    22,    23,    24,
       0,    30,    25,    26,    27,     0,    28,     0,    29,     0,
       0,     0,     0,    31,    32,    33,    34,    35,    36,     0,
       0,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    32,    33,
      34,    35,    36
};

static const yytype_int16 yycheck[] =
{
      18,   135,    30,    69,    71,    72,    73,   136,    31,     3,
       4,     5,    30,    22,    23,    24,   105,   218,    27,    28,
      29,     3,     4,     5,    56,    44,    93,    55,    51,    96,
     164,    50,    43,    99,   101,   154,   102,    48,    56,    46,
      23,    24,    49,   244,     0,    63,    22,    23,    24,    25,
      26,    27,    28,    29,    41,    42,   140,    75,    52,   188,
     179,   150,    20,    46,    44,    47,    49,    44,    40,    68,
      50,    40,    44,    50,    58,    44,    68,   105,    44,    97,
      58,    90,    91,    92,    30,   151,    34,    35,    36,    37,
      26,   158,   221,    82,    83,    84,    85,    28,    74,    25,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    44,    32,    33,
      47,   139,   150,    44,   208,    44,    47,    44,    47,   213,
      47,    44,    44,    44,    47,    47,    47,    40,   205,    44,
     224,    43,    47,    20,    21,    22,    47,   156,    38,    39,
     168,   169,   170,   219,    58,   239,   174,   241,     3,     4,
       5,    44,     3,     4,     5,     6,    44,   185,    18,    19,
      11,    12,    13,    14,   192,   203,    49,    18,    19,    20,
     156,   157,    23,    24,    25,    48,    27,    58,    29,   207,
      46,   209,    44,    45,   212,    46,   214,    43,    44,    43,
      44,    62,    43,    43,    44,    46,    49,    48,    46,   227,
       3,     4,     5,    54,    55,    46,    57,    58,    59,    60,
      61,    62,    63,    43,    44,    18,    19,    20,    86,    87,
      23,    24,    25,    46,    27,    46,    29,     6,    80,    81,
      88,    89,    11,    12,    13,    14,    64,    47,    43,    18,
      19,    20,    12,    46,    23,    24,    25,    64,    27,    62,
      29,    58,    44,    46,    44,    58,    59,    60,    61,    62,
      63,    47,    43,    25,    43,    43,    15,    46,    43,    48,
      58,    58,    43,    47,    43,    54,    55,     0,    57,    58,
      59,    60,    61,    62,    63,    18,    19,    20,     7,   250,
      23,    24,    25,   150,    27,   179,    29,   227,   145,    76,
      -1,    74,   212,    79,    -1,    77,    -1,    -1,   157,    -1,
      18,    19,    20,    46,    47,    23,    24,    25,    78,    27,
      -1,    29,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    62,    63,    18,    19,    20,    -1,
      -1,    23,    24,    25,    -1,    27,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    18,    19,    20,    -1,    -1,    23,    24,    25,
      -1,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    18,    19,
      20,    -1,    -1,    23,    24,    25,    -1,    27,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19,    20,    46,    47,    23,    24,
      25,    -1,    27,    -1,    29,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    18,    19,    20,
      -1,    46,    23,    24,    25,    -1,    27,    -1,    29,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      61,    62,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    52,    70,    73,    74,    76,    79,
      83,    56,     0,    70,    72,    72,    20,    71,    58,    68,
      68,    58,    18,    19,    20,    23,    24,    25,    27,    29,
      46,    58,    59,    60,    61,    62,    63,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   108,   109,    46,    49,    77,    80,   104,
     105,   104,   104,    46,   105,   105,   104,   104,   104,    83,
      91,    44,    41,    42,    31,    51,    30,    26,    28,    25,
      32,    33,    34,    35,    36,    37,    38,    39,    18,    19,
      20,    21,    22,    40,    23,    24,    46,    49,    47,    83,
      91,    40,    44,    78,    43,    48,    71,    47,    92,    92,
      92,    95,    91,    96,    97,    98,    99,   100,   100,   101,
     101,   101,   101,   102,   102,   103,   103,   104,   104,   104,
      92,    47,    92,    91,    71,    50,    92,    71,    43,     6,
      11,    12,    13,    14,    43,    48,    54,    55,    57,    75,
      76,    83,    84,    85,    87,    91,    47,    45,    44,   107,
      50,    58,    77,    78,    58,    43,    91,    84,    46,    46,
      46,    85,    46,    46,    46,    75,    71,    64,    86,    87,
      43,   104,    93,    92,    47,    49,    81,    43,    77,    43,
      12,    91,    43,    88,    91,    91,    64,    62,    62,    91,
      58,    86,    91,    44,    82,    40,    78,    46,    47,    43,
      89,    91,    43,    47,    44,    47,    44,    47,    50,    83,
      47,    92,    91,    84,    47,    90,    91,    43,    89,    84,
      91,    43,    25,    43,    81,    71,    78,    47,    84,    47,
      90,    15,    47,    58,    58,    43,    84,    84,    43,    47,
      81,    43,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      73,    74,    75,    75,    76,    76,    77,    77,    78,    78,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    84,    85,    86,    86,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,    99,   100,   100,   100,   100,
     100,   101,   101,   101,   102,   102,   102,   103,   103,   103,
     103,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   106,   106,   106,   106,   106,   106,   107,   107,
     108,   108,   108,   108,   108,   109,   109,   109
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     0,     4,     1,
       1,     6,     2,     2,     8,     6,     4,     0,     7,     5,
       0,     5,     2,     7,     4,     0,     6,     0,     1,     1,
       1,     3,     2,     2,     0,     7,     5,     7,     5,     3,
       5,     7,     8,     5,     2,     3,     2,     1,     1,     3,
       2,     3,     2,     3,     2,     1,     3,     1,     3,     3,
       3,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     5,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     4,     2,     2,     3,     5,     2,     0,
       1,     1,     1,     1,     3,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: declaracoes programa_loop END_OF_FILE  */
#line 96 "sintatico.y"
                                                 { return 0; }
#line 1432 "sintatico.tab.c"
    break;

  case 3: /* programa: funcao programa_loop END_OF_FILE  */
#line 97 "sintatico.y"
                                                 { return 0; }
#line 1438 "sintatico.tab.c"
    break;


#line 1442 "sintatico.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 291 "sintatico.y"


void get_line_content(char buffer[1024], int line_number) {
    fseek(stdin, 0, SEEK_SET);

    int i = 0;
    for (i; i < line_number; i++) {
        if(fgets(buffer, 1024, stdin) == NULL){
            buffer[0] = '\0';
        }
    }

}

void yyerror(char *s){

    if(yychar == LONG_IDENTIFIER){
        printf("%serror:lexical:%i:%i: identifier too long", nextline, yylineno, yycolno);
    }
    else if(yychar == UNKNOWN_CHARACTER){
        printf("%serror:lexical:%i:%i: %s", nextline, yylineno, yycolno, yytext);
    }
    else if(yychar == UNTERMINATED_COMMENT){
        printf("%serror:lexical:%i:%i: unterminated comment", nextline, comment_start_line, comment_start_col);
    }
    else if(yychar == END_OF_FILE){
        printf("%serror:syntax:%i:%i: expected declaration or statement at end of input\n", nextline, last_token_line, last_token_col);
        char line_buffer[1024];

        get_line_content(line_buffer, last_token_line);
        int last_index = strlen(line_buffer) - 1;
        if (line_buffer[last_index] == '\n') {
            line_buffer[last_index] = '\0';
        }
        
        printf("%s\n", line_buffer);

        int i;
        for(i = 0; i < last_token_col - 1; i++){
            printf(" ");
        }
        printf("^");
    }
    else{
        printf("%serror:syntax:%i:%i: %s\n", nextline, yylineno, yycolno - yyleng, yytext);
        char line_buffer[1024];

        get_line_content(line_buffer, yylineno);
        printf("%s", line_buffer);

        int i;
        for(i = 0; i < yycolno - yyleng - 1; i++){
            printf(" ");
        }
        printf("^");
    }

    exit(1);
}

int main(int argc, char** argv){
    yyparse();
    

    printf("%sSUCCESSFUL COMPILATION.", nextline);

    return 0;
}
