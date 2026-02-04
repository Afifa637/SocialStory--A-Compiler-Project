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
#include "socialstory_tokens.h"

/* Forward declarations */
void yyerror(const char *s);
int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern int error_count;

/* AST Node Types */
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
    AST_LITERAL_INT,
    AST_LITERAL_FLOAT,
    AST_LITERAL_STRING,
    AST_LITERAL_BOOL,
    AST_IDENTIFIER,
    AST_METRIC
} ASTNodeType;

/* AST Node Structure */
typedef struct ASTNode {
    ASTNodeType type;
    
    /* Value holders */
    int ival;
    float fval;
    char* sval;
    
    /* Node connections */
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* condition;
    struct ASTNode* body;
    struct ASTNode* else_body;
    struct ASTNode* next;
    
    /* Additional info */
    int line_number;
} ASTNode;

/* Symbol Table Entry */
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
    
    struct SymbolEntry* next;
} SymbolEntry;

/* Global variables */
ASTNode* ast_root = NULL;
SymbolEntry* symbol_table = NULL;
int semantic_errors = 0;

/* AST functions */
ASTNode* make_node(ASTNodeType type);
ASTNode* make_node_with_int(ASTNodeType type, int value);
ASTNode* make_node_with_float(ASTNodeType type, float value);
ASTNode* make_node_with_string(ASTNodeType type, char* value);
ASTNode* make_binary_op(ASTNodeType type, ASTNode* left, ASTNode* right);
void print_ast(ASTNode* node, int depth);
void free_ast(ASTNode* node);

/* Symbol table functions */
SymbolEntry* lookup_symbol(const char* name);
SymbolEntry* insert_symbol(const char* name, int sym_type);
void print_symbol_table();
void free_symbol_table();

/* Semantic analysis */
void check_account_exists(const char* name, int line);
void check_duplicate_account(const char* name, int line);

/* Interpreter */
void execute(ASTNode* node);
void execute_statements(ASTNode* node);


#line 190 "socialstory_parser.tab.c"

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
  YYSYMBOL_T_THE_FEED = 40,                /* T_THE_FEED  */
  YYSYMBOL_T_CONTAINS = 41,                /* T_CONTAINS  */
  YYSYMBOL_T_AT_INDEX = 42,                /* T_AT_INDEX  */
  YYSYMBOL_T_LIKES = 43,                   /* T_LIKES  */
  YYSYMBOL_T_FOLLOWERS = 44,               /* T_FOLLOWERS  */
  YYSYMBOL_T_VIEWS = 45,                   /* T_VIEWS  */
  YYSYMBOL_T_COMMENTS = 46,                /* T_COMMENTS  */
  YYSYMBOL_T_SHARES = 47,                  /* T_SHARES  */
  YYSYMBOL_T_POSTS = 48,                   /* T_POSTS  */
  YYSYMBOL_T_STORIES = 49,                 /* T_STORIES  */
  YYSYMBOL_T_ENGAGEMENT_RATE = 50,         /* T_ENGAGEMENT_RATE  */
  YYSYMBOL_T_REACH = 51,                   /* T_REACH  */
  YYSYMBOL_T_GROWTH_RATE = 52,             /* T_GROWTH_RATE  */
  YYSYMBOL_T_WHEN = 53,                    /* T_WHEN  */
  YYSYMBOL_T_OTHERWISE_IF = 54,            /* T_OTHERWISE_IF  */
  YYSYMBOL_T_OTHERWISE = 55,               /* T_OTHERWISE  */
  YYSYMBOL_T_WENT_VIRAL = 56,              /* T_WENT_VIRAL  */
  YYSYMBOL_T_REACHED = 57,                 /* T_REACHED  */
  YYSYMBOL_T_EXCEEDED = 58,                /* T_EXCEEDED  */
  YYSYMBOL_T_DROPPED_BELOW = 59,           /* T_DROPPED_BELOW  */
  YYSYMBOL_T_STAYED_AT = 60,               /* T_STAYED_AT  */
  YYSYMBOL_T_MORE_THAN = 61,               /* T_MORE_THAN  */
  YYSYMBOL_T_LESS_THAN = 62,               /* T_LESS_THAN  */
  YYSYMBOL_T_EXACTLY = 63,                 /* T_EXACTLY  */
  YYSYMBOL_T_AT_LEAST = 64,                /* T_AT_LEAST  */
  YYSYMBOL_T_AT_MOST = 65,                 /* T_AT_MOST  */
  YYSYMBOL_T_DIFFERENT_FROM = 66,          /* T_DIFFERENT_FROM  */
  YYSYMBOL_T_EQUAL_TO = 67,                /* T_EQUAL_TO  */
  YYSYMBOL_T_NOT_EQUAL_TO = 68,            /* T_NOT_EQUAL_TO  */
  YYSYMBOL_T_EVERY_DAY_FOR = 69,           /* T_EVERY_DAY_FOR  */
  YYSYMBOL_T_EVERY = 70,                   /* T_EVERY  */
  YYSYMBOL_T_DAYS = 71,                    /* T_DAYS  */
  YYSYMBOL_T_INCREMENTING_BY = 72,         /* T_INCREMENTING_BY  */
  YYSYMBOL_T_DECREMENTING_BY = 73,         /* T_DECREMENTING_BY  */
  YYSYMBOL_T_FOR_EACH = 74,                /* T_FOR_EACH  */
  YYSYMBOL_T_POST_IN = 75,                 /* T_POST_IN  */
  YYSYMBOL_T_STORY_IN = 76,                /* T_STORY_IN  */
  YYSYMBOL_T_FOLLOWER_FROM = 77,           /* T_FOLLOWER_FROM  */
  YYSYMBOL_T_TO = 78,                      /* T_TO  */
  YYSYMBOL_T_TRENDING_LOOP = 79,           /* T_TRENDING_LOOP  */
  YYSYMBOL_T_UNTIL = 80,                   /* T_UNTIL  */
  YYSYMBOL_T_STOP_THE_STORY = 81,          /* T_STOP_THE_STORY  */
  YYSYMBOL_T_SKIP_THIS_POST = 82,          /* T_SKIP_THIS_POST  */
  YYSYMBOL_T_THE_STORY_OF = 83,            /* T_THE_STORY_OF  */
  YYSYMBOL_T_BEGINS_WITH = 84,             /* T_BEGINS_WITH  */
  YYSYMBOL_T_TELL_BACK = 85,               /* T_TELL_BACK  */
  YYSYMBOL_T_THE_STORY_ENDS = 86,          /* T_THE_STORY_ENDS  */
  YYSYMBOL_T_TELL = 87,                    /* T_TELL  */
  YYSYMBOL_T_ANNOUNCE = 88,                /* T_ANNOUNCE  */
  YYSYMBOL_T_ASK_FOR = 89,                 /* T_ASK_FOR  */
  YYSYMBOL_T_DISPLAY = 90,                 /* T_DISPLAY  */
  YYSYMBOL_T_CALCULATE_VIRALITY = 91,      /* T_CALCULATE_VIRALITY  */
  YYSYMBOL_T_CALCULATE_ENGAGEMENT = 92,    /* T_CALCULATE_ENGAGEMENT  */
  YYSYMBOL_T_FIND_TOP_POST = 93,           /* T_FIND_TOP_POST  */
  YYSYMBOL_T_FIND_HIGHEST_REACH = 94,      /* T_FIND_HIGHEST_REACH  */
  YYSYMBOL_T_FIND_TOTAL_REACH = 95,        /* T_FIND_TOTAL_REACH  */
  YYSYMBOL_T_COUNT_TOTAL_ENGAGEMENT = 96,  /* T_COUNT_TOTAL_ENGAGEMENT  */
  YYSYMBOL_T_CHECK_IF_TRENDING = 97,       /* T_CHECK_IF_TRENDING  */
  YYSYMBOL_T_ANALYZE_GROWTH = 98,          /* T_ANALYZE_GROWTH  */
  YYSYMBOL_T_FIND_MAX_VIRAL_ACCOUNT = 99,  /* T_FIND_MAX_VIRAL_ACCOUNT  */
  YYSYMBOL_T_REVERSE_THE_CAPTION = 100,    /* T_REVERSE_THE_CAPTION  */
  YYSYMBOL_T_DETECT_SPAM = 101,            /* T_DETECT_SPAM  */
  YYSYMBOL_T_CLAMP_ENGAGEMENT = 102,       /* T_CLAMP_ENGAGEMENT  */
  YYSYMBOL_T_BETWEEN = 103,                /* T_BETWEEN  */
  YYSYMBOL_T_REVERSE_GROWTH = 104,         /* T_REVERSE_GROWTH  */
  YYSYMBOL_T_ALSO = 105,                   /* T_ALSO  */
  YYSYMBOL_T_EITHER = 106,                 /* T_EITHER  */
  YYSYMBOL_T_OPPOSITE = 107,               /* T_OPPOSITE  */
  YYSYMBOL_T_LPAREN = 108,                 /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 109,                 /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 110,                 /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 111,                 /* T_RBRACE  */
  YYSYMBOL_T_LBRACKET = 112,               /* T_LBRACKET  */
  YYSYMBOL_T_RBRACKET = 113,               /* T_RBRACKET  */
  YYSYMBOL_T_COMMA = 114,                  /* T_COMMA  */
  YYSYMBOL_T_DOT = 115,                    /* T_DOT  */
  YYSYMBOL_T_COLON = 116,                  /* T_COLON  */
  YYSYMBOL_T_NUMBER = 117,                 /* T_NUMBER  */
  YYSYMBOL_T_DECIMAL = 118,                /* T_DECIMAL  */
  YYSYMBOL_T_TEXT = 119,                   /* T_TEXT  */
  YYSYMBOL_T_ID = 120,                     /* T_ID  */
  YYSYMBOL_T_CHAR = 121,                   /* T_CHAR  */
  YYSYMBOL_T_TRUE_STORY = 122,             /* T_TRUE_STORY  */
  YYSYMBOL_T_FALSE_ALARM = 123,            /* T_FALSE_ALARM  */
  YYSYMBOL_YYACCEPT = 124,                 /* $accept  */
  YYSYMBOL_program = 125,                  /* program  */
  YYSYMBOL_statements = 126,               /* statements  */
  YYSYMBOL_statement = 127,                /* statement  */
  YYSYMBOL_account_create = 128,           /* account_create  */
  YYSYMBOL_account_init = 129,             /* account_init  */
  YYSYMBOL_account_update = 130,           /* account_update  */
  YYSYMBOL_story_post = 131,               /* story_post  */
  YYSYMBOL_conditional = 132,              /* conditional  */
  YYSYMBOL_optional_else = 133,            /* optional_else  */
  YYSYMBOL_else_if_chain = 134,            /* else_if_chain  */
  YYSYMBOL_loop = 135,                     /* loop  */
  YYSYMBOL_loop_control = 136,             /* loop_control  */
  YYSYMBOL_function_def = 137,             /* function_def  */
  YYSYMBOL_function_call = 138,            /* function_call  */
  YYSYMBOL_builtin_call = 139,             /* builtin_call  */
  YYSYMBOL_io_statement = 140,             /* io_statement  */
  YYSYMBOL_expression = 141,               /* expression  */
  YYSYMBOL_term = 142,                     /* term  */
  YYSYMBOL_factor = 143,                   /* factor  */
  YYSYMBOL_comparison = 144,               /* comparison  */
  YYSYMBOL_metric = 145,                   /* metric  */
  YYSYMBOL_literal = 146                   /* literal  */
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
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   590

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  124
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   378


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
     115,   116,   117,   118,   119,   120,   121,   122,   123
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   187,   187,   194,   204,   215,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   243,   254,
     263,   272,   284,   293,   302,   311,   323,   336,   347,   348,
     352,   356,   368,   375,   383,   391,   399,   409,   414,   423,
     435,   445,   451,   459,   465,   471,   477,   487,   493,   499,
     509,   514,   519,   523,   528,   533,   538,   542,   543,   544,
     549,   554,   559,   564,   569,   574,   579,   584,   589,   594,
     600,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     618,   623,   624,   625,   626,   627
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
  "T_DIVIDE", "T_MODULO", "T_WITH", "T_AND_THEN", "T_THE_FEED",
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
  "T_FALSE_ALARM", "$accept", "program", "statements", "statement",
  "account_create", "account_init", "account_update", "story_post",
  "conditional", "optional_else", "else_if_chain", "loop", "loop_control",
  "function_def", "function_call", "builtin_call", "io_statement",
  "expression", "term", "factor", "comparison", "metric", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,   339,    12,   -84,   -76,   -78,   424,   -66,   -65,   -43,
     -42,   -40,   -48,   -44,   -41,   -34,   -24,   -86,    39,   -86,
     -86,   -86,   -86,   366,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -36,   -20,   -86,   -86,   -86,   -86,     4,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,
     467,   -86,   -86,   -86,   -13,   -86,   -86,   -18,    -9,   -86,
      -7,   -86,   -86,    34,    36,    69,    -5,   -86,   -86,    26,
       9,     3,    11,    13,    10,    14,   -86,   -86,   -86,    19,
     123,    21,    23,    22,    25,    27,    28,    29,   -86,   -29,
     467,   467,   -86,   467,   467,   467,   467,   467,   467,   467,
     467,   467,   467,   467,   409,    35,   -64,    38,    72,    31,
     467,   -86,   -86,   -86,    41,   -86,   -86,    42,   477,   477,
     477,   477,   477,   477,   477,   -86,    -9,    -9,    18,    18,
      18,    18,    18,    18,    18,    18,   -86,   -86,   -86,     0,
      43,    40,    45,   409,    57,    48,   -25,    61,   147,    64,
      65,    66,    68,    74,    82,    83,   -32,   409,    77,    89,
      32,    90,   409,   -86,   -86,    91,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   424,    97,   -86,   -86,   103,   409,   409,
     -86,   409,   135,   166,   102,   409,   -86,   162,   205,   237,
     127,   104,   409,   264,   -86,   -86,   -86,   105,   -86,   307,
     -86,   -86,   -32,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,    43,
      46,    44,    45,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,    16,     1,    17,     3,     0,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,    81,    82,    83,    59,    84,    85,     0,    52,    56,
       0,    60,    58,     0,     0,     0,     0,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     4,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
       0,     0,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    47,    49,    48,     0,     2,    18,     0,     0,     0,
       0,     0,     0,     0,     0,    57,    50,    51,    67,    68,
      61,    62,    63,    64,    65,    66,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,     0,     0,
       0,     0,     0,    40,    42,     0,    19,    20,    21,    22,
      23,    24,    25,     0,     0,    27,    30,     0,     0,     0,
      36,     0,     0,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,     0,    33,    34,    35,     0,    26,     0,
      29,    39,    28,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,   -10,   -23,   -86,   -86,   -86,   -86,   -86,    37,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -39,   -55,   -85,
      56,   -56,   -86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    23,    24,    25,    26,    27,    28,    29,   175,
     176,    30,    31,    32,    33,    34,    35,    57,    58,    59,
      60,    61,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,     3,    90,    91,     1,     5,    90,    91,   141,   142,
      79,    89,    36,    90,    91,    80,   136,   137,   138,    81,
      82,    83,   173,   174,   101,    84,    85,   102,   103,    86,
      87,    37,    65,     3,    66,   126,   127,     5,    92,    38,
      93,    94,    39,    95,    96,    97,    98,    99,   100,    90,
      91,    63,    64,     6,   128,   129,   130,   131,   132,   133,
     134,   135,   149,   150,   151,   152,   153,   154,   155,     7,
       8,   146,    69,    67,     9,    68,    70,    74,    71,    77,
     125,    10,    11,    12,   163,     6,    72,    13,    14,    15,
      16,    17,    18,    19,   139,    78,    73,   -70,    20,    21,
      22,     7,     8,   104,     3,   105,     9,   106,     5,   107,
     109,   156,   108,    10,    11,    12,    76,   110,   111,    13,
      14,    15,    16,    17,    18,    19,   112,   114,   113,   115,
      20,    21,    22,   160,   116,   117,     3,    76,   118,   120,
       5,   119,   121,   180,   122,   123,   124,   177,   143,   140,
     144,   145,   182,   157,    76,   147,     6,   158,   162,    76,
     165,   148,   159,     3,    76,    76,    76,     5,   187,   188,
      76,   189,     7,     8,   161,   193,    76,     9,   164,   166,
     167,   168,   199,   169,    10,    11,    12,   178,     6,   170,
      13,    14,    15,    16,    17,    18,    19,   171,   172,   179,
     181,    20,    21,    22,     7,     8,     3,   185,   183,     9,
       5,   191,   192,   197,   186,     6,    10,    11,    12,   198,
     201,     0,    13,    14,    15,    16,    17,    18,    19,   184,
       0,     7,     8,    20,    21,    22,     9,     0,     3,   203,
       0,     0,     5,    10,    11,    12,   190,     0,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     6,     0,
      20,    21,    22,     0,     0,     3,     0,     0,     0,     5,
       0,     0,     0,   194,     7,     8,     0,     0,     0,     9,
       0,     0,     0,     0,     0,     0,    10,    11,    12,     0,
       6,     0,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,    20,    21,    22,     7,     8,     3,     0,
       0,     9,     5,     0,     0,     0,   195,     6,    10,    11,
      12,     0,     0,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     7,     8,    20,    21,    22,     9,     0,
       3,     0,     0,     4,     5,    10,    11,    12,   196,     0,
       0,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       6,     0,    20,    21,    22,     0,     0,     3,     0,     0,
      75,     5,     0,     0,     0,   200,     7,     8,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,    10,    11,
      12,     0,     6,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,    20,    21,    22,     7,     8,
       3,     0,     0,     9,     5,     0,     0,     0,   202,     6,
      10,    11,    12,     0,     0,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     7,     8,    20,    21,    22,
       9,     0,     0,     0,     0,     0,     0,    10,    11,    12,
       0,     0,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     6,     0,    20,    21,    22,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,     0,     7,     8,
       0,     0,     0,     9,     0,     0,     0,     0,     0,     0,
      10,    11,    12,     0,     0,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,    20,    21,    22,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    88,     0,    55,
      56
};

static const yytype_int16 yycheck[] =
{
      23,     1,    31,    32,     3,     5,    31,    32,    72,    73,
       6,    50,     0,    31,    32,    11,   101,   102,   103,    15,
      16,    17,    54,    55,    33,    21,    22,    36,    37,    25,
      26,   115,    75,     1,    77,    90,    91,     5,    56,   115,
      58,    59,   120,    61,    62,    63,    64,    65,    66,    31,
      32,   117,   117,    53,    93,    94,    95,    96,    97,    98,
      99,   100,   118,   119,   120,   121,   122,   123,   124,    69,
      70,   110,   120,   115,    74,   115,   120,    38,   119,   115,
     109,    81,    82,    83,   109,    53,   120,    87,    88,    89,
      90,    91,    92,    93,   104,   115,   120,   110,    98,    99,
     100,    69,    70,   110,     1,    71,    74,    71,     5,    40,
      84,   111,   117,    81,    82,    83,   139,   108,   115,    87,
      88,    89,    90,    91,    92,    93,   115,   117,   115,   115,
      98,    99,   100,   143,   115,    12,     1,   160,   117,   117,
       5,   118,   117,   111,   117,   117,   117,   157,   110,   114,
      78,   120,   162,   110,   177,   114,    53,   117,   110,   182,
      13,   119,   117,     1,   187,   188,   189,     5,   178,   179,
     193,   181,    69,    70,   117,   185,   199,    74,   117,   115,
     115,   115,   192,   115,    81,    82,    83,   110,    53,   115,
      87,    88,    89,    90,    91,    92,    93,   115,   115,   110,
     110,    98,    99,   100,    69,    70,     1,   110,   117,    74,
       5,    45,   110,    86,   111,    53,    81,    82,    83,   115,
     115,    -1,    87,    88,    89,    90,    91,    92,    93,   173,
      -1,    69,    70,    98,    99,   100,    74,    -1,     1,   202,
      -1,    -1,     5,    81,    82,    83,   111,    -1,    -1,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    53,    -1,
      98,    99,   100,    -1,    -1,     1,    -1,    -1,    -1,     5,
      -1,    -1,    -1,   111,    69,    70,    -1,    -1,    -1,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    -1,
      53,    -1,    87,    88,    89,    90,    91,    92,    93,    -1,
      -1,    -1,    -1,    98,    99,   100,    69,    70,     1,    -1,
      -1,    74,     5,    -1,    -1,    -1,   111,    53,    81,    82,
      83,    -1,    -1,    -1,    87,    88,    89,    90,    91,    92,
      93,    -1,    -1,    69,    70,    98,    99,   100,    74,    -1,
       1,    -1,    -1,     4,     5,    81,    82,    83,   111,    -1,
      -1,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      53,    -1,    98,    99,   100,    -1,    -1,     1,    -1,    -1,
       4,     5,    -1,    -1,    -1,   111,    69,    70,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    -1,    53,    -1,    87,    88,    89,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    98,    99,   100,    69,    70,
       1,    -1,    -1,    74,     5,    -1,    -1,    -1,   111,    53,
      81,    82,    83,    -1,    -1,    -1,    87,    88,    89,    90,
      91,    92,    93,    -1,    -1,    69,    70,    98,    99,   100,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      -1,    -1,    -1,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    53,    -1,    98,    99,   100,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    69,    70,
      -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    -1,    -1,    -1,    87,    88,    89,    90,
      91,    92,    93,    -1,    -1,    -1,    -1,    98,    99,   100,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,    -1,   122,   123,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,    -1,   122,
     123
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   125,     1,     4,     5,    53,    69,    70,    74,
      81,    82,    83,    87,    88,    89,    90,    91,    92,    93,
      98,    99,   100,   126,   127,   128,   129,   130,   131,   132,
     135,   136,   137,   138,   139,   140,     0,   115,   115,   120,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
     108,   117,   118,   119,   120,   122,   123,   141,   142,   143,
     144,   145,   146,   117,   117,    75,    77,   115,   115,   120,
     120,   119,   120,   120,    38,     4,   127,   115,   115,     6,
      11,    15,    16,    17,    21,    22,    25,    26,   120,   141,
      31,    32,    56,    58,    59,    61,    62,    63,    64,    65,
      66,    33,    36,    37,   110,    71,    71,    40,   117,    84,
     108,   115,   115,   115,   117,   115,   115,    12,   117,   118,
     117,   117,   117,   117,   117,   109,   142,   142,   141,   141,
     141,   141,   141,   141,   141,   141,   143,   143,   143,   126,
     114,    72,    73,   110,    78,   120,   141,   114,   119,   145,
     145,   145,   145,   145,   145,   145,   111,   110,   117,   117,
     126,   117,   110,   109,   117,    13,   115,   115,   115,   115,
     115,   115,   115,    54,    55,   133,   134,   126,   110,   110,
     111,   110,   126,   117,   144,   110,   111,   126,   126,   126,
     111,    45,   110,   126,   111,   111,   111,    86,   115,   126,
     111,   115,   111,   133
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   124,   125,   125,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   128,   129,
     129,   129,   130,   130,   130,   130,   131,   132,   133,   133,
     133,   134,   135,   135,   135,   135,   135,   136,   136,   137,
     138,   139,   139,   139,   139,   139,   139,   140,   140,   140,
     141,   141,   141,   142,   142,   142,   142,   143,   143,   143,
     143,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   146,   146,   146,   146,   146
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     4,     6,
       6,     6,     6,     6,     6,     6,     9,     6,     0,     4,
       1,     6,     7,     8,     8,     8,     6,     2,     2,     9,
       5,     1,     5,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
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
  case 2: /* program: T_GO_LIVE statements T_END_LIVE T_DOT  */
#line 188 "socialstory_parser.y"
    {
        ast_root = make_node(AST_PROGRAM);
        ast_root->body = (yyvsp[-2].node);
        (yyval.node) = ast_root;
        printf("\n✅ Parse successful! AST built.\n");
    }
#line 1563 "socialstory_parser.tab.c"
    break;

  case 3: /* program: T_GO_LIVE T_END_LIVE T_DOT  */
#line 195 "socialstory_parser.y"
    {
        ast_root = make_node(AST_PROGRAM);
        ast_root->body = NULL;
        (yyval.node) = ast_root;
        printf("\n✅ Parse successful! Empty program.\n");
    }
#line 1574 "socialstory_parser.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 205 "socialstory_parser.y"
    {
        if ((yyvsp[-1].node) == NULL) {
            (yyval.node) = (yyvsp[0].node);
        } else {
            ASTNode* temp = (yyvsp[-1].node);
            while (temp->next != NULL) temp = temp->next;
            temp->next = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
    }
#line 1589 "socialstory_parser.tab.c"
    break;

  case 5: /* statements: statement  */
#line 216 "socialstory_parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1597 "socialstory_parser.tab.c"
    break;

  case 6: /* statement: account_create  */
#line 222 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1603 "socialstory_parser.tab.c"
    break;

  case 7: /* statement: account_init  */
#line 223 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1609 "socialstory_parser.tab.c"
    break;

  case 8: /* statement: account_update  */
#line 224 "socialstory_parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1615 "socialstory_parser.tab.c"
    break;

  case 9: /* statement: story_post  */
#line 225 "socialstory_parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1621 "socialstory_parser.tab.c"
    break;

  case 10: /* statement: conditional  */
#line 226 "socialstory_parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1627 "socialstory_parser.tab.c"
    break;

  case 11: /* statement: loop  */
#line 227 "socialstory_parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1633 "socialstory_parser.tab.c"
    break;

  case 12: /* statement: loop_control  */
#line 228 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1639 "socialstory_parser.tab.c"
    break;

  case 13: /* statement: function_def  */
#line 229 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1645 "socialstory_parser.tab.c"
    break;

  case 14: /* statement: function_call T_DOT  */
#line 230 "socialstory_parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 1651 "socialstory_parser.tab.c"
    break;

  case 15: /* statement: builtin_call T_DOT  */
#line 231 "socialstory_parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1657 "socialstory_parser.tab.c"
    break;

  case 16: /* statement: io_statement  */
#line 232 "socialstory_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1663 "socialstory_parser.tab.c"
    break;

  case 17: /* statement: error T_DOT  */
#line 234 "socialstory_parser.y"
    {
        yyerror("Invalid statement - skipping to next");
        yyerrok;
        (yyval.node) = NULL;
    }
#line 1673 "socialstory_parser.tab.c"
    break;

  case 18: /* account_create: T_THE_ACCOUNT T_ID T_WAS_CREATED T_DOT  */
#line 244 "socialstory_parser.y"
    {
        check_duplicate_account((yyvsp[-2].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_CREATE);
        (yyval.node)->sval = (yyvsp[-2].sval);
        (yyval.node)->line_number = yylineno;
        insert_symbol((yyvsp[-2].sval), SYM_ACCOUNT);
    }
#line 1685 "socialstory_parser.tab.c"
    break;

  case 19: /* account_init: T_THE_ACCOUNT T_ID T_STARTED_WITH T_NUMBER metric T_DOT  */
#line 255 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1698 "socialstory_parser.tab.c"
    break;

  case 20: /* account_init: T_THE_ACCOUNT T_ID T_BEGAN_AT T_DECIMAL metric T_DOT  */
#line 264 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->fval = (yyvsp[-2].fval);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1711 "socialstory_parser.tab.c"
    break;

  case 21: /* account_init: T_THE_ACCOUNT T_ID T_NOW_HAS T_NUMBER metric T_DOT  */
#line 273 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_INIT);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1724 "socialstory_parser.tab.c"
    break;

  case 22: /* account_update: T_THE_ACCOUNT T_ID T_GAINED T_NUMBER metric T_DOT  */
#line 285 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1737 "socialstory_parser.tab.c"
    break;

  case 23: /* account_update: T_THE_ACCOUNT T_ID T_LOST T_NUMBER metric T_DOT  */
#line 294 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = -(yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1750 "socialstory_parser.tab.c"
    break;

  case 24: /* account_update: T_THE_ACCOUNT T_ID T_INCREASED_BY T_NUMBER metric T_DOT  */
#line 303 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1763 "socialstory_parser.tab.c"
    break;

  case 25: /* account_update: T_THE_ACCOUNT T_ID T_DECREASED_BY T_NUMBER metric T_DOT  */
#line 312 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-4].sval), yylineno);
        (yyval.node) = make_node(AST_ACCOUNT_UPDATE);
        (yyval.node)->sval = (yyvsp[-4].sval);
        (yyval.node)->ival = -(yyvsp[-2].ival);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1776 "socialstory_parser.tab.c"
    break;

  case 26: /* story_post: T_THE_ACCOUNT T_ID T_POSTED T_ABOUT T_TEXT T_THAT_HAD T_NUMBER T_VIEWS T_DOT  */
#line 324 "socialstory_parser.y"
    {
        check_account_exists((yyvsp[-7].sval), yylineno);
        (yyval.node) = make_node(AST_STORY_POST);
        (yyval.node)->sval = (yyvsp[-7].sval);
        (yyval.node)->left = make_node_with_string(AST_LITERAL_STRING, (yyvsp[-4].sval));
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->line_number = yylineno;
    }
#line 1789 "socialstory_parser.tab.c"
    break;

  case 27: /* conditional: T_WHEN comparison T_LBRACE statements T_RBRACE optional_else  */
#line 337 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONDITIONAL);
        (yyval.node)->condition = (yyvsp[-4].node);
        (yyval.node)->body = (yyvsp[-2].node);
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1801 "socialstory_parser.tab.c"
    break;

  case 28: /* optional_else: %empty  */
#line 347 "socialstory_parser.y"
                { (yyval.node) = NULL; }
#line 1807 "socialstory_parser.tab.c"
    break;

  case 29: /* optional_else: T_OTHERWISE T_LBRACE statements T_RBRACE  */
#line 349 "socialstory_parser.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1815 "socialstory_parser.tab.c"
    break;

  case 30: /* optional_else: else_if_chain  */
#line 352 "socialstory_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1821 "socialstory_parser.tab.c"
    break;

  case 31: /* else_if_chain: T_OTHERWISE_IF comparison T_LBRACE statements T_RBRACE optional_else  */
#line 357 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONDITIONAL);
        (yyval.node)->condition = (yyvsp[-4].node);
        (yyval.node)->body = (yyvsp[-2].node);
        (yyval.node)->else_body = (yyvsp[0].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1833 "socialstory_parser.tab.c"
    break;

  case 32: /* loop: T_EVERY_DAY_FOR T_NUMBER T_DAYS T_COMMA T_LBRACE statements T_RBRACE  */
#line 369 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP);
        (yyval.node)->ival = (yyvsp[-5].ival);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1844 "socialstory_parser.tab.c"
    break;

  case 33: /* loop: T_EVERY T_NUMBER T_DAYS T_INCREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE  */
#line 376 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_INCREMENT);
        (yyval.node)->ival = (yyvsp[-6].ival);
        (yyval.node)->fval = (float)(yyvsp[-3].ival);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1856 "socialstory_parser.tab.c"
    break;

  case 34: /* loop: T_EVERY T_NUMBER T_DAYS T_DECREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE  */
#line 384 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_DECREMENT);
        (yyval.node)->ival = (yyvsp[-6].ival);
        (yyval.node)->fval = (float)(yyvsp[-3].ival);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1868 "socialstory_parser.tab.c"
    break;

  case 35: /* loop: T_FOR_EACH T_FOLLOWER_FROM T_NUMBER T_TO T_NUMBER T_LBRACE statements T_RBRACE  */
#line 392 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_RANGE);
        (yyval.node)->ival = (yyvsp[-5].ival);
        (yyval.node)->fval = (float)(yyvsp[-3].ival);
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1880 "socialstory_parser.tab.c"
    break;

  case 36: /* loop: T_FOR_EACH T_POST_IN T_THE_FEED T_LBRACE statements T_RBRACE  */
#line 400 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_LOOP_COLLECTION);
        (yyval.node)->sval = strdup("posts");
        (yyval.node)->body = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1891 "socialstory_parser.tab.c"
    break;

  case 37: /* loop_control: T_STOP_THE_STORY T_DOT  */
#line 410 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BREAK);
        (yyval.node)->line_number = yylineno;
    }
#line 1900 "socialstory_parser.tab.c"
    break;

  case 38: /* loop_control: T_SKIP_THIS_POST T_DOT  */
#line 415 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_CONTINUE);
        (yyval.node)->line_number = yylineno;
    }
#line 1909 "socialstory_parser.tab.c"
    break;

  case 39: /* function_def: T_THE_STORY_OF T_ID T_BEGINS_WITH T_ID T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT  */
#line 424 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_DEF);
        (yyval.node)->sval = (yyvsp[-7].sval);
        (yyval.node)->left = make_node_with_string(AST_IDENTIFIER, (yyvsp[-5].sval));
        (yyval.node)->body = (yyvsp[-3].node);
        (yyval.node)->line_number = yylineno;
        insert_symbol((yyvsp[-7].sval), SYM_FUNCTION);
    }
#line 1922 "socialstory_parser.tab.c"
    break;

  case 40: /* function_call: T_TELL T_ID T_LPAREN expression T_RPAREN  */
#line 436 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_FUNCTION_CALL);
        (yyval.node)->sval = (yyvsp[-3].sval);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->line_number = yylineno;
    }
#line 1933 "socialstory_parser.tab.c"
    break;

  case 41: /* builtin_call: T_CALCULATE_VIRALITY  */
#line 446 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("calculate_virality");
        (yyval.node)->line_number = yylineno;
    }
#line 1943 "socialstory_parser.tab.c"
    break;

  case 42: /* builtin_call: T_CALCULATE_ENGAGEMENT T_WITH T_NUMBER T_COMMA T_NUMBER  */
#line 452 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("calculate_engagement");
        (yyval.node)->ival = (yyvsp[-2].ival);
        (yyval.node)->fval = (float)(yyvsp[0].ival);
        (yyval.node)->line_number = yylineno;
    }
#line 1955 "socialstory_parser.tab.c"
    break;

  case 43: /* builtin_call: T_FIND_TOP_POST  */
#line 460 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_top_post");
        (yyval.node)->line_number = yylineno;
    }
#line 1965 "socialstory_parser.tab.c"
    break;

  case 44: /* builtin_call: T_FIND_MAX_VIRAL_ACCOUNT  */
#line 466 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("find_max_viral_account");
        (yyval.node)->line_number = yylineno;
    }
#line 1975 "socialstory_parser.tab.c"
    break;

  case 45: /* builtin_call: T_REVERSE_THE_CAPTION  */
#line 472 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("reverse_caption");
        (yyval.node)->line_number = yylineno;
    }
#line 1985 "socialstory_parser.tab.c"
    break;

  case 46: /* builtin_call: T_ANALYZE_GROWTH  */
#line 478 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_BUILTIN_CALL);
        (yyval.node)->sval = strdup("analyze_growth");
        (yyval.node)->line_number = yylineno;
    }
#line 1995 "socialstory_parser.tab.c"
    break;

  case 47: /* io_statement: T_ANNOUNCE T_TEXT T_DOT  */
#line 488 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ANNOUNCE);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2005 "socialstory_parser.tab.c"
    break;

  case 48: /* io_statement: T_DISPLAY T_ID T_DOT  */
#line 494 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_DISPLAY);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2015 "socialstory_parser.tab.c"
    break;

  case 49: /* io_statement: T_ASK_FOR T_ID T_DOT  */
#line 500 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_ASK_FOR);
        (yyval.node)->sval = (yyvsp[-1].sval);
        (yyval.node)->line_number = yylineno;
    }
#line 2025 "socialstory_parser.tab.c"
    break;

  case 50: /* expression: expression T_PLUS term  */
#line 510 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '+';
    }
#line 2034 "socialstory_parser.tab.c"
    break;

  case 51: /* expression: expression T_MINUS term  */
#line 515 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '-';
    }
#line 2043 "socialstory_parser.tab.c"
    break;

  case 52: /* expression: term  */
#line 519 "socialstory_parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2049 "socialstory_parser.tab.c"
    break;

  case 53: /* term: term T_TIMES factor  */
#line 524 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '*';
    }
#line 2058 "socialstory_parser.tab.c"
    break;

  case 54: /* term: term T_DIVIDE factor  */
#line 529 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '/';
    }
#line 2067 "socialstory_parser.tab.c"
    break;

  case 55: /* term: term T_MODULO factor  */
#line 534 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_BINARY_OP, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '%';
    }
#line 2076 "socialstory_parser.tab.c"
    break;

  case 56: /* term: factor  */
#line 538 "socialstory_parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2082 "socialstory_parser.tab.c"
    break;

  case 57: /* factor: T_LPAREN expression T_RPAREN  */
#line 542 "socialstory_parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2088 "socialstory_parser.tab.c"
    break;

  case 58: /* factor: literal  */
#line 543 "socialstory_parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2094 "socialstory_parser.tab.c"
    break;

  case 59: /* factor: T_ID  */
#line 545 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_IDENTIFIER);
        (yyval.node)->sval = (yyvsp[0].sval);
    }
#line 2103 "socialstory_parser.tab.c"
    break;

  case 60: /* factor: metric  */
#line 549 "socialstory_parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2109 "socialstory_parser.tab.c"
    break;

  case 61: /* comparison: expression T_MORE_THAN expression  */
#line 555 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '>';
    }
#line 2118 "socialstory_parser.tab.c"
    break;

  case 62: /* comparison: expression T_LESS_THAN expression  */
#line 560 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '<';
    }
#line 2127 "socialstory_parser.tab.c"
    break;

  case 63: /* comparison: expression T_EXACTLY expression  */
#line 565 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '=';
    }
#line 2136 "socialstory_parser.tab.c"
    break;

  case 64: /* comparison: expression T_AT_LEAST expression  */
#line 570 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = 'G';
    }
#line 2145 "socialstory_parser.tab.c"
    break;

  case 65: /* comparison: expression T_AT_MOST expression  */
#line 575 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = 'L';
    }
#line 2154 "socialstory_parser.tab.c"
    break;

  case 66: /* comparison: expression T_DIFFERENT_FROM expression  */
#line 580 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '!';
    }
#line 2163 "socialstory_parser.tab.c"
    break;

  case 67: /* comparison: expression T_EXCEEDED expression  */
#line 585 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '>';
    }
#line 2172 "socialstory_parser.tab.c"
    break;

  case 68: /* comparison: expression T_DROPPED_BELOW expression  */
#line 590 "socialstory_parser.y"
    {
        (yyval.node) = make_binary_op(AST_COMPARISON, (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->ival = '<';
    }
#line 2181 "socialstory_parser.tab.c"
    break;

  case 69: /* comparison: expression T_WENT_VIRAL  */
#line 595 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_COMPARISON);
        (yyval.node)->left = (yyvsp[-1].node);
        (yyval.node)->ival = 'V';
    }
#line 2191 "socialstory_parser.tab.c"
    break;

  case 70: /* comparison: T_ID  */
#line 601 "socialstory_parser.y"
    {
        (yyval.node) = make_node(AST_IDENTIFIER);
        (yyval.node)->sval = (yyvsp[0].sval);
    }
#line 2200 "socialstory_parser.tab.c"
    break;

  case 71: /* metric: T_LIKES  */
#line 609 "socialstory_parser.y"
            { (yyval.node) = make_node_with_string(AST_METRIC, strdup("likes")); }
#line 2206 "socialstory_parser.tab.c"
    break;

  case 72: /* metric: T_FOLLOWERS  */
#line 610 "socialstory_parser.y"
                  { (yyval.node) = make_node_with_string(AST_METRIC, strdup("followers")); }
#line 2212 "socialstory_parser.tab.c"
    break;

  case 73: /* metric: T_VIEWS  */
#line 611 "socialstory_parser.y"
              { (yyval.node) = make_node_with_string(AST_METRIC, strdup("views")); }
#line 2218 "socialstory_parser.tab.c"
    break;

  case 74: /* metric: T_COMMENTS  */
#line 612 "socialstory_parser.y"
                 { (yyval.node) = make_node_with_string(AST_METRIC, strdup("comments")); }
#line 2224 "socialstory_parser.tab.c"
    break;

  case 75: /* metric: T_SHARES  */
#line 613 "socialstory_parser.y"
               { (yyval.node) = make_node_with_string(AST_METRIC, strdup("shares")); }
#line 2230 "socialstory_parser.tab.c"
    break;

  case 76: /* metric: T_POSTS  */
#line 614 "socialstory_parser.y"
              { (yyval.node) = make_node_with_string(AST_METRIC, strdup("posts")); }
#line 2236 "socialstory_parser.tab.c"
    break;

  case 77: /* metric: T_STORIES  */
#line 615 "socialstory_parser.y"
                { (yyval.node) = make_node_with_string(AST_METRIC, strdup("stories")); }
#line 2242 "socialstory_parser.tab.c"
    break;

  case 78: /* metric: T_ENGAGEMENT_RATE  */
#line 616 "socialstory_parser.y"
                        { (yyval.node) = make_node_with_string(AST_METRIC, strdup("engagement_rate")); }
#line 2248 "socialstory_parser.tab.c"
    break;

  case 79: /* metric: T_REACH  */
#line 617 "socialstory_parser.y"
              { (yyval.node) = make_node_with_string(AST_METRIC, strdup("reach")); }
#line 2254 "socialstory_parser.tab.c"
    break;

  case 80: /* metric: T_GROWTH_RATE  */
#line 618 "socialstory_parser.y"
                    { (yyval.node) = make_node_with_string(AST_METRIC, strdup("growth_rate")); }
#line 2260 "socialstory_parser.tab.c"
    break;

  case 81: /* literal: T_NUMBER  */
#line 623 "socialstory_parser.y"
             { (yyval.node) = make_node_with_int(AST_LITERAL_INT, (yyvsp[0].ival)); }
#line 2266 "socialstory_parser.tab.c"
    break;

  case 82: /* literal: T_DECIMAL  */
#line 624 "socialstory_parser.y"
                { (yyval.node) = make_node_with_float(AST_LITERAL_FLOAT, (yyvsp[0].fval)); }
#line 2272 "socialstory_parser.tab.c"
    break;

  case 83: /* literal: T_TEXT  */
#line 625 "socialstory_parser.y"
             { (yyval.node) = make_node_with_string(AST_LITERAL_STRING, (yyvsp[0].sval)); }
#line 2278 "socialstory_parser.tab.c"
    break;

  case 84: /* literal: T_TRUE_STORY  */
#line 626 "socialstory_parser.y"
                   { (yyval.node) = make_node_with_int(AST_LITERAL_BOOL, 1); }
#line 2284 "socialstory_parser.tab.c"
    break;

  case 85: /* literal: T_FALSE_ALARM  */
#line 627 "socialstory_parser.y"
                    { (yyval.node) = make_node_with_int(AST_LITERAL_BOOL, 0); }
#line 2290 "socialstory_parser.tab.c"
    break;


#line 2294 "socialstory_parser.tab.c"

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

#line 630 "socialstory_parser.y"


/* Error handler */
void yyerror(const char *s) {
    fprintf(stderr, "❌ Syntax Error at line %d: %s\n", yylineno, s);
    semantic_errors++;
}

/* AST node creation functions */
ASTNode* make_node(ASTNodeType type) {
    ASTNode* node = (ASTNode*)calloc(1, sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->type = type;
    node->line_number = yylineno;
    return node;
}

ASTNode* make_node_with_int(ASTNodeType type, int value) {
    ASTNode* node = make_node(type);
    node->ival = value;
    return node;
}

ASTNode* make_node_with_float(ASTNodeType type, float value) {
    ASTNode* node = make_node(type);
    node->fval = value;
    return node;
}

ASTNode* make_node_with_string(ASTNodeType type, char* value) {
    ASTNode* node = make_node(type);
    node->sval = value;
    return node;
}

ASTNode* make_binary_op(ASTNodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = make_node(type);
    node->left = left;
    node->right = right;
    return node;
}

/* Symbol table functions */
SymbolEntry* lookup_symbol(const char* name) {
    SymbolEntry* current = symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

SymbolEntry* insert_symbol(const char* name, int sym_type) {
    SymbolEntry* entry = (SymbolEntry*)calloc(1, sizeof(SymbolEntry));
    if (!entry) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    entry->name = strdup(name);
    entry->type = sym_type;
    entry->next = symbol_table;
    symbol_table = entry;
    return entry;
}

void check_account_exists(const char* name, int line) {
    if (lookup_symbol(name) == NULL) {
        fprintf(stderr, "❌ Semantic Error (line %d): Account '%s' not declared\n", line, name);
        semantic_errors++;
    }
}

void check_duplicate_account(const char* name, int line) {
    if (lookup_symbol(name) != NULL) {
        fprintf(stderr, "❌ Semantic Error (line %d): Account '%s' already exists\n", line, name);
        semantic_errors++;
    }
}

void print_symbol_table() {
    printf("\n📋 Symbol Table:\n");
    printf("================\n");
    SymbolEntry* current = symbol_table;
    while (current != NULL) {
        printf("%-20s | Type: ", current->name);
        switch (current->type) {
            case SYM_ACCOUNT: printf("Account"); break;
            case SYM_VARIABLE: printf("Variable"); break;
            case SYM_FUNCTION: printf("Function"); break;
        }
        if (current->type == SYM_ACCOUNT) {
            printf(" | Likes: %d, Followers: %d", current->likes, current->followers);
        }
        printf("\n");
        current = current->next;
    }
    printf("================\n");
}

void free_symbol_table() {
    SymbolEntry* current = symbol_table;
    while (current != NULL) {
        SymbolEntry* temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
}

/* AST printing */
const char* node_type_name(ASTNodeType type) {
    switch (type) {
        case AST_PROGRAM: return "PROGRAM";
        case AST_ACCOUNT_CREATE: return "ACCOUNT_CREATE";
        case AST_ACCOUNT_INIT: return "ACCOUNT_INIT";
        case AST_ACCOUNT_UPDATE: return "ACCOUNT_UPDATE";
        case AST_STORY_POST: return "STORY_POST";
        case AST_CONDITIONAL: return "CONDITIONAL";
        case AST_LOOP: return "LOOP";
        case AST_LOOP_INCREMENT: return "LOOP_INCREMENT";
        case AST_LOOP_DECREMENT: return "LOOP_DECREMENT";
        case AST_LOOP_RANGE: return "LOOP_RANGE";
        case AST_LOOP_COLLECTION: return "LOOP_COLLECTION";
        case AST_FUNCTION_DEF: return "FUNCTION_DEF";
        case AST_FUNCTION_CALL: return "FUNCTION_CALL";
        case AST_BUILTIN_CALL: return "BUILTIN_CALL";
        case AST_ANNOUNCE: return "ANNOUNCE";
        case AST_DISPLAY: return "DISPLAY";
        case AST_ASK_FOR: return "ASK_FOR";
        case AST_BINARY_OP: return "BINARY_OP";
        case AST_COMPARISON: return "COMPARISON";
        case AST_LITERAL_INT: return "LITERAL_INT";
        case AST_LITERAL_FLOAT: return "LITERAL_FLOAT";
        case AST_LITERAL_STRING: return "LITERAL_STRING";
        case AST_LITERAL_BOOL: return "LITERAL_BOOL";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_METRIC: return "METRIC";
        case AST_BREAK: return "BREAK";
        case AST_CONTINUE: return "CONTINUE";
        default: return "UNKNOWN";
    }
}

void print_ast(ASTNode* node, int depth) {
    if (node == NULL) return;
    
    for (int i = 0; i < depth; i++) printf("  ");
    printf("├─ %s", node_type_name(node->type));
    
    if (node->sval) printf(" (%s)", node->sval);
    if (node->type == AST_LITERAL_INT) printf(" [%d]", node->ival);
    if (node->type == AST_LITERAL_FLOAT) printf(" [%.2f]", node->fval);
    if (node->type == AST_BINARY_OP) printf(" ['%c']", (char)node->ival);
    
    printf("\n");
    
    if (node->condition) {
        for (int i = 0; i < depth + 1; i++) printf("  ");
        printf("Condition:\n");
        print_ast(node->condition, depth + 2);
    }
    
    if (node->body) {
        for (int i = 0; i < depth + 1; i++) printf("  ");
        printf("Body:\n");
        print_ast(node->body, depth + 2);
    }
    
    if (node->else_body) {
        for (int i = 0; i < depth + 1; i++) printf("  ");
        printf("Else:\n");
        print_ast(node->else_body, depth + 2);
    }
    
    if (node->left) print_ast(node->left, depth + 1);
    if (node->right) print_ast(node->right, depth + 1);
    if (node->next) print_ast(node->next, depth);
}

void free_ast(ASTNode* node) {
    if (node == NULL) return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->condition);
    free_ast(node->body);
    free_ast(node->else_body);
    free_ast(node->next);
    if (node->sval) free(node->sval);
    free(node);
}

/* Interpreter */
int evaluate_expression(ASTNode* node) {
    if (node == NULL) return 0;
    
    switch (node->type) {
        case AST_LITERAL_INT:
            return node->ival;
        case AST_LITERAL_BOOL:
            return node->ival;
        case AST_BINARY_OP: {
            int left = evaluate_expression(node->left);
            int right = evaluate_expression(node->right);
            switch (node->ival) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return right != 0 ? left / right : 0;
                case '%': return right != 0 ? left % right : 0;
            }
        }
        case AST_COMPARISON: {
            int left = evaluate_expression(node->left);
            int right = evaluate_expression(node->right);
            switch (node->ival) {
                case '>': return left > right;
                case '<': return left < right;
                case '=': return left == right;
                case 'G': return left >= right;
                case 'L': return left <= right;
                case '!': return left != right;
                case 'V': return left > 1000;
            }
        }
        default:
            return 0;
    }
}

void execute(ASTNode* node) {
    if (node == NULL) return;
    
    switch (node->type) {
        case AST_PROGRAM:
            printf("\n🎬 Executing SocialStoryScript Program...\n");
            printf("==========================================\n");
            execute_statements(node->body);
            printf("==========================================\n");
            printf("✅ Program execution complete!\n");
            break;
            
        case AST_ACCOUNT_CREATE: {
            SymbolEntry* account = lookup_symbol(node->sval);
            if (account) {
                printf("✨ Created account: %s\n", node->sval);
            }
            break;
        }
            
        case AST_ACCOUNT_INIT: {
            SymbolEntry* account = lookup_symbol(node->sval);
            if (account && node->left && node->left->sval) {
                if (strcmp(node->left->sval, "likes") == 0) {
                    account->likes = node->ival;
                    printf("📊 %s started with %d likes\n", node->sval, node->ival);
                } else if (strcmp(node->left->sval, "followers") == 0) {
                    account->followers = node->ival;
                    printf("👥 %s started with %d followers\n", node->sval, node->ival);
                } else if (strcmp(node->left->sval, "views") == 0) {
                    account->views = node->ival;
                    printf("👁️  %s started with %d views\n", node->sval, node->ival);
                }
            }
            break;
        }
            
        case AST_ACCOUNT_UPDATE: {
            SymbolEntry* account = lookup_symbol(node->sval);
            if (account && node->left && node->left->sval) {
                if (strcmp(node->left->sval, "likes") == 0) {
                    account->likes += node->ival;
                    printf("❤️  %s %s %d likes (now: %d)\n", 
                           node->sval, 
                           node->ival > 0 ? "gained" : "lost", 
                           abs(node->ival), 
                           account->likes);
                } else if (strcmp(node->left->sval, "followers") == 0) {
                    account->followers += node->ival;
                    printf("👥 %s %s %d followers (now: %d)\n", 
                           node->sval, 
                           node->ival > 0 ? "gained" : "lost", 
                           abs(node->ival), 
                           account->followers);
                }
            }
            break;
        }
            
        case AST_STORY_POST:
            if (node->left && node->left->sval) {
                printf("📱 %s posted story: \"%s\" (%d views)\n", 
                       node->sval, node->left->sval, node->ival);
            }
            break;
            
        case AST_CONDITIONAL:
            if (evaluate_expression(node->condition)) {
                execute_statements(node->body);
            } else if (node->else_body) {
                execute(node->else_body);
            }
            break;
            
        case AST_LOOP:
            for (int i = 0; i < node->ival; i++) {
                execute_statements(node->body);
            }
            break;
            
        case AST_LOOP_INCREMENT:
            for (int i = 0; i < node->ival; i += (int)node->fval) {
                execute_statements(node->body);
            }
            break;
            
        case AST_ANNOUNCE:
            printf("📢 Announcement: %s\n", node->sval);
            break;
            
        case AST_DISPLAY: {
            SymbolEntry* sym = lookup_symbol(node->sval);
            if (sym && sym->type == SYM_ACCOUNT) {
                printf("📊 Account %s: Likes=%d, Followers=%d, Views=%d\n",
                       node->sval, sym->likes, sym->followers, sym->views);
            }
            break;
        }
            
        case AST_BUILTIN_CALL:
            if (strcmp(node->sval, "find_max_viral_account") == 0) {
                SymbolEntry* max = NULL;
                int max_score = 0;
                SymbolEntry* current = symbol_table;
                while (current != NULL) {
                    if (current->type == SYM_ACCOUNT) {
                        int score = current->likes + current->followers + current->views;
                        if (score > max_score) {
                            max_score = score;
                            max = current;
                        }
                    }
                    current = current->next;
                }
                if (max) {
                    printf("🏆 Most viral account: %s (score: %d)\n", max->name, max_score);
                }
            }
            break;
            
        default:
            break;
    }
}

void execute_statements(ASTNode* node) {
    while (node != NULL) {
        execute(node);
        node = node->next;
    }
}

/* Main function */
int main(int argc, char** argv) {
    FILE *input;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }
    
    yyin = input;
    
    printf("🚀 SocialStoryScript Compiler\n");
    printf("==============================\n");
    printf("Parsing: %s\n", argv[1]);
    printf("==============================\n\n");
    
    int parse_result = yyparse();
    
    if (parse_result == 0 && semantic_errors == 0) {
        printf("\n🌲 Abstract Syntax Tree:\n");
        print_ast(ast_root, 0);
        
        print_symbol_table();
        
        execute(ast_root);
        
        printf("\n✅ Compilation successful!\n");
        printf("   Lexical errors: %d\n", error_count);
        printf("   Syntax errors: 0\n");
        printf("   Semantic errors: %d\n", semantic_errors);
    } else {
        printf("\n❌ Compilation failed with errors.\n");
        printf("   Lexical errors: %d\n", error_count);
        printf("   Semantic errors: %d\n", semantic_errors);
    }
    
    free_ast(ast_root);
    free_symbol_table();
    fclose(input);
    
    return (parse_result == 0 && semantic_errors == 0) ? 0 : 1;
}
