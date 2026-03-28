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
#line 1 "socialstory_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "socialstory_tokens.h"

#ifndef HAVE_STRDUP
static char* sss_strdup(const char* s) {
    size_t n = strlen(s) + 1;
    char* p = (char*)malloc(n);
    if (!p) {
        fprintf(stderr, "❌ Memory allocation failed in strdup fallback\n");
        exit(1);
    }
    memcpy(p, s, n);
    return p;
}
#define strdup sss_strdup
#endif

/* ========================================
 * FORWARD DECLARATIONS
 * ======================================== */
void yyerror(const char *s);
int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern int error_count;
extern char* yytext;

/* Output file for structured output */
FILE* output_file = NULL;

/* ========================================
 * OPERATOR TYPE DEFINITIONS FOR TAC
 * ======================================== */
#define OP_ADD 0
#define OP_SUB 1
#define OP_MUL 2
#define OP_DIV 3
#define OP_MOD 4

#define CMP_GT 0
#define CMP_LT 1
#define CMP_EQ 2
#define CMP_NEQ 3
#define CMP_GTE 4
#define CMP_LTE 5

/* ========================================
 * AST NODE TYPES
 * ======================================== */
typedef enum {
    AST_PROGRAM,
    AST_ACCOUNT_CREATE,
    AST_ACCOUNT_INIT,
    AST_ACCOUNT_UPDATE,
    AST_STORY_POST,
    AST_CONDITIONAL,
    AST_LOOP,
    AST_LOOP_INCREMENT,
    AST_LOOP_DECREMENT,
    AST_LOOP_RANGE,
    AST_LOOP_COLLECTION,
    AST_LOOP_TRENDING,
    AST_FUNCTION_DEF,
    AST_FUNCTION_CALL,
    AST_BUILTIN_CALL,
    AST_RETURN,
    AST_BREAK,
    AST_CONTINUE,
    AST_ANNOUNCE,
    AST_DISPLAY,
    AST_ASK_FOR,
    AST_BINARY_OP,
    AST_COMPARISON,
    AST_LOGICAL_OP,
    AST_UNARY_OP,
    AST_LITERAL_INT,
    AST_LITERAL_FLOAT,
    AST_LITERAL_STRING,
    AST_LITERAL_BOOL,
    AST_IDENTIFIER,
    AST_METRIC,
    AST_ACCOUNT_REF,
    AST_STRING_OP,
    AST_FEED_DECLARE,
    AST_FEED_SET,
    AST_FEED_GET,
    AST_FEED_LENGTH,
    AST_FEED_DISPLAY
} ASTNodeType;

/* ========================================
 * AST NODE STRUCTURE
 * ======================================== */
typedef struct ASTNode {
    ASTNodeType type;
    
    /* Value holders */
    int ival;
    int ival2;
    int step;
    float fval;
    char* sval;
    char* sval2;
    
    /* Node connections */
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* condition;
    struct ASTNode* body;
    struct ASTNode* else_body;
    struct ASTNode* next;
    struct ASTNode* param;
    
    /* Additional info */
    int line_number;
} ASTNode;

/* ========================================
 * SYMBOL TABLE STRUCTURE
 * ======================================== */
typedef struct SymbolEntry {
    char* name;
    enum { SYM_ACCOUNT, SYM_VARIABLE, SYM_FUNCTION } type;
    
    /* Account data */
    int likes;
    int followers;
    int views;
    int comments;
    int shares;
    int posts;
    int stories;
    float engagement_rate;
    float reach;
    float growth_rate;
    int is_viral;
    int is_trending;
    
    /* Function data */
    struct ASTNode* function_body;
    struct ASTNode* function_params;
    
    struct SymbolEntry* next;
} SymbolEntry;

/* ========================================
 * GLOBAL VARIABLES
 * ======================================== */
ASTNode* ast_root = NULL;
SymbolEntry* symbol_table = NULL;
int semantic_errors = 0;
int loop_break_flag = 0;
int loop_continue_flag = 0;

/* ========================================
 * INCLUDE MODULAR COMPONENTS
 * Each header file contains a specific functionality
 * This makes code easier to understand and maintain
 * ======================================== */
#include "ast_functions.h"      /* AST creation and manipulation */
#include "symbol_table.h"       /* Symbol table management */
#include "statistics.h"         /* AST and symbol table statistics */
#include "tac_generator.h"      /* Three-Address Code generation */
#include "optimizer.h"          /* Code optimization passes */
#include "interpreter.h"        /* Program execution */


#line 243 "socialstory_parser.tab.c"

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

#include "socialstory_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_GO_LIVE = 3,                  /* T_GO_LIVE  */
  YYSYMBOL_T_END_LIVE = 4,                 /* T_END_LIVE  */
  YYSYMBOL_T_THE_ACCOUNT = 5,              /* T_THE_ACCOUNT  */
  YYSYMBOL_T_WAS_CREATED = 6,              /* T_WAS_CREATED  */
  YYSYMBOL_T_THE_POST = 7,                 /* T_THE_POST  */
  YYSYMBOL_T_THE_CAPTION = 8,              /* T_THE_CAPTION  */
  YYSYMBOL_T_THE_FOLLOWER = 9,             /* T_THE_FOLLOWER  */
  YYSYMBOL_T_THE_STORY = 10,               /* T_THE_STORY  */
  YYSYMBOL_T_POSTED = 11,                  /* T_POSTED  */
  YYSYMBOL_T_ABOUT = 12,                   /* T_ABOUT  */
  YYSYMBOL_T_THAT_HAD = 13,                /* T_THAT_HAD  */
  YYSYMBOL_T_ANOTHER = 14,                 /* T_ANOTHER  */
  YYSYMBOL_T_STARTED_WITH = 15,            /* T_STARTED_WITH  */
  YYSYMBOL_T_BEGAN_AT = 16,                /* T_BEGAN_AT  */
  YYSYMBOL_T_NOW_HAS = 17,                 /* T_NOW_HAS  */
  YYSYMBOL_T_READS = 18,                   /* T_READS  */
  YYSYMBOL_T_IS_VIRAL = 19,                /* T_IS_VIRAL  */
  YYSYMBOL_T_IS_TRENDING = 20,             /* T_IS_TRENDING  */
  YYSYMBOL_T_GAINED = 21,                  /* T_GAINED  */
  YYSYMBOL_T_LOST = 22,                    /* T_LOST  */
  YYSYMBOL_T_ADDED = 23,                   /* T_ADDED  */
  YYSYMBOL_T_REMOVED = 24,                 /* T_REMOVED  */
  YYSYMBOL_T_INCREASED_BY = 25,            /* T_INCREASED_BY  */
  YYSYMBOL_T_DECREASED_BY = 26,            /* T_DECREASED_BY  */
  YYSYMBOL_T_WAS_UPDATED_TO = 27,          /* T_WAS_UPDATED_TO  */
  YYSYMBOL_T_BECAME = 28,                  /* T_BECAME  */
  YYSYMBOL_T_MULTIPLIED_BY = 29,           /* T_MULTIPLIED_BY  */
  YYSYMBOL_T_DIVIDED_BY = 30,              /* T_DIVIDED_BY  */
  YYSYMBOL_T_PLUS = 31,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 32,                   /* T_MINUS  */
  YYSYMBOL_T_TIMES = 33,                   /* T_TIMES  */
  YYSYMBOL_T_MULTIPLY = 34,                /* T_MULTIPLY  */
  YYSYMBOL_T_DIVIDED_EVENLY_BY = 35,       /* T_DIVIDED_EVENLY_BY  */
  YYSYMBOL_T_DIVIDE = 36,                  /* T_DIVIDE  */
  YYSYMBOL_T_MODULO = 37,                  /* T_MODULO  */
  YYSYMBOL_T_WITH = 38,                    /* T_WITH  */
  YYSYMBOL_T_AND_THEN = 39,                /* T_AND_THEN  */
  YYSYMBOL_T_FOR = 40,                     /* T_FOR  */
  YYSYMBOL_T_THE_FEED = 41,                /* T_THE_FEED  */
  YYSYMBOL_T_CONTAINS = 42,                /* T_CONTAINS  */
  YYSYMBOL_T_AT_INDEX = 43,                /* T_AT_INDEX  */
  YYSYMBOL_T_LIKES = 44,                   /* T_LIKES  */
  YYSYMBOL_T_FOLLOWERS = 45,               /* T_FOLLOWERS  */
  YYSYMBOL_T_VIEWS = 46,                   /* T_VIEWS  */
  YYSYMBOL_T_COMMENTS = 47,                /* T_COMMENTS  */
  YYSYMBOL_T_SHARES = 48,                  /* T_SHARES  */
  YYSYMBOL_T_POSTS = 49,                   /* T_POSTS  */
  YYSYMBOL_T_STORIES = 50,                 /* T_STORIES  */
  YYSYMBOL_T_ENGAGEMENT_RATE = 51,         /* T_ENGAGEMENT_RATE  */
  YYSYMBOL_T_REACH = 52,                   /* T_REACH  */
  YYSYMBOL_T_GROWTH_RATE = 53,             /* T_GROWTH_RATE  */
  YYSYMBOL_T_WHEN = 54,                    /* T_WHEN  */
  YYSYMBOL_T_OTHERWISE_IF = 55,            /* T_OTHERWISE_IF  */
  YYSYMBOL_T_OTHERWISE = 56,               /* T_OTHERWISE  */
  YYSYMBOL_T_WENT_VIRAL = 57,              /* T_WENT_VIRAL  */
  YYSYMBOL_T_REACHED = 58,                 /* T_REACHED  */
  YYSYMBOL_T_EXCEEDED = 59,                /* T_EXCEEDED  */
  YYSYMBOL_T_DROPPED_BELOW = 60,           /* T_DROPPED_BELOW  */
  YYSYMBOL_T_STAYED_AT = 61,               /* T_STAYED_AT  */
  YYSYMBOL_T_MORE_THAN = 62,               /* T_MORE_THAN  */
  YYSYMBOL_T_LESS_THAN = 63,               /* T_LESS_THAN  */
  YYSYMBOL_T_EXACTLY = 64,                 /* T_EXACTLY  */
  YYSYMBOL_T_AT_LEAST = 65,                /* T_AT_LEAST  */
  YYSYMBOL_T_AT_MOST = 66,                 /* T_AT_MOST  */
  YYSYMBOL_T_DIFFERENT_FROM = 67,          /* T_DIFFERENT_FROM  */
  YYSYMBOL_T_EQUAL_TO = 68,                /* T_EQUAL_TO  */
  YYSYMBOL_T_NOT_EQUAL_TO = 69,            /* T_NOT_EQUAL_TO  */
  YYSYMBOL_T_EVERY_DAY_FOR = 70,           /* T_EVERY_DAY_FOR  */
  YYSYMBOL_T_EVERY = 71,                   /* T_EVERY  */
  YYSYMBOL_T_DAYS = 72,                    /* T_DAYS  */
  YYSYMBOL_T_INCREMENTING_BY = 73,         /* T_INCREMENTING_BY  */
  YYSYMBOL_T_DECREMENTING_BY = 74,         /* T_DECREMENTING_BY  */
  YYSYMBOL_T_FOR_EACH = 75,                /* T_FOR_EACH  */
  YYSYMBOL_T_POST_IN = 76,                 /* T_POST_IN  */
  YYSYMBOL_T_STORY_IN = 77,                /* T_STORY_IN  */
  YYSYMBOL_T_FOLLOWER_FROM = 78,           /* T_FOLLOWER_FROM  */
  YYSYMBOL_T_TO = 79,                      /* T_TO  */
  YYSYMBOL_T_TRENDING_LOOP = 80,           /* T_TRENDING_LOOP  */
  YYSYMBOL_T_UNTIL = 81,                   /* T_UNTIL  */
  YYSYMBOL_T_STOP_THE_STORY = 82,          /* T_STOP_THE_STORY  */
  YYSYMBOL_T_SKIP_THIS_POST = 83,          /* T_SKIP_THIS_POST  */
  YYSYMBOL_T_THE_STORY_OF = 84,            /* T_THE_STORY_OF  */
  YYSYMBOL_T_BEGINS_WITH = 85,             /* T_BEGINS_WITH  */
  YYSYMBOL_T_TELL_BACK = 86,               /* T_TELL_BACK  */
  YYSYMBOL_T_THE_STORY_ENDS = 87,          /* T_THE_STORY_ENDS  */
  YYSYMBOL_T_TELL = 88,                    /* T_TELL  */
  YYSYMBOL_T_ANNOUNCE = 89,                /* T_ANNOUNCE  */
  YYSYMBOL_T_ASK_FOR = 90,                 /* T_ASK_FOR  */
  YYSYMBOL_T_DISPLAY = 91,                 /* T_DISPLAY  */
  YYSYMBOL_T_CALCULATE_VIRALITY = 92,      /* T_CALCULATE_VIRALITY  */
  YYSYMBOL_T_CALCULATE_ENGAGEMENT = 93,    /* T_CALCULATE_ENGAGEMENT  */
  YYSYMBOL_T_FIND_TOP_POST = 94,           /* T_FIND_TOP_POST  */
  YYSYMBOL_T_FIND_HIGHEST_REACH = 95,      /* T_FIND_HIGHEST_REACH  */
  YYSYMBOL_T_FIND_TOTAL_REACH = 96,        /* T_FIND_TOTAL_REACH  */
  YYSYMBOL_T_COUNT_TOTAL_ENGAGEMENT = 97,  /* T_COUNT_TOTAL_ENGAGEMENT  */
  YYSYMBOL_T_CHECK_IF_TRENDING = 98,       /* T_CHECK_IF_TRENDING  */
  YYSYMBOL_T_ANALYZE_GROWTH = 99,          /* T_ANALYZE_GROWTH  */
  YYSYMBOL_T_FIND_MAX_VIRAL_ACCOUNT = 100, /* T_FIND_MAX_VIRAL_ACCOUNT  */
  YYSYMBOL_T_REVERSE_THE_CAPTION = 101,    /* T_REVERSE_THE_CAPTION  */
  YYSYMBOL_T_DETECT_SPAM = 102,            /* T_DETECT_SPAM  */
  YYSYMBOL_T_CLAMP_ENGAGEMENT = 103,       /* T_CLAMP_ENGAGEMENT  */
  YYSYMBOL_T_BETWEEN = 104,                /* T_BETWEEN  */
  YYSYMBOL_T_REVERSE_GROWTH = 105,         /* T_REVERSE_GROWTH  */
  YYSYMBOL_T_ALSO = 106,                   /* T_ALSO  */
  YYSYMBOL_T_EITHER = 107,                 /* T_EITHER  */
  YYSYMBOL_T_OPPOSITE = 108,               /* T_OPPOSITE  */
  YYSYMBOL_T_LPAREN = 109,                 /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 110,                 /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 111,                 /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 112,                 /* T_RBRACE  */
  YYSYMBOL_T_LBRACKET = 113,               /* T_LBRACKET  */
  YYSYMBOL_T_RBRACKET = 114,               /* T_RBRACKET  */
  YYSYMBOL_T_COMMA = 115,                  /* T_COMMA  */
  YYSYMBOL_T_DOT = 116,                    /* T_DOT  */
  YYSYMBOL_T_COLON = 117,                  /* T_COLON  */
  YYSYMBOL_T_NUMBER = 118,                 /* T_NUMBER  */
  YYSYMBOL_T_DECIMAL = 119,                /* T_DECIMAL  */
  YYSYMBOL_T_TEXT = 120,                   /* T_TEXT  */
  YYSYMBOL_T_ID = 121,                     /* T_ID  */
  YYSYMBOL_T_CHAR = 122,                   /* T_CHAR  */
  YYSYMBOL_T_TRUE_STORY = 123,             /* T_TRUE_STORY  */
  YYSYMBOL_T_FALSE_ALARM = 124,            /* T_FALSE_ALARM  */
  YYSYMBOL_LOWER_THAN_OTHERWISE = 125,     /* LOWER_THAN_OTHERWISE  */
  YYSYMBOL_YYACCEPT = 126,                 /* $accept  */
  YYSYMBOL_program = 127,                  /* program  */
  YYSYMBOL_statements = 128,               /* statements  */
  YYSYMBOL_statement = 129,                /* statement  */
  YYSYMBOL_account_create = 130,           /* account_create  */
  YYSYMBOL_account_init = 131,             /* account_init  */
  YYSYMBOL_account_update = 132,           /* account_update  */
  YYSYMBOL_story_post = 133,               /* story_post  */
  YYSYMBOL_conditional = 134,              /* conditional  */
  YYSYMBOL_optional_else = 135,            /* optional_else  */
  YYSYMBOL_else_if_chain = 136,            /* else_if_chain  */
  YYSYMBOL_comparison = 137,               /* comparison  */
  YYSYMBOL_account_metric_ref = 138,       /* account_metric_ref  */
  YYSYMBOL_loop = 139,                     /* loop  */
  YYSYMBOL_loop_control = 140,             /* loop_control  */
  YYSYMBOL_function_def = 141,             /* function_def  */
  YYSYMBOL_param_list = 142,               /* param_list  */
  YYSYMBOL_function_call = 143,            /* function_call  */
  YYSYMBOL_arg_list = 144,                 /* arg_list  */
  YYSYMBOL_builtin_call = 145,             /* builtin_call  */
  YYSYMBOL_io_statement = 146,             /* io_statement  */
  YYSYMBOL_account_update_ext = 147,       /* account_update_ext  */
  YYSYMBOL_feed_statement = 148,           /* feed_statement  */
  YYSYMBOL_expression = 149,               /* expression  */
  YYSYMBOL_term = 150,                     /* term  */
  YYSYMBOL_factor = 151,                   /* factor  */
  YYSYMBOL_metric = 152,                   /* metric  */
  YYSYMBOL_literal = 153                   /* literal  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2352

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  126
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  438

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   380


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   254,   254,   261,   271,   282,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     309,   326,   335,   344,   353,   365,   375,   385,   395,   408,
     417,   429,   437,   450,   460,   474,   483,   484,   490,   494,
     506,   512,   518,   524,   530,   536,   542,   548,   554,   561,
     567,   573,   580,   586,   592,   598,   604,   610,   616,   622,
     628,   634,   640,   646,   654,   660,   670,   682,   691,   700,
     710,   720,   730,   735,   744,   752,   760,   770,   775,   782,
     789,   796,   802,   811,   816,   823,   830,   837,   844,   851,
     858,   864,   874,   882,   889,   896,   903,   910,   917,   924,
     932,   940,   949,   956,   965,   971,   977,   983,   992,   998,
    1005,  1013,  1026,  1035,  1044,  1054,  1064,  1074,  1084,  1091,
    1103,  1114,  1123,  1140,  1149,  1158,  1167,  1176,  1183,  1193,
    1194,  1200,  1209,  1210,  1216,  1222,  1228,  1234,  1240,  1249,
    1250,  1251,  1252,  1253,  1261,  1267,  1273,  1277,  1283,  1289,
    1295,  1301,  1307,  1313,  1319,  1325,  1331,  1340,  1345,  1350,
    1355,  1360
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
  "\"end of file\"", "error", "\"invalid token\"", "T_GO_LIVE",
  "T_END_LIVE", "T_THE_ACCOUNT", "T_WAS_CREATED", "T_THE_POST",
  "T_THE_CAPTION", "T_THE_FOLLOWER", "T_THE_STORY", "T_POSTED", "T_ABOUT",
  "T_THAT_HAD", "T_ANOTHER", "T_STARTED_WITH", "T_BEGAN_AT", "T_NOW_HAS",
  "T_READS", "T_IS_VIRAL", "T_IS_TRENDING", "T_GAINED", "T_LOST",
  "T_ADDED", "T_REMOVED", "T_INCREASED_BY", "T_DECREASED_BY",
  "T_WAS_UPDATED_TO", "T_BECAME", "T_MULTIPLIED_BY", "T_DIVIDED_BY",
  "T_PLUS", "T_MINUS", "T_TIMES", "T_MULTIPLY", "T_DIVIDED_EVENLY_BY",
  "T_DIVIDE", "T_MODULO", "T_WITH", "T_AND_THEN", "T_FOR", "T_THE_FEED",
  "T_CONTAINS", "T_AT_INDEX", "T_LIKES", "T_FOLLOWERS", "T_VIEWS",
  "T_COMMENTS", "T_SHARES", "T_POSTS", "T_STORIES", "T_ENGAGEMENT_RATE",
  "T_REACH", "T_GROWTH_RATE", "T_WHEN", "T_OTHERWISE_IF", "T_OTHERWISE",
  "T_WENT_VIRAL", "T_REACHED", "T_EXCEEDED", "T_DROPPED_BELOW",
  "T_STAYED_AT", "T_MORE_THAN", "T_LESS_THAN", "T_EXACTLY", "T_AT_LEAST",
  "T_AT_MOST", "T_DIFFERENT_FROM", "T_EQUAL_TO", "T_NOT_EQUAL_TO",
  "T_EVERY_DAY_FOR", "T_EVERY", "T_DAYS", "T_INCREMENTING_BY",
  "T_DECREMENTING_BY", "T_FOR_EACH", "T_POST_IN", "T_STORY_IN",
  "T_FOLLOWER_FROM", "T_TO", "T_TRENDING_LOOP", "T_UNTIL",
  "T_STOP_THE_STORY", "T_SKIP_THIS_POST", "T_THE_STORY_OF",
  "T_BEGINS_WITH", "T_TELL_BACK", "T_THE_STORY_ENDS", "T_TELL",
  "T_ANNOUNCE", "T_ASK_FOR", "T_DISPLAY", "T_CALCULATE_VIRALITY",
  "T_CALCULATE_ENGAGEMENT", "T_FIND_TOP_POST", "T_FIND_HIGHEST_REACH",
  "T_FIND_TOTAL_REACH", "T_COUNT_TOTAL_ENGAGEMENT", "T_CHECK_IF_TRENDING",
  "T_ANALYZE_GROWTH", "T_FIND_MAX_VIRAL_ACCOUNT", "T_REVERSE_THE_CAPTION",
  "T_DETECT_SPAM", "T_CLAMP_ENGAGEMENT", "T_BETWEEN", "T_REVERSE_GROWTH",
  "T_ALSO", "T_EITHER", "T_OPPOSITE", "T_LPAREN", "T_RPAREN", "T_LBRACE",
  "T_RBRACE", "T_LBRACKET", "T_RBRACKET", "T_COMMA", "T_DOT", "T_COLON",
  "T_NUMBER", "T_DECIMAL", "T_TEXT", "T_ID", "T_CHAR", "T_TRUE_STORY",
  "T_FALSE_ALARM", "LOWER_THAN_OTHERWISE", "$accept", "program",
  "statements", "statement", "account_create", "account_init",
  "account_update", "story_post", "conditional", "optional_else",
  "else_if_chain", "comparison", "account_metric_ref", "loop",
  "loop_control", "function_def", "param_list", "function_call",
  "arg_list", "builtin_call", "io_statement", "account_update_ext",
  "feed_statement", "expression", "term", "factor", "metric", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-332)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,   -81,    39,  2073,  -332,   -65,   -61,   -50,   -11,    69,
      31,   184,    -4,     5,     0,    16,    13,    44,    48,   155,
      53,   -12,    55,   -21,   -19,    97,    59,   139,   140,    66,
     -34,   -16,   -90,    75,    77,     1,   -22,  2176,  -332,  -332,
    -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,
    -332,  -332,  -332,  -332,   429,    41,    78,    92,   155,   100,
      37,  -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,
    -332,   155,   155,  -332,  -332,  -332,   142,  -332,  -332,   -79,
     629,   521,    27,  -332,    42,  -332,   141,   143,   171,   173,
      98,   155,  -332,  -332,   132,  -332,   -24,  -332,   -28,   105,
     108,   122,   -30,   123,    -3,   235,   120,   237,  -332,   131,
     145,  -332,   243,  -332,   257,   144,   146,  -332,   148,   147,
     227,   232,   272,  -332,   165,  -332,   167,   273,   166,   168,
     423,   170,   172,   155,   155,   155,   155,   176,   177,   436,
     526,   178,   179,   174,    52,    21,  2247,    76,   155,   -77,
     -15,  -332,   155,   155,   322,  -332,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   183,    54,   180,
     188,   210,   -41,   -99,  -332,   155,   155,  -332,  -332,  -332,
    -332,   155,  -332,  -332,  -332,   185,   190,   196,   193,  -332,
    -332,   194,   195,   207,   203,   209,  -332,   204,   212,   205,
    -332,  -332,   213,   142,   142,   142,   610,  -332,  -332,   610,
     610,   610,   610,   142,   142,   142,   610,   142,   610,   142,
     142,  -332,   216,   218,   155,   155,   425,  -332,  -332,   610,
     528,  -332,  -332,  -332,   107,   631,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,    27,    27,
     133,   133,   133,   133,   133,   133,   133,   133,  -332,  -332,
    -332,  -332,  -332,  -332,   133,   133,   133,   224,   220,   221,
    2247,  2247,   222,  2247,  2247,   -78,   230,   226,   -17,   234,
     610,  -332,   229,   231,   233,   238,   239,   240,   225,   244,
     245,   246,   248,    -9,   250,   251,   253,   254,   255,   256,
     258,   259,   261,   263,   267,   268,   269,   270,   271,   274,
    -332,  -332,   610,   610,  -332,  -332,   107,   734,   155,   262,
    -332,  -332,   107,  2247,   278,   280,   837,   940,   283,  1043,
    1146,  2247,   275,  2247,  -332,   155,   279,   282,  -332,  -332,
    -332,  -332,  -332,  -332,   241,  -332,  -332,  -332,  -332,   281,
    -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,  -332,
    -332,  -332,  -332,  -332,  -332,  -332,  -332,   284,   285,  -332,
     107,   -39,  2247,  -332,  1249,  2247,  2247,  -332,  -332,  2247,
    -332,   316,  1352,   292,  -332,  1455,  -332,  -332,  -332,   293,
     302,  -332,  -332,  -332,  2247,  1558,  -332,  1661,  1764,  1867,
     312,   342,   344,  -332,   320,  1970,  -332,  -332,  -332,  -332,
    -332,   321,   323,  -332,   107,  -332,  -332,  -332
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     3,     0,     0,     0,     0,     0,     0,
       0,   147,   148,   149,   150,   151,   155,   156,   153,   152,
     154,     0,     0,   157,   158,   159,   142,   160,   161,     0,
     140,     0,   129,   132,   141,   139,     0,     0,     0,     0,
       0,     0,    72,    73,     0,   140,     0,   141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,    95,     0,    94,     0,     0,     0,    90,     0,     0,
       0,     0,     0,   103,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    66,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,    81,   104,   109,
     108,     0,   111,   105,   106,     0,     0,     0,     0,    97,
      98,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       2,    20,     0,     0,     0,   157,     0,   119,   120,     0,
       0,     0,     0,     0,     0,   157,     0,   157,     0,     0,
       0,   118,     0,     0,     0,     0,     0,   144,   145,     0,
       0,   146,    64,    65,    36,     0,    62,    47,    48,    61,
      40,    41,    42,    45,    46,    60,    43,    44,   130,   131,
      52,    53,    54,    57,    58,    59,    55,    56,   135,   133,
     134,   137,   136,   138,    49,    50,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,     0,
       0,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,     0,     0,    35,   143,    36,     0,     0,     0,
      33,    38,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    79,     0,     0,     0,    85,    86,
      87,    93,    88,    89,     0,    92,   100,   101,   102,     0,
      30,    21,    23,    22,    24,    25,    26,    27,    28,   112,
     113,   114,   115,   116,   117,   121,   122,     0,     0,    34,
      36,     0,     0,    31,     0,     0,     0,   127,   128,     0,
      71,     0,     0,    78,    77,     0,    83,    80,   110,     0,
       0,   126,   125,    32,     0,     0,    67,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    37,    68,    69,    70,
      76,     0,     0,    29,    36,    75,    74,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -332,  -332,   -71,   -37,  -332,  -332,  -332,  -332,  -332,  -331,
    -332,   -68,    -2,  -332,  -332,  -332,     7,  -332,  -194,  -332,
    -332,  -332,  -332,   -18,     2,   -47,    20,  -332
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,    37,    38,    39,    40,    41,    42,    43,   340,
     341,    79,    95,    44,    45,    46,   296,    47,   297,    48,
      49,    50,    51,    81,    82,    83,    97,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     125,    96,   299,   149,   369,   389,   112,   168,   169,    80,
     195,   393,   294,   201,   168,   169,   168,   169,   122,   116,
     102,   105,   295,   192,   114,     1,   117,   152,   153,   152,
     153,    84,   154,   351,   250,     3,   244,   352,   245,     4,
     145,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    52,   168,   169,   150,    53,   141,   178,   142,   413,
     179,   180,   181,   182,   183,   152,   153,   152,   153,    80,
     293,    54,   414,    57,    58,   246,    88,    89,    90,   147,
     148,   196,   113,   255,   252,   253,   202,    56,   197,    80,
     106,    84,   194,   115,   123,   251,   151,    91,   355,   103,
     104,   242,   243,   437,   184,   185,   186,   370,    99,   100,
      55,    84,   226,   204,    86,   229,   230,   231,   232,   120,
     121,   236,   238,    87,   205,   247,   248,   288,   289,    92,
     249,   278,   279,   280,   281,   282,   283,   107,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
      80,    80,   270,   271,   272,   273,   274,   275,   276,   277,
      93,   406,   338,   339,   168,   169,   284,   285,   286,    94,
     268,   269,    84,    84,    98,   108,   101,   298,   298,   337,
     109,   110,   111,   300,   118,    59,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    60,   119,   143,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,   125,
     144,   146,   189,   187,   190,   188,   191,   193,   125,   346,
     347,   198,   349,   350,   199,    60,   332,   333,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,   200,   203,
     206,   207,   208,   314,   315,   316,   317,   209,   211,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   210,   212,   216,    72,   213,   217,   214,   215,   335,
     391,   218,   394,    73,    74,    75,    76,   219,    77,    78,
     402,   220,   405,   221,   223,   222,   227,   224,   228,   292,
     241,   290,    71,    72,   233,   234,   239,   240,   287,   291,
     125,   301,    73,    74,    75,    76,   303,    77,    78,   125,
     125,   302,   125,   125,   304,   305,   306,   307,   308,   309,
     357,   415,   310,     5,   417,   418,   312,     7,   419,     8,
       9,   311,   330,   313,   331,   343,    80,   298,   344,   345,
     348,   353,   354,   425,   356,   358,   364,   359,   424,   360,
       0,   409,   387,   388,   361,   362,   363,   125,    84,   404,
     365,   366,   367,    10,   368,   125,   371,   372,   125,   373,
     374,   375,   376,   392,   377,   378,    11,   379,   125,   380,
     125,   125,   125,   381,   382,   383,   384,   385,   125,   395,
     386,   396,    12,    13,   399,   407,   403,    14,   408,   410,
     411,   412,    15,   420,    16,    17,    18,   352,    19,   423,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     5,    36,   430,   431,
       7,   432,     8,     9,   254,   126,   433,   435,     0,   436,
     127,     0,     0,     0,   128,   129,   130,     0,   131,   132,
     133,   134,     0,     0,   135,   136,   137,   138,   139,   140,
       0,     0,     0,     0,    60,     0,    10,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    60,     0,    11,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       0,     0,     0,     0,     0,    12,    13,     0,     0,     0,
      14,     0,     0,     0,     0,    15,     0,    16,    17,    18,
       0,    19,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,     5,
      36,     0,    72,     7,     0,     8,     9,   334,     0,     0,
       0,   225,    74,    75,    76,    72,    77,    78,     0,     0,
       0,     0,   168,   169,   235,    74,    75,    76,     0,    77,
      78,     0,     0,     0,     0,     0,     0,    60,     0,    10,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       0,     0,    11,   170,   171,   172,   173,   174,   175,   176,
     177,     0,     0,     0,     0,     0,     0,     0,    12,    13,
       0,     0,     0,    14,     0,     0,     0,     0,    15,     0,
      16,    17,    18,     0,    19,     0,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     5,    36,     0,    72,     7,     0,     8,     9,
     336,   168,   169,     0,   237,    74,    75,    76,     0,    77,
      78,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,     0,
       0,    12,    13,     0,     0,     0,    14,     0,     0,     0,
       0,    15,     0,    16,    17,    18,     0,    19,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     5,    36,     0,     0,     7,
       0,     8,     9,   342,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,     0,     0,     0,    14,
       0,     0,     0,     0,    15,     0,    16,    17,    18,     0,
      19,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     5,    36,
       0,     0,     7,     0,     8,     9,   390,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,     0,
       0,     0,    14,     0,     0,     0,     0,    15,     0,    16,
      17,    18,     0,    19,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     5,    36,     0,     0,     7,     0,     8,     9,   397,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,     0,     0,     0,    14,     0,     0,     0,     0,
      15,     0,    16,    17,    18,     0,    19,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     5,    36,     0,     0,     7,     0,
       8,     9,   398,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,     0,     0,     0,    14,     0,
       0,     0,     0,    15,     0,    16,    17,    18,     0,    19,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     5,    36,     0,
       0,     7,     0,     8,     9,   400,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,     0,     0,
       0,    14,     0,     0,     0,     0,    15,     0,    16,    17,
      18,     0,    19,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       5,    36,     0,     0,     7,     0,     8,     9,   401,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      13,     0,     0,     0,    14,     0,     0,     0,     0,    15,
       0,    16,    17,    18,     0,    19,     0,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     5,    36,     0,     0,     7,     0,     8,
       9,   416,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,     0,     0,     0,    14,     0,     0,
       0,     0,    15,     0,    16,    17,    18,     0,    19,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     5,    36,     0,     0,
       7,     0,     8,     9,   421,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,     0,     0,     0,
      14,     0,     0,     0,     0,    15,     0,    16,    17,    18,
       0,    19,     0,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,     5,
      36,     0,     0,     7,     0,     8,     9,   422,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    13,
       0,     0,     0,    14,     0,     0,     0,     0,    15,     0,
      16,    17,    18,     0,    19,     0,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     5,    36,     0,     0,     7,     0,     8,     9,
     426,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,     0,     0,     0,    14,     0,     0,     0,
       0,    15,     0,    16,    17,    18,     0,    19,     0,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     5,    36,     0,     0,     7,
       0,     8,     9,   427,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,     0,     0,     0,    14,
       0,     0,     0,     0,    15,     0,    16,    17,    18,     0,
      19,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     5,    36,
       0,     0,     7,     0,     8,     9,   428,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,     0,
       0,     0,    14,     0,     0,     0,     0,    15,     0,    16,
      17,    18,     0,    19,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     5,    36,     0,     0,     7,     0,     8,     9,   429,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    13,     0,     0,     0,    14,     0,     0,     0,     0,
      15,     0,    16,    17,    18,     0,    19,     0,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     5,    36,     0,     6,     7,     0,
       8,     9,   434,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,     0,     0,     0,    14,     0,
       0,     0,     0,    15,     0,    16,    17,    18,     0,    19,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     5,    36,     0,
     124,     7,     0,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,     5,     0,
       0,    14,     7,     0,     8,     9,    15,     0,    16,    17,
      18,     0,    19,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,     0,     0,     0,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    12,    13,     0,
       0,     0,    14,     0,     0,     0,     0,    15,     0,    16,
      17,    18,     0,    19,     0,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     0,    36
};

static const yytype_int16 yycheck[] =
{
      37,    19,   196,    71,    13,   336,    40,    31,    32,    11,
      38,   342,   111,    43,    31,    32,    31,    32,    40,   109,
      41,    40,   121,    91,    40,     3,   116,   106,   107,   106,
     107,    11,   111,   111,   111,   116,    15,   115,    17,     0,
      58,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   116,    31,    32,    72,   116,    15,    30,    17,   390,
      33,    34,    35,    36,    37,   106,   107,   106,   107,    71,
     111,   121,   111,    42,    43,   146,    76,    77,    78,    42,
      43,   109,   116,   154,   152,   153,   116,    18,   116,    91,
     109,    71,   116,   109,   116,   110,    76,    81,   115,   120,
     121,    49,    50,   434,    62,    63,    64,   116,   120,   121,
     121,    91,   130,   116,   118,   133,   134,   135,   136,   118,
     119,   139,   140,   118,   104,    49,    50,    73,    74,   116,
     148,   178,   179,   180,   181,   182,   183,    40,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     152,   153,   170,   171,   172,   173,   174,   175,   176,   177,
     116,   355,    55,    56,    31,    32,   184,   185,   186,   121,
     168,   169,   152,   153,   121,   116,   121,   195,   196,   250,
      41,    41,   116,   201,   109,     1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    41,   120,   120,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,   246,
     118,   111,    41,    72,    41,    72,   118,    85,   255,   290,
     291,   116,   293,   294,   116,    41,   244,   245,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,   116,   116,
       5,   121,     5,   223,   224,   225,   226,   116,     5,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   116,     5,   116,   109,   121,    39,   121,   120,   249,
     338,    39,   343,   118,   119,   120,   121,     5,   123,   124,
     351,   116,   353,   116,   118,    12,   116,   119,   116,    79,
     116,   111,   108,   109,   118,   118,   118,   118,   115,   111,
     337,   116,   118,   119,   120,   121,   110,   123,   124,   346,
     347,   121,   349,   350,   121,   121,   121,   110,   115,   110,
     300,   392,   118,     1,   395,   396,   121,     5,   399,     7,
       8,   119,   116,   120,   116,   111,   338,   355,   118,   118,
     118,   111,   116,   414,   110,   116,   121,   116,    46,   116,
      -1,   110,   332,   333,   116,   116,   116,   394,   338,   352,
     116,   116,   116,    41,   116,   402,   116,   116,   405,   116,
     116,   116,   116,   111,   116,   116,    54,   116,   415,   116,
     417,   418,   419,   116,   116,   116,   116,   116,   425,   111,
     116,   111,    70,    71,   111,   116,   121,    75,   116,   118,
     116,   116,    80,    87,    82,    83,    84,   115,    86,   116,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     1,   105,   116,    87,
       5,    87,     7,     8,   112,     6,   116,   116,    -1,   116,
      11,    -1,    -1,    -1,    15,    16,    17,    -1,    19,    20,
      21,    22,    -1,    -1,    25,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    41,    -1,    41,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    41,    -1,    54,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     1,
     105,    -1,   109,     5,    -1,     7,     8,   112,    -1,    -1,
      -1,   118,   119,   120,   121,   109,   123,   124,    -1,    -1,
      -1,    -1,    31,    32,   118,   119,   120,   121,    -1,   123,
     124,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    41,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    54,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     1,   105,    -1,   109,     5,    -1,     7,     8,
     112,    31,    32,    -1,   118,   119,   120,   121,    -1,   123,
     124,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    70,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     1,   105,    -1,    -1,     5,
      -1,     7,     8,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     1,   105,
      -1,    -1,     5,    -1,     7,     8,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     1,   105,    -1,    -1,     5,    -1,     7,     8,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     1,   105,    -1,    -1,     5,    -1,
       7,     8,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     1,   105,    -1,
      -1,     5,    -1,     7,     8,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       1,   105,    -1,    -1,     5,    -1,     7,     8,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,     1,   105,    -1,    -1,     5,    -1,     7,
       8,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    80,    -1,    82,    83,    84,    -1,    86,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     1,   105,    -1,    -1,
       5,    -1,     7,     8,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     1,
     105,    -1,    -1,     5,    -1,     7,     8,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     1,   105,    -1,    -1,     5,    -1,     7,     8,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     1,   105,    -1,    -1,     5,
      -1,     7,     8,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     1,   105,
      -1,    -1,     5,    -1,     7,     8,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     1,   105,    -1,    -1,     5,    -1,     7,     8,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     1,   105,    -1,     4,     5,    -1,
       7,     8,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     1,   105,    -1,
       4,     5,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,     1,    -1,
      -1,    75,     5,    -1,     7,     8,    80,    -1,    82,    83,
      84,    -1,    86,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   127,   116,     0,     1,     4,     5,     7,     8,
      41,    54,    70,    71,    75,    80,    82,    83,    84,    86,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   105,   128,   129,   130,
     131,   132,   133,   134,   139,   140,   141,   143,   145,   146,
     147,   148,   116,   116,   121,   121,    18,    42,    43,     1,
      41,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,   108,   109,   118,   119,   120,   121,   123,   124,   137,
     138,   149,   150,   151,   152,   153,   118,   118,    76,    77,
      78,    81,   116,   116,   121,   138,   149,   152,   121,   120,
     121,   121,    41,   120,   121,    40,   109,    40,   116,    41,
      41,   116,    40,   116,    40,   109,   109,   116,   109,   120,
     118,   119,    40,   116,     4,   129,     6,    11,    15,    16,
      17,    19,    20,    21,    22,    25,    26,    27,    28,    29,
      30,    15,    17,   120,   118,   149,   111,    42,    43,   137,
     149,   152,   106,   107,   111,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    31,    32,
      62,    63,    64,    65,    66,    67,    68,    69,    30,    33,
      34,    35,    36,    37,    62,    63,    64,    72,    72,    41,
      41,   118,   137,    85,   116,    38,   109,   116,   116,   116,
     116,    43,   116,   116,   116,   152,     5,   121,     5,   116,
     116,     5,     5,   121,   121,   120,   116,    39,    39,     5,
     116,   116,    12,   118,   119,   118,   149,   116,   116,   149,
     149,   149,   149,   118,   118,   118,   149,   118,   149,   118,
     118,   116,    49,    50,    15,    17,   128,    49,    50,   149,
     111,   110,   137,   137,   112,   128,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   150,   150,
     149,   149,   149,   149,   149,   149,   149,   149,   151,   151,
     151,   151,   151,   151,   149,   149,   149,   115,    73,    74,
     111,   111,    79,   111,   111,   121,   142,   144,   149,   144,
     149,   116,   121,   110,   121,   121,   121,   110,   115,   110,
     118,   119,   121,   120,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     116,   116,   149,   149,   112,   152,   112,   128,    55,    56,
     135,   136,   112,   111,   118,   118,   128,   128,   118,   128,
     128,   111,   115,   111,   116,   115,   110,   152,   116,   116,
     116,   116,   116,   116,   121,   116,   116,   116,   116,    13,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   152,   152,   135,
     112,   137,   111,   135,   128,   111,   111,   112,   112,   111,
     112,   112,   128,   121,   142,   128,   144,   116,   116,   110,
     118,   116,   116,   135,   111,   128,   112,   128,   128,   128,
      87,   112,   112,   116,    46,   128,   112,   112,   112,   112,
     116,    87,    87,   116,   112,   116,   116,   135
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   126,   127,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     130,   131,   131,   131,   131,   132,   132,   132,   132,   133,
     133,   134,   134,   134,   134,   134,   135,   135,   135,   136,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   138,   139,   139,   139,
     139,   139,   140,   140,   141,   141,   141,   142,   142,   143,
     143,   143,   143,   144,   144,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   146,   146,   146,   146,   146,   146,
     146,   146,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   148,   148,   148,   148,   148,   148,   149,
     149,   149,   150,   150,   150,   150,   150,   150,   150,   151,
     151,   151,   151,   151,   151,   151,   151,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   153,   153,   153,
     153,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     6,     6,     6,     6,     6,     6,     6,     9,
       6,     6,     7,     5,     6,     5,     0,     4,     1,     6,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     2,     7,     8,     8,
       8,     6,     2,     2,     9,     9,     8,     3,     1,     5,
       6,     3,     3,     3,     1,     5,     5,     5,     5,     5,
       2,     7,     5,     5,     2,     2,     2,     3,     3,     3,
       5,     5,     5,     2,     3,     3,     3,     4,     3,     3,
       6,     3,     6,     6,     6,     6,     6,     6,     4,     4,
       4,     6,     6,     5,     5,     7,     7,     6,     6,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     4,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
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
  switch (yykind)
    {
    case YYSYMBOL_T_TEXT: /* T_TEXT  */
#line 186 "socialstory_parser.y"
            { free(((*yyvaluep).sval)); }
#line 1806 "socialstory_parser.tab.c"
        break;

    case YYSYMBOL_T_ID: /* T_ID  */
#line 186 "socialstory_parser.y"
            { free(((*yyvaluep).sval)); }
#line 1812 "socialstory_parser.tab.c"
        break;

      default:
        break;
    }
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
  case 2: /* program: T_GO_LIVE T_DOT statements T_END_LIVE T_DOT  */
#line 255 "socialstory_parser.y"
    {
        ast_root = make_node(AST_PROGRAM);
        ast_root->body = (yyvsp[-2].node);
        (yyval.node) = ast_root;
        fprintf(output_file, "\n✅ Parse successful! AST built.\n");
    }
#line 2087 "socialstory_parser.tab.c"
    break;

  case 3: /* program: T_GO_LIVE T_DOT T_END_LIVE T_DOT  */
#line 262 "socialstory_parser.y"
    {
        ast_root = make_node(AST_PROGRAM);
        ast_root->body = NULL;
        (yyval.node) = ast_root;
        fprintf(output_file, "\n✅ Parse successful! Empty program.\n");
    }
#line 2098 "socialstory_parser.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 272 "socialstory_parser.y"
    {
        if ((yyvsp[-1].node)) {
            ASTNode* temp = (yyvsp[-1].node);
            while (temp->next) temp = temp->next;
            temp->next = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        } else {
            (yyval.node) = (yyvsp[0].node);
        }
    }
#line 2113 "socialstory_parser.tab.c"
    break;

  case 5: /* statements: statement  */
#line 282 "socialstory_parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2119 "socialstory_parser.tab.c"
    break;

  case 6: /* statement: account_create  */
#line 286 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2125 "socialstory_parser.tab.c"
    break;

  case 7: /* statement: account_init  */
#line 287 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2131 "socialstory_parser.tab.c"
    break;

  case 8: /* statement: account_update  */
#line 288 "socialstory_parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2137 "socialstory_parser.tab.c"
    break;

  case 9: /* statement: story_post  */
#line 289 "socialstory_parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2143 "socialstory_parser.tab.c"
    break;

  case 10: /* statement: conditional  */
#line 290 "socialstory_parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2149 "socialstory_parser.tab.c"
    break;

  case 11: /* statement: loop  */
#line 291 "socialstory_parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2155 "socialstory_parser.tab.c"
    break;

  case 12: /* statement: loop_control  */
#line 292 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2161 "socialstory_parser.tab.c"
    break;

  case 13: /* statement: function_def  */
#line 293 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2167 "socialstory_parser.tab.c"
    break;

  case 14: /* statement: function_call  */
#line 294 "socialstory_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2173 "socialstory_parser.tab.c"
    break;

  case 15: /* statement: builtin_call  */
#line 295 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2179 "socialstory_parser.tab.c"
    break;

  case 16: /* statement: io_statement  */
#line 296 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2185 "socialstory_parser.tab.c"
    break;

  case 17: /* statement: account_update_ext  */
#line 297 "socialstory_parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2191 "socialstory_parser.tab.c"
    break;

  case 18: /* statement: feed_statement  */
#line 298 "socialstory_parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2197 "socialstory_parser.tab.c"
    break;

  case 19: /* statement: error T_DOT  */
#line 299 "socialstory_parser.y"
                  {
        fprintf(stderr, "⚠️ Syntax error at line %d: Skipping to next statement\n", yylineno);
        fprintf(output_file, "⚠️ Syntax error at line %d: Recovered\n", yylineno);
        yyerrok;
        semantic_errors++;
        (yyval.node) = NULL;
    }
#line 2209 "socialstory_parser.tab.c"
    break;

  case 20: /* account_create: T_THE_ACCOUNT T_ID T_WAS_CREATED T_DOT  */
#line 310 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_CREATE);
        (yyval.node)->sval = (yyvsp[-2].sval);
        (yyval.node)->line_number = yylineno;
        check_duplicate_account((yyvsp[-2].sval), yylineno);
        {
            SymbolEntry *existing = lookup_symbol((yyvsp[-2].sval));
            if (!(existing && existing->type == SYM_ACCOUNT))
            {
                insert_symbol((yyvsp[-2].sval), SYM_ACCOUNT);
            }
        }
    }
#line 2227 "socialstory_parser.tab.c"
    break;

  case 21: /* account_init: T_THE_ACCOUNT T_ID T_STARTED_WITH T_NUMBER metric T_DOT  */
#line 327 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2240 "socialstory_parser.tab.c"
    break;

  case 22: /* account_init: T_THE_ACCOUNT T_ID T_NOW_HAS T_NUMBER metric T_DOT  */
#line 336 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2253 "socialstory_parser.tab.c"
    break;

  case 23: /* account_init: T_THE_ACCOUNT T_ID T_BEGAN_AT T_DECIMAL metric T_DOT  */
#line 345 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->fval = (yyvsp[-2].fval);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2266 "socialstory_parser.tab.c"
    break;

  case 24: /* account_init: T_THE_ACCOUNT T_ID T_NOW_HAS expression metric T_DOT  */
#line 354 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->right = (yyvsp[-2].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2279 "socialstory_parser.tab.c"
    break;

  case 25: /* account_update: T_THE_ACCOUNT T_ID T_GAINED expression metric T_DOT  */
#line 366 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->right = (yyvsp[-2].node);   /* expression node */
        (yyval.node)->ival = 0;     /* 0 = add */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2293 "socialstory_parser.tab.c"
    break;

  case 26: /* account_update: T_THE_ACCOUNT T_ID T_LOST expression metric T_DOT  */
#line 376 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->right = (yyvsp[-2].node);   /* expression node */
        (yyval.node)->ival = -1;    /* -1 = subtract */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2307 "socialstory_parser.tab.c"
    break;

  case 27: /* account_update: T_THE_ACCOUNT T_ID T_INCREASED_BY expression metric T_DOT  */
#line 386 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->right = (yyvsp[-2].node);
        (yyval.node)->ival = 0;
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2321 "socialstory_parser.tab.c"
    break;

  case 28: /* account_update: T_THE_ACCOUNT T_ID T_DECREASED_BY expression metric T_DOT  */
#line 396 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->right = (yyvsp[-2].node);
        (yyval.node)->ival = -1;    /* -1 = subtract */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2335 "socialstory_parser.tab.c"
    break;

  case 29: /* story_post: T_THE_ACCOUNT T_ID T_POSTED T_ABOUT T_TEXT T_THAT_HAD T_NUMBER T_VIEWS T_DOT  */
#line 409 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_STORY_POST);
        (yyval.node)->sval = (yyvsp[-7].sval);
        (yyval.node)->left = make_node_with_string(AST_LITERAL_STRING, (yyvsp[-4].sval));
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-7].sval), yylineno);
    }
#line 2348 "socialstory_parser.tab.c"
    break;

  case 30: /* story_post: T_THE_ACCOUNT T_ID T_POSTED T_ABOUT T_TEXT T_DOT  */
#line 418 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_STORY_POST);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->left = make_node_with_string(AST_LITERAL_STRING, (yyvsp[-1].sval));
        (yyval.node)->ival = 5000; // Default views
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 2361 "socialstory_parser.tab.c"
    break;

  case 31: /* conditional: T_WHEN comparison T_LBRACE statements T_RBRACE optional_else  */
#line 430 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONDITIONAL);
        (yyval.node)->condition = (yyvsp[-4].node);
        (yyval.node)->body = (yyvsp[-2].node);
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2373 "socialstory_parser.tab.c"
    break;

  case 32: /* conditional: T_WHEN T_OPPOSITE comparison T_LBRACE statements T_RBRACE optional_else  */
#line 438 "socialstory_parser.y"
    {
        /* NEW FEATURE: opposite (logical NOT) */
        (yyval.node) = make_node(AST_CONDITIONAL);
        ASTNode* not_node = make_node(AST_UNARY_OP);
        not_node->ival = 0; // NOT operation
        not_node->left = (yyvsp[-4].node);
        (yyval.node)->condition = not_node;
        (yyval.node)->body = (yyvsp[-2].node);
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2389 "socialstory_parser.tab.c"
    break;

  case 33: /* conditional: T_WHEN comparison T_LBRACE T_RBRACE optional_else  */
#line 451 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONDITIONAL);
        (yyval.node)->condition = (yyvsp[-3].node);
        (yyval.node)->body = NULL;  // Empty body allowed
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
        
        fprintf(output_file, "⚠️  Note at line %d: Empty conditional block detected\n", yylineno);
    }
#line 2403 "socialstory_parser.tab.c"
    break;

  case 34: /* conditional: T_WHEN T_OPPOSITE comparison T_LBRACE T_RBRACE optional_else  */
#line 461 "socialstory_parser.y"
    {
        /* Empty conditional with opposite */
        (yyval.node) = make_node(AST_CONDITIONAL);
        ASTNode* not_node = make_node(AST_UNARY_OP);
        not_node->ival = 0; // NOT operation
        not_node->left = (yyvsp[-3].node);
        (yyval.node)->condition = not_node;
        (yyval.node)->body = NULL;  // Empty body allowed
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
        
        fprintf(output_file, "⚠️  Note at line %d: Empty conditional block detected\n", yylineno);
    }
#line 2421 "socialstory_parser.tab.c"
    break;

  case 35: /* conditional: T_WHEN error T_LBRACE statements T_RBRACE  */
#line 474 "socialstory_parser.y"
                                                {
        fprintf(stderr, "⚠️ Invalid condition at line %d\n", yylineno);
        yyerrok;
        semantic_errors++;
        (yyval.node) = NULL;
    }
#line 2432 "socialstory_parser.tab.c"
    break;

  case 36: /* optional_else: %empty  */
#line 483 "socialstory_parser.y"
                                           { (yyval.node) = NULL; }
#line 2438 "socialstory_parser.tab.c"
    break;

  case 37: /* optional_else: T_OTHERWISE T_LBRACE statements T_RBRACE  */
#line 485 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONDITIONAL);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2448 "socialstory_parser.tab.c"
    break;

  case 38: /* optional_else: else_if_chain  */
#line 490 "socialstory_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2454 "socialstory_parser.tab.c"
    break;

  case 39: /* else_if_chain: T_OTHERWISE_IF comparison T_LBRACE statements T_RBRACE optional_else  */
#line 495 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONDITIONAL);
        (yyval.node)->condition = (yyvsp[-4].node);
        (yyval.node)->body = (yyvsp[-2].node);
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2466 "socialstory_parser.tab.c"
    break;

  case 40: /* comparison: account_metric_ref T_MORE_THAN expression  */
#line 507 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_GT;
        (yyval.node)->line_number = yylineno;
    }
#line 2476 "socialstory_parser.tab.c"
    break;

  case 41: /* comparison: account_metric_ref T_LESS_THAN expression  */
#line 513 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_LT;
        (yyval.node)->line_number = yylineno;
    }
#line 2486 "socialstory_parser.tab.c"
    break;

  case 42: /* comparison: account_metric_ref T_EXACTLY expression  */
#line 519 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2496 "socialstory_parser.tab.c"
    break;

  case 43: /* comparison: account_metric_ref T_EQUAL_TO expression  */
#line 525 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2506 "socialstory_parser.tab.c"
    break;

  case 44: /* comparison: account_metric_ref T_NOT_EQUAL_TO expression  */
#line 531 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_NEQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2516 "socialstory_parser.tab.c"
    break;

  case 45: /* comparison: account_metric_ref T_AT_LEAST expression  */
#line 537 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_GTE;
        (yyval.node)->line_number = yylineno;
    }
#line 2526 "socialstory_parser.tab.c"
    break;

  case 46: /* comparison: account_metric_ref T_AT_MOST expression  */
#line 543 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_LTE;
        (yyval.node)->line_number = yylineno;
    }
#line 2536 "socialstory_parser.tab.c"
    break;

  case 47: /* comparison: account_metric_ref T_EXCEEDED expression  */
#line 549 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_GT;
        (yyval.node)->line_number = yylineno;
    }
#line 2546 "socialstory_parser.tab.c"
    break;

  case 48: /* comparison: account_metric_ref T_DROPPED_BELOW expression  */
#line 555 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_LT;
        (yyval.node)->line_number = yylineno;
    }
#line 2556 "socialstory_parser.tab.c"
    break;

  case 49: /* comparison: metric T_MORE_THAN expression  */
#line 562 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_GT;
        (yyval.node)->line_number = yylineno;
    }
#line 2566 "socialstory_parser.tab.c"
    break;

  case 50: /* comparison: metric T_LESS_THAN expression  */
#line 568 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_LT;
        (yyval.node)->line_number = yylineno;
    }
#line 2576 "socialstory_parser.tab.c"
    break;

  case 51: /* comparison: metric T_EXACTLY expression  */
#line 574 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2586 "socialstory_parser.tab.c"
    break;

  case 52: /* comparison: expression T_MORE_THAN expression  */
#line 581 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_GT;
        (yyval.node)->line_number = yylineno;
    }
#line 2596 "socialstory_parser.tab.c"
    break;

  case 53: /* comparison: expression T_LESS_THAN expression  */
#line 587 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_LT;
        (yyval.node)->line_number = yylineno;
    }
#line 2606 "socialstory_parser.tab.c"
    break;

  case 54: /* comparison: expression T_EXACTLY expression  */
#line 593 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2616 "socialstory_parser.tab.c"
    break;

  case 55: /* comparison: expression T_EQUAL_TO expression  */
#line 599 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2626 "socialstory_parser.tab.c"
    break;

  case 56: /* comparison: expression T_NOT_EQUAL_TO expression  */
#line 605 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_NEQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2636 "socialstory_parser.tab.c"
    break;

  case 57: /* comparison: expression T_AT_LEAST expression  */
#line 611 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_GTE;
        (yyval.node)->line_number = yylineno;
    }
#line 2646 "socialstory_parser.tab.c"
    break;

  case 58: /* comparison: expression T_AT_MOST expression  */
#line 617 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_LTE;
        (yyval.node)->line_number = yylineno;
    }
#line 2656 "socialstory_parser.tab.c"
    break;

  case 59: /* comparison: expression T_DIFFERENT_FROM expression  */
#line 623 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_NEQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2666 "socialstory_parser.tab.c"
    break;

  case 60: /* comparison: account_metric_ref T_DIFFERENT_FROM expression  */
#line 629 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_NEQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2676 "socialstory_parser.tab.c"
    break;

  case 61: /* comparison: account_metric_ref T_STAYED_AT expression  */
#line 635 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2686 "socialstory_parser.tab.c"
    break;

  case 62: /* comparison: account_metric_ref T_REACHED expression  */
#line 641 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = CMP_EQ;
        (yyval.node)->line_number = yylineno;
    }
#line 2696 "socialstory_parser.tab.c"
    break;

  case 63: /* comparison: account_metric_ref T_WENT_VIRAL  */
#line 647 "socialstory_parser.y"
    {
        /* When likes went viral => likes > 1000 */
        ASTNode* threshold = make_node_with_int(AST_LITERAL_INT, 1000);
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-1].node), threshold);
        (yyval.node)->ival = CMP_GT;
        (yyval.node)->line_number = yylineno;
    }
#line 2708 "socialstory_parser.tab.c"
    break;

  case 64: /* comparison: comparison T_ALSO comparison  */
#line 655 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_LOGICAL_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = 0; // AND
        (yyval.node)->line_number = yylineno;
    }
#line 2718 "socialstory_parser.tab.c"
    break;

  case 65: /* comparison: comparison T_EITHER comparison  */
#line 661 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_LOGICAL_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = 1; // OR
        (yyval.node)->line_number = yylineno;
    }
#line 2728 "socialstory_parser.tab.c"
    break;

  case 66: /* account_metric_ref: T_ID metric  */
#line 671 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_REF);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->sval2 = (yyvsp[0].node)->sval;
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-1].sval), yylineno);
        free((yyvsp[0].node)); // Free the temporary metric node
    }
#line 2741 "socialstory_parser.tab.c"
    break;

  case 67: /* loop: T_EVERY_DAY_FOR T_NUMBER T_DAYS T_COMMA T_LBRACE statements T_RBRACE  */
#line 683 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP);
        (yyval.node)->ival = 1;
        (yyval.node)->ival2 = (yyvsp[-5].ival);
        (yyval.node)->step = 1;
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2754 "socialstory_parser.tab.c"
    break;

  case 68: /* loop: T_EVERY T_NUMBER T_DAYS T_INCREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE  */
#line 692 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_INCREMENT);
        (yyval.node)->ival = 1;
        (yyval.node)->ival2 = (yyvsp[-6].ival);
        (yyval.node)->step = (yyvsp[-3].ival);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2767 "socialstory_parser.tab.c"
    break;

  case 69: /* loop: T_EVERY T_NUMBER T_DAYS T_DECREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE  */
#line 701 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_DECREMENT);
        (yyval.node)->ival = (yyvsp[-6].ival);
        (yyval.node)->ival2 = 1;
        (yyval.node)->step = (yyvsp[-3].ival);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2780 "socialstory_parser.tab.c"
    break;

  case 70: /* loop: T_FOR_EACH T_FOLLOWER_FROM T_NUMBER T_TO T_NUMBER T_LBRACE statements T_RBRACE  */
#line 711 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_RANGE);
        (yyval.node)->ival = (yyvsp[-5].ival);
        (yyval.node)->ival2 = (yyvsp[-3].ival);
        (yyval.node)->step = 1;
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2793 "socialstory_parser.tab.c"
    break;

  case 71: /* loop: T_TRENDING_LOOP T_UNTIL comparison T_LBRACE statements T_RBRACE  */
#line 721 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_TRENDING);
        (yyval.node)->condition = (yyvsp[-3].node);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2804 "socialstory_parser.tab.c"
    break;

  case 72: /* loop_control: T_STOP_THE_STORY T_DOT  */
#line 731 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BREAK);
        (yyval.node)->line_number = yylineno;
    }
#line 2813 "socialstory_parser.tab.c"
    break;

  case 73: /* loop_control: T_SKIP_THIS_POST T_DOT  */
#line 736 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONTINUE);
        (yyval.node)->line_number = yylineno;
    }
#line 2822 "socialstory_parser.tab.c"
    break;

  case 74: /* function_def: T_THE_STORY_OF T_ID T_BEGINS_WITH param_list T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT  */
#line 745 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_DEF);
        (yyval.node)->sval = (yyvsp[-7].sval);
        (yyval.node)->param = (yyvsp[-5].node);
        (yyval.node)->body = (yyvsp[-3].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2834 "socialstory_parser.tab.c"
    break;

  case 75: /* function_def: T_THE_STORY_OF T_ID T_BEGINS_WITH T_ID T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT  */
#line 753 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_DEF);
        (yyval.node)->sval = (yyvsp[-7].sval);
        (yyval.node)->param = make_node_with_string(AST_IDENTIFIER, (yyvsp[-5].sval));
        (yyval.node)->body = (yyvsp[-3].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2846 "socialstory_parser.tab.c"
    break;

  case 76: /* function_def: T_THE_STORY_OF T_ID T_BEGINS_WITH T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT  */
#line 761 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_DEF);
        (yyval.node)->sval = (yyvsp[-6].sval);
        (yyval.node)->body = (yyvsp[-3].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2857 "socialstory_parser.tab.c"
    break;

  case 77: /* param_list: T_ID T_COMMA param_list  */
#line 771 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_string(AST_IDENTIFIER, (yyvsp[-2].sval));
        (yyval.node)->next = (yyvsp[0].node);
    }
#line 2866 "socialstory_parser.tab.c"
    break;

  case 78: /* param_list: T_ID  */
#line 776 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_string(AST_IDENTIFIER, (yyvsp[0].sval));
    }
#line 2874 "socialstory_parser.tab.c"
    break;

  case 79: /* function_call: T_TELL T_ID T_WITH arg_list T_DOT  */
#line 783 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_CALL);
        (yyval.node)->sval = (yyvsp[-3].sval);
        (yyval.node)->param = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2885 "socialstory_parser.tab.c"
    break;

  case 80: /* function_call: T_TELL T_ID T_LPAREN arg_list T_RPAREN T_DOT  */
#line 790 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_CALL);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->param = (yyvsp[-2].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2896 "socialstory_parser.tab.c"
    break;

  case 81: /* function_call: T_TELL T_ID T_DOT  */
#line 797 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_CALL);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2906 "socialstory_parser.tab.c"
    break;

  case 82: /* function_call: T_TELL_BACK expression T_DOT  */
#line 803 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_RETURN);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 2916 "socialstory_parser.tab.c"
    break;

  case 83: /* arg_list: expression T_COMMA arg_list  */
#line 812 "socialstory_parser.y"
    {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->next = (yyvsp[0].node);
    }
#line 2925 "socialstory_parser.tab.c"
    break;

  case 84: /* arg_list: expression  */
#line 817 "socialstory_parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2933 "socialstory_parser.tab.c"
    break;

  case 85: /* builtin_call: T_CALCULATE_VIRALITY T_FOR T_THE_ACCOUNT T_ID T_DOT  */
#line 824 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("calculate_virality");
        (yyval.node)->sval2 = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2944 "socialstory_parser.tab.c"
    break;

  case 86: /* builtin_call: T_CALCULATE_VIRALITY T_LPAREN T_ID T_RPAREN T_DOT  */
#line 831 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("calculate_virality");
        (yyval.node)->sval2 = (yyvsp[-2].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2955 "socialstory_parser.tab.c"
    break;

  case 87: /* builtin_call: T_CALCULATE_ENGAGEMENT T_FOR T_THE_ACCOUNT T_ID T_DOT  */
#line 838 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("calculate_engagement");
        (yyval.node)->sval2 = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2966 "socialstory_parser.tab.c"
    break;

  case 88: /* builtin_call: T_ANALYZE_GROWTH T_FOR T_THE_ACCOUNT T_ID T_DOT  */
#line 845 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("analyze_growth");
        (yyval.node)->sval2 = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2977 "socialstory_parser.tab.c"
    break;

  case 89: /* builtin_call: T_ANALYZE_GROWTH T_LPAREN T_ID T_RPAREN T_DOT  */
#line 852 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("analyze_growth");
        (yyval.node)->sval2 = (yyvsp[-2].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2988 "socialstory_parser.tab.c"
    break;

  case 90: /* builtin_call: T_FIND_MAX_VIRAL_ACCOUNT T_DOT  */
#line 859 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_max_viral_account");
        (yyval.node)->line_number = yylineno;
    }
#line 2998 "socialstory_parser.tab.c"
    break;

  case 91: /* builtin_call: T_FIND_MAX_VIRAL_ACCOUNT T_LPAREN T_ID T_COMMA T_ID T_RPAREN T_DOT  */
#line 865 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_max_viral_account");
        (yyval.node)->line_number = yylineno;

        free((yyvsp[-4].sval));
        free((yyvsp[-2].sval));
    }
#line 3011 "socialstory_parser.tab.c"
    break;

  case 92: /* builtin_call: T_REVERSE_THE_CAPTION T_LPAREN T_TEXT T_RPAREN T_DOT  */
#line 875 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_STRING_OP);
        (yyval.node)->sval = strdup("reverse");
        (yyval.node)->sval2 = (yyvsp[-2].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3022 "socialstory_parser.tab.c"
    break;

  case 93: /* builtin_call: T_CHECK_IF_TRENDING T_FOR T_THE_ACCOUNT T_ID T_DOT  */
#line 883 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("check_if_trending");
        (yyval.node)->sval2 = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3033 "socialstory_parser.tab.c"
    break;

  case 94: /* builtin_call: T_CHECK_IF_TRENDING T_DOT  */
#line 890 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("check_if_trending");
        (yyval.node)->line_number = yylineno;
    }
#line 3043 "socialstory_parser.tab.c"
    break;

  case 95: /* builtin_call: T_COUNT_TOTAL_ENGAGEMENT T_DOT  */
#line 897 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("count_total_engagement");
        (yyval.node)->line_number = yylineno;
    }
#line 3053 "socialstory_parser.tab.c"
    break;

  case 96: /* builtin_call: T_FIND_TOP_POST T_DOT  */
#line 904 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_top_post");
        (yyval.node)->line_number = yylineno;
    }
#line 3063 "socialstory_parser.tab.c"
    break;

  case 97: /* builtin_call: T_FIND_HIGHEST_REACH T_THE_FEED T_DOT  */
#line 911 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_highest_reach");
        (yyval.node)->line_number = yylineno;
    }
#line 3073 "socialstory_parser.tab.c"
    break;

  case 98: /* builtin_call: T_FIND_TOTAL_REACH T_THE_FEED T_DOT  */
#line 918 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_total_reach");
        (yyval.node)->line_number = yylineno;
    }
#line 3083 "socialstory_parser.tab.c"
    break;

  case 99: /* builtin_call: T_DETECT_SPAM T_TEXT T_DOT  */
#line 925 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_STRING_OP);
        (yyval.node)->sval = strdup("detect_spam");
        (yyval.node)->sval2 = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3094 "socialstory_parser.tab.c"
    break;

  case 100: /* builtin_call: T_CLAMP_ENGAGEMENT T_NUMBER T_AND_THEN T_NUMBER T_DOT  */
#line 933 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("clamp_engagement");
        (yyval.node)->ival = (yyvsp[-3].ival);
        (yyval.node)->ival2 = (yyvsp[-1].ival);
        (yyval.node)->line_number = yylineno;
    }
#line 3106 "socialstory_parser.tab.c"
    break;

  case 101: /* builtin_call: T_CLAMP_ENGAGEMENT T_DECIMAL T_AND_THEN T_DECIMAL T_DOT  */
#line 941 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("clamp_engagement");
        (yyval.node)->fval = (yyvsp[-3].fval);
        (yyval.node)->ival2 = (int)(yyvsp[-1].fval);
        (yyval.node)->line_number = yylineno;
    }
#line 3118 "socialstory_parser.tab.c"
    break;

  case 102: /* builtin_call: T_REVERSE_GROWTH T_FOR T_THE_ACCOUNT T_ID T_DOT  */
#line 950 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("reverse_growth");
        (yyval.node)->sval2 = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3129 "socialstory_parser.tab.c"
    break;

  case 103: /* builtin_call: T_REVERSE_GROWTH T_DOT  */
#line 957 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("reverse_growth");
        (yyval.node)->line_number = yylineno;
    }
#line 3139 "socialstory_parser.tab.c"
    break;

  case 104: /* io_statement: T_ANNOUNCE T_TEXT T_DOT  */
#line 966 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ANNOUNCE);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3149 "socialstory_parser.tab.c"
    break;

  case 105: /* io_statement: T_DISPLAY T_TEXT T_DOT  */
#line 972 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ANNOUNCE);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3159 "socialstory_parser.tab.c"
    break;

  case 106: /* io_statement: T_DISPLAY T_ID T_DOT  */
#line 978 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_DISPLAY);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3169 "socialstory_parser.tab.c"
    break;

  case 107: /* io_statement: T_DISPLAY T_ID metric T_DOT  */
#line 984 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_DISPLAY);
        (yyval.node)->sval = (yyvsp[-2].sval);
        (yyval.node)->sval2 = (yyvsp[-1].node)->sval;
        (yyval.node)->line_number = yylineno;
        free((yyvsp[-1].node));
    }
#line 3181 "socialstory_parser.tab.c"
    break;

  case 108: /* io_statement: T_ASK_FOR T_ID T_DOT  */
#line 993 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ASK_FOR);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3191 "socialstory_parser.tab.c"
    break;

  case 109: /* io_statement: T_ANNOUNCE T_ID T_DOT  */
#line 999 "socialstory_parser.y"
    {
        /* Display a variable's value via Announce */
        (yyval.node) = make_node(AST_DISPLAY);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3202 "socialstory_parser.tab.c"
    break;

  case 110: /* io_statement: T_DISPLAY T_THE_FEED T_AT_INDEX expression metric T_DOT  */
#line 1006 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_DISPLAY);
        (yyval.node)->left = (yyvsp[-2].node);           /* index expression */
        (yyval.node)->sval = (yyvsp[-1].node)->sval;     /* metric */
        (yyval.node)->line_number = yylineno;
        free((yyvsp[-1].node));
    }
#line 3214 "socialstory_parser.tab.c"
    break;

  case 111: /* io_statement: T_DISPLAY T_THE_FEED T_DOT  */
#line 1014 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_DISPLAY);
        (yyval.node)->line_number = yylineno;
    }
#line 3223 "socialstory_parser.tab.c"
    break;

  case 112: /* account_update_ext: T_THE_ACCOUNT T_ID T_WAS_UPDATED_TO T_NUMBER metric T_DOT  */
#line 1027 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 3236 "socialstory_parser.tab.c"
    break;

  case 113: /* account_update_ext: T_THE_ACCOUNT T_ID T_BECAME T_NUMBER metric T_DOT  */
#line 1036 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 3249 "socialstory_parser.tab.c"
    break;

  case 114: /* account_update_ext: T_THE_ACCOUNT T_ID T_MULTIPLIED_BY T_NUMBER metric T_DOT  */
#line 1045 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->ival2 = 1; /* flag: multiply */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 3263 "socialstory_parser.tab.c"
    break;

  case 115: /* account_update_ext: T_THE_ACCOUNT T_ID T_MULTIPLIED_BY expression metric T_DOT  */
#line 1055 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->right = (yyvsp[-2].node);
        (yyval.node)->ival2 = 1; /* flag: multiply */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 3277 "socialstory_parser.tab.c"
    break;

  case 116: /* account_update_ext: T_THE_ACCOUNT T_ID T_DIVIDED_BY T_NUMBER metric T_DOT  */
#line 1065 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->ival2 = 2; /* flag: divide */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 3291 "socialstory_parser.tab.c"
    break;

  case 117: /* account_update_ext: T_THE_ACCOUNT T_ID T_DIVIDED_BY expression metric T_DOT  */
#line 1075 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->right = (yyvsp[-2].node);
        (yyval.node)->ival2 = 2; /* flag: divide */
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-4].sval), yylineno);
    }
#line 3305 "socialstory_parser.tab.c"
    break;

  case 118: /* account_update_ext: T_THE_CAPTION T_READS T_TEXT T_DOT  */
#line 1085 "socialstory_parser.y"
    {
        /* Caption assignment */
        (yyval.node) = make_node(AST_ANNOUNCE);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 3316 "socialstory_parser.tab.c"
    break;

  case 119: /* account_update_ext: T_THE_ACCOUNT T_ID T_IS_VIRAL T_DOT  */
#line 1092 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-2].sval);
        (yyval.node)->ival2 = 3; /* flag: set viral */
        (yyval.node)->left = make_node_with_int(AST_LITERAL_INT, 1);
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("viral");
        (yyval.node)->left = m;
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-2].sval), yylineno);
    }
#line 3332 "socialstory_parser.tab.c"
    break;

  case 120: /* account_update_ext: T_THE_ACCOUNT T_ID T_IS_TRENDING T_DOT  */
#line 1104 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-2].sval);
        (yyval.node)->ival2 = 4; /* flag: set trending */
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("trending");
        (yyval.node)->left = m;
        (yyval.node)->line_number = yylineno;
        check_account_exists((yyvsp[-2].sval), yylineno);
    }
#line 3347 "socialstory_parser.tab.c"
    break;

  case 121: /* account_update_ext: T_THE_POST T_ID T_STARTED_WITH T_NUMBER metric T_DOT  */
#line 1115 "socialstory_parser.y"
    {
        /* Post metrics (reuse account_init semantics) */
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 3360 "socialstory_parser.tab.c"
    break;

  case 122: /* account_update_ext: T_THE_POST T_ID T_NOW_HAS T_NUMBER metric T_DOT  */
#line 1124 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 3372 "socialstory_parser.tab.c"
    break;

  case 123: /* feed_statement: T_THE_FEED T_CONTAINS T_NUMBER T_POSTS T_DOT  */
#line 1141 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_DECLARE);
        (yyval.node)->ival = (yyvsp[-2].ival);
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("posts");
        (yyval.node)->left = m;
        (yyval.node)->line_number = yylineno;
    }
#line 3385 "socialstory_parser.tab.c"
    break;

  case 124: /* feed_statement: T_THE_FEED T_CONTAINS T_NUMBER T_STORIES T_DOT  */
#line 1150 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_DECLARE);
        (yyval.node)->ival = (yyvsp[-2].ival);
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("stories");
        (yyval.node)->left = m;
        (yyval.node)->line_number = yylineno;
    }
#line 3398 "socialstory_parser.tab.c"
    break;

  case 125: /* feed_statement: T_THE_FEED T_AT_INDEX expression T_NOW_HAS expression metric T_DOT  */
#line 1159 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_SET);
        (yyval.node)->left = (yyvsp[-4].node);            /* index expression */
        (yyval.node)->right = (yyvsp[-2].node);           /* value expression */
        (yyval.node)->sval = (yyvsp[-1].node)->sval;      /* metric */
        (yyval.node)->line_number = yylineno;
        free((yyvsp[-1].node));
    }
#line 3411 "socialstory_parser.tab.c"
    break;

  case 126: /* feed_statement: T_THE_FEED T_AT_INDEX expression T_STARTED_WITH expression metric T_DOT  */
#line 1168 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_SET);
        (yyval.node)->left = (yyvsp[-4].node);            /* index expression */
        (yyval.node)->right = (yyvsp[-2].node);           /* value expression */
        (yyval.node)->sval = (yyvsp[-1].node)->sval;      /* metric */
        (yyval.node)->line_number = yylineno;
        free((yyvsp[-1].node));
    }
#line 3424 "socialstory_parser.tab.c"
    break;

  case 127: /* feed_statement: T_FOR_EACH T_POST_IN T_THE_FEED T_LBRACE statements T_RBRACE  */
#line 1177 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_COLLECTION);
        (yyval.node)->sval = strdup("post");
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 3435 "socialstory_parser.tab.c"
    break;

  case 128: /* feed_statement: T_FOR_EACH T_STORY_IN T_THE_FEED T_LBRACE statements T_RBRACE  */
#line 1184 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_COLLECTION);
        (yyval.node)->sval = strdup("story");
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 3446 "socialstory_parser.tab.c"
    break;

  case 129: /* expression: term  */
#line 1193 "socialstory_parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 3452 "socialstory_parser.tab.c"
    break;

  case 130: /* expression: expression T_PLUS term  */
#line 1195 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_ADD;
        (yyval.node)->line_number = yylineno;
    }
#line 3462 "socialstory_parser.tab.c"
    break;

  case 131: /* expression: expression T_MINUS term  */
#line 1201 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_SUB;
        (yyval.node)->line_number = yylineno;
    }
#line 3472 "socialstory_parser.tab.c"
    break;

  case 132: /* term: factor  */
#line 1209 "socialstory_parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 3478 "socialstory_parser.tab.c"
    break;

  case 133: /* term: term T_TIMES factor  */
#line 1211 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_MUL;
        (yyval.node)->line_number = yylineno;
    }
#line 3488 "socialstory_parser.tab.c"
    break;

  case 134: /* term: term T_MULTIPLY factor  */
#line 1217 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_MUL;
        (yyval.node)->line_number = yylineno;
    }
#line 3498 "socialstory_parser.tab.c"
    break;

  case 135: /* term: term T_DIVIDED_BY factor  */
#line 1223 "socialstory_parser.y"
    {
    (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
    (yyval.node)->ival = OP_DIV;
    (yyval.node)->line_number = yylineno;
    }
#line 3508 "socialstory_parser.tab.c"
    break;

  case 136: /* term: term T_DIVIDE factor  */
#line 1229 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_DIV;
        (yyval.node)->line_number = yylineno;
    }
#line 3518 "socialstory_parser.tab.c"
    break;

  case 137: /* term: term T_DIVIDED_EVENLY_BY factor  */
#line 1235 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_DIV;
        (yyval.node)->line_number = yylineno;
    }
#line 3528 "socialstory_parser.tab.c"
    break;

  case 138: /* term: term T_MODULO factor  */
#line 1241 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = OP_MOD;
        (yyval.node)->line_number = yylineno;
    }
#line 3538 "socialstory_parser.tab.c"
    break;

  case 139: /* factor: literal  */
#line 1249 "socialstory_parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 3544 "socialstory_parser.tab.c"
    break;

  case 140: /* factor: account_metric_ref  */
#line 1250 "socialstory_parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3550 "socialstory_parser.tab.c"
    break;

  case 141: /* factor: metric  */
#line 1251 "socialstory_parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 3556 "socialstory_parser.tab.c"
    break;

  case 142: /* factor: T_ID  */
#line 1252 "socialstory_parser.y"
           { (yyval.node) = make_node_with_string(AST_IDENTIFIER, (yyvsp[0].sval)); }
#line 3562 "socialstory_parser.tab.c"
    break;

  case 143: /* factor: T_THE_FEED T_AT_INDEX expression metric  */
#line 1254 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_GET);
        (yyval.node)->left = (yyvsp[-1].node);           /* index expression */
        (yyval.node)->sval = (yyvsp[0].node)->sval;     /* metric */
        (yyval.node)->line_number = yylineno;
        free((yyvsp[0].node));
    }
#line 3574 "socialstory_parser.tab.c"
    break;

  case 144: /* factor: T_THE_FEED T_CONTAINS T_POSTS  */
#line 1262 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_LENGTH);
        (yyval.node)->sval = strdup("posts");
        (yyval.node)->line_number = yylineno;
    }
#line 3584 "socialstory_parser.tab.c"
    break;

  case 145: /* factor: T_THE_FEED T_CONTAINS T_STORIES  */
#line 1268 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FEED_LENGTH);
        (yyval.node)->sval = strdup("stories");
        (yyval.node)->line_number = yylineno;
    }
#line 3594 "socialstory_parser.tab.c"
    break;

  case 146: /* factor: T_LPAREN expression T_RPAREN  */
#line 1273 "socialstory_parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 3600 "socialstory_parser.tab.c"
    break;

  case 147: /* metric: T_LIKES  */
#line 1278 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("likes");
        (yyval.node)->line_number = yylineno;
    }
#line 3610 "socialstory_parser.tab.c"
    break;

  case 148: /* metric: T_FOLLOWERS  */
#line 1284 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("followers");
        (yyval.node)->line_number = yylineno;
    }
#line 3620 "socialstory_parser.tab.c"
    break;

  case 149: /* metric: T_VIEWS  */
#line 1290 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("views");
        (yyval.node)->line_number = yylineno;
    }
#line 3630 "socialstory_parser.tab.c"
    break;

  case 150: /* metric: T_COMMENTS  */
#line 1296 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("comments");
        (yyval.node)->line_number = yylineno;
    }
#line 3640 "socialstory_parser.tab.c"
    break;

  case 151: /* metric: T_SHARES  */
#line 1302 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("shares");
        (yyval.node)->line_number = yylineno;
    }
#line 3650 "socialstory_parser.tab.c"
    break;

  case 152: /* metric: T_REACH  */
#line 1308 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("reach");
        (yyval.node)->line_number = yylineno;
    }
#line 3660 "socialstory_parser.tab.c"
    break;

  case 153: /* metric: T_ENGAGEMENT_RATE  */
#line 1314 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("engagement rate");
        (yyval.node)->line_number = yylineno;
    }
#line 3670 "socialstory_parser.tab.c"
    break;

  case 154: /* metric: T_GROWTH_RATE  */
#line 1320 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("growth rate");
        (yyval.node)->line_number = yylineno;
    }
#line 3680 "socialstory_parser.tab.c"
    break;

  case 155: /* metric: T_POSTS  */
#line 1326 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("posts");
        (yyval.node)->line_number = yylineno;
    }
#line 3690 "socialstory_parser.tab.c"
    break;

  case 156: /* metric: T_STORIES  */
#line 1332 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_METRIC);
        (yyval.node)->sval = strdup("stories");
        (yyval.node)->line_number = yylineno;
    }
#line 3700 "socialstory_parser.tab.c"
    break;

  case 157: /* literal: T_NUMBER  */
#line 1341 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_int(AST_LITERAL_INT, (yyvsp[0].ival));
        (yyval.node)->line_number = yylineno;
    }
#line 3709 "socialstory_parser.tab.c"
    break;

  case 158: /* literal: T_DECIMAL  */
#line 1346 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_float(AST_LITERAL_FLOAT, (yyvsp[0].fval));
        (yyval.node)->line_number = yylineno;
    }
#line 3718 "socialstory_parser.tab.c"
    break;

  case 159: /* literal: T_TEXT  */
#line 1351 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_string(AST_LITERAL_STRING, (yyvsp[0].sval));
        (yyval.node)->line_number = yylineno;
    }
#line 3727 "socialstory_parser.tab.c"
    break;

  case 160: /* literal: T_TRUE_STORY  */
#line 1356 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_int(AST_LITERAL_BOOL, 1);
        (yyval.node)->line_number = yylineno;
    }
#line 3736 "socialstory_parser.tab.c"
    break;

  case 161: /* literal: T_FALSE_ALARM  */
#line 1361 "socialstory_parser.y"
    {
        (yyval.node) = make_node_with_int(AST_LITERAL_BOOL, 0);
        (yyval.node)->line_number = yylineno;
    }
#line 3745 "socialstory_parser.tab.c"
    break;


#line 3749 "socialstory_parser.tab.c"

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

#line 1367 "socialstory_parser.y"


/* ========================================
 * ERROR HANDLING
 * ======================================== */
void yyerror(const char *s) {
    fprintf(stderr, "\n❌ SYNTAX ERROR at line %d:\n", yylineno);
    fprintf(stderr, "   Unexpected token: '%s'\n", yytext);
    fprintf(stderr, "   Parser message: %s\n", s);
    
    /* Helpful context-sensitive hints */
    if (yytext && yytext[0] != '\0') {
        if (strcmp(yytext, "+") == 0 || strcmp(yytext, "-") == 0 ||
            strcmp(yytext, "*") == 0 || strcmp(yytext, "/") == 0) {
            fprintf(stderr, "   Hint: Arithmetic operators (+, -, *, /) work in expressions like:\n");
            fprintf(stderr, "         The account Alice now has 100 + 50 likes.\n");
        } else if (strcmp(yytext, ",") == 0) {
            fprintf(stderr, "   Hint: Check for missing keywords or incorrect list syntax.\n");
            fprintf(stderr, "         Function params: The story of name begins with a, b, c\n");
        } else if (strcmp(yytext, "{") == 0 || strcmp(yytext, "}") == 0) {
            fprintf(stderr, "   Hint: Mismatched braces. Every 'When', loop, or function body needs { and }.\n");
        } else if (strcmp(yytext, ".") == 0) {
            fprintf(stderr, "   Hint: Check the statement before this period for correct syntax.\n");
            fprintf(stderr, "         All statements must end with a period (.)\n");
        } else {
            fprintf(stderr, "   Hint: Check the SocialStoryScript syntax. Statements end with '.'\n");
            fprintf(stderr, "         e.g. 'The account Alice gained 50 likes.'\n");
        }
    }
    fprintf(stderr, "\n");
    
    if (output_file) {
        fprintf(output_file, "\n❌ SYNTAX ERROR at line %d: near '%s' — %s\n", yylineno, yytext, s);
    }
}

int compiler_run(const char* input_filename,
                 const char* output_filename,
                 FILE* input_file,
                 FILE* out_file)
{
    (void)output_filename;

    error_count = 0;
    semantic_errors = 0;
    loop_break_flag = 0;
    loop_continue_flag = 0;
    temp_counter = 0;
    label_counter = 0;

    output_file = out_file;
    yyin       = input_file;

    /* Write output file header */
    fprintf(output_file, "SocialStoryScript Compiler — Output Report\n");
    fprintf(output_file, "==========================================\n");
    fprintf(output_file, "Input file : %s\n", input_filename);
    fprintf(output_file, "==========================================\n\n");

    /* ---- Lex + Parse ---- */
    printf("🔍 Phase 1: Lexical Analysis + Parsing...\n");
    int parse_result = yyparse();

    if (parse_result == 0 && error_count == 0) {
        if (semantic_errors == 0) {
            printf("   ✅ Parsing complete — 0 semantic errors\n\n");
        } else {
            printf("   ⚠️  Parsing complete — %d semantic issue(s) detected before execution\n\n", semantic_errors);
        }

        /* ---- AST ---- */
        printf("🌲 Phase 2: Abstract Syntax Tree\n");
        fprintf(output_file, "\n🌲 ABSTRACT SYNTAX TREE:\n");
        fprintf(output_file, "========================\n");
        print_ast(ast_root, 0);
        print_ast_statistics(output_file);
        printf("   ✅ AST built\n\n");

        /* ---- TAC ---- */
        printf("🔧 Phase 3: Three-Address Code Generation...\n");
        fprintf(output_file, "\n🔧 THREE-ADDRESS CODE:\n");
        fprintf(output_file, "======================\n");
        if (ast_root && ast_root->body) {
            generate_tac_statements(ast_root->body);
        }
        fprintf(output_file, "\n💻 ORIGINAL TAC:\n");
        print_tac_to_file(output_file);
        printf("   ✅ TAC generated: %d temps, %d labels\n\n", temp_counter, label_counter);

        /* ---- Optimize ---- */
        printf("⚡ Phase 4: Code Optimization...\n");
        run_all_optimizations(output_file);
        fprintf(output_file, "\n💻 OPTIMIZED TAC:\n");
        print_tac_to_file(output_file);
        printf("   ✅ Optimizations applied\n\n");

        /* ---- Execute ---- */
        printf("🎬 Phase 5: Program Execution...\n");
        printf("──────────────────────────────────────────\n");
        execute(ast_root);
        printf("──────────────────────────────────────────\n");
        printf("   ✅ Execution complete\n\n");

        /* ---- Symbol Table ---- */
        printf("📋 Phase 6: Symbol Table\n");
        print_symbol_table();
        print_symbol_table_stats(output_file);

        /* ---- Final summary ---- */
        if (semantic_errors == 0 && error_count == 0) {
            fprintf(output_file, "\n✅ Compilation and execution completed successfully\n");
            fprintf(output_file, "   Lexical errors  : %d\n", error_count);
            fprintf(output_file, "   Syntax errors   : 0\n");
            fprintf(output_file, "   Semantic errors : %d\n", semantic_errors);
            fprintf(output_file, "   TAC temporaries : %d\n", temp_counter);
            fprintf(output_file, "   TAC labels      : %d\n", label_counter);
            return 0;
        } else {
            fprintf(output_file, "\n❌ Execution completed with runtime/semantic errors\n");
            fprintf(output_file, "   Lexical errors  : %d\n", error_count);
            fprintf(output_file, "   Syntax errors   : 0\n");
            fprintf(output_file, "   Semantic errors : %d\n", semantic_errors);
            fprintf(output_file, "   TAC temporaries : %d\n", temp_counter);
            fprintf(output_file, "   TAC labels      : %d\n", label_counter);
            return 1;
        }

    } else {
        /* ---- Failure ---- */
        fprintf(output_file, "\n❌ COMPILATION FAILED\n");
        fprintf(output_file, "   Lexical errors  : %d\n", error_count);
        fprintf(output_file, "   Semantic errors : %d\n", semantic_errors);
        return 1;
    }
}
