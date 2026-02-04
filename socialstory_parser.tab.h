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

#ifndef YY_YY_SOCIALSTORY_PARSER_TAB_H_INCLUDED
# define YY_YY_SOCIALSTORY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    T_GO_LIVE = 258,               /* T_GO_LIVE  */
    T_END_LIVE = 259,              /* T_END_LIVE  */
    T_THE_ACCOUNT = 260,           /* T_THE_ACCOUNT  */
    T_WAS_CREATED = 261,           /* T_WAS_CREATED  */
    T_THE_POST = 262,              /* T_THE_POST  */
    T_THE_CAPTION = 263,           /* T_THE_CAPTION  */
    T_THE_FOLLOWER = 264,          /* T_THE_FOLLOWER  */
    T_THE_STORY = 265,             /* T_THE_STORY  */
    T_POSTED = 266,                /* T_POSTED  */
    T_ABOUT = 267,                 /* T_ABOUT  */
    T_THAT_HAD = 268,              /* T_THAT_HAD  */
    T_ANOTHER = 269,               /* T_ANOTHER  */
    T_STARTED_WITH = 270,          /* T_STARTED_WITH  */
    T_BEGAN_AT = 271,              /* T_BEGAN_AT  */
    T_NOW_HAS = 272,               /* T_NOW_HAS  */
    T_READS = 273,                 /* T_READS  */
    T_IS_VIRAL = 274,              /* T_IS_VIRAL  */
    T_IS_TRENDING = 275,           /* T_IS_TRENDING  */
    T_GAINED = 276,                /* T_GAINED  */
    T_LOST = 277,                  /* T_LOST  */
    T_ADDED = 278,                 /* T_ADDED  */
    T_REMOVED = 279,               /* T_REMOVED  */
    T_INCREASED_BY = 280,          /* T_INCREASED_BY  */
    T_DECREASED_BY = 281,          /* T_DECREASED_BY  */
    T_WAS_UPDATED_TO = 282,        /* T_WAS_UPDATED_TO  */
    T_BECAME = 283,                /* T_BECAME  */
    T_MULTIPLIED_BY = 284,         /* T_MULTIPLIED_BY  */
    T_DIVIDED_BY = 285,            /* T_DIVIDED_BY  */
    T_PLUS = 286,                  /* T_PLUS  */
    T_MINUS = 287,                 /* T_MINUS  */
    T_TIMES = 288,                 /* T_TIMES  */
    T_MULTIPLY = 289,              /* T_MULTIPLY  */
    T_DIVIDED_EVENLY_BY = 290,     /* T_DIVIDED_EVENLY_BY  */
    T_DIVIDE = 291,                /* T_DIVIDE  */
    T_MODULO = 292,                /* T_MODULO  */
    T_WITH = 293,                  /* T_WITH  */
    T_AND_THEN = 294,              /* T_AND_THEN  */
    T_THE_FEED = 295,              /* T_THE_FEED  */
    T_CONTAINS = 296,              /* T_CONTAINS  */
    T_AT_INDEX = 297,              /* T_AT_INDEX  */
    T_LIKES = 298,                 /* T_LIKES  */
    T_FOLLOWERS = 299,             /* T_FOLLOWERS  */
    T_VIEWS = 300,                 /* T_VIEWS  */
    T_COMMENTS = 301,              /* T_COMMENTS  */
    T_SHARES = 302,                /* T_SHARES  */
    T_POSTS = 303,                 /* T_POSTS  */
    T_STORIES = 304,               /* T_STORIES  */
    T_ENGAGEMENT_RATE = 305,       /* T_ENGAGEMENT_RATE  */
    T_REACH = 306,                 /* T_REACH  */
    T_GROWTH_RATE = 307,           /* T_GROWTH_RATE  */
    T_WHEN = 308,                  /* T_WHEN  */
    T_OTHERWISE_IF = 309,          /* T_OTHERWISE_IF  */
    T_OTHERWISE = 310,             /* T_OTHERWISE  */
    T_WENT_VIRAL = 311,            /* T_WENT_VIRAL  */
    T_REACHED = 312,               /* T_REACHED  */
    T_EXCEEDED = 313,              /* T_EXCEEDED  */
    T_DROPPED_BELOW = 314,         /* T_DROPPED_BELOW  */
    T_STAYED_AT = 315,             /* T_STAYED_AT  */
    T_MORE_THAN = 316,             /* T_MORE_THAN  */
    T_LESS_THAN = 317,             /* T_LESS_THAN  */
    T_EXACTLY = 318,               /* T_EXACTLY  */
    T_AT_LEAST = 319,              /* T_AT_LEAST  */
    T_AT_MOST = 320,               /* T_AT_MOST  */
    T_DIFFERENT_FROM = 321,        /* T_DIFFERENT_FROM  */
    T_EQUAL_TO = 322,              /* T_EQUAL_TO  */
    T_NOT_EQUAL_TO = 323,          /* T_NOT_EQUAL_TO  */
    T_EVERY_DAY_FOR = 324,         /* T_EVERY_DAY_FOR  */
    T_EVERY = 325,                 /* T_EVERY  */
    T_DAYS = 326,                  /* T_DAYS  */
    T_INCREMENTING_BY = 327,       /* T_INCREMENTING_BY  */
    T_DECREMENTING_BY = 328,       /* T_DECREMENTING_BY  */
    T_FOR_EACH = 329,              /* T_FOR_EACH  */
    T_POST_IN = 330,               /* T_POST_IN  */
    T_STORY_IN = 331,              /* T_STORY_IN  */
    T_FOLLOWER_FROM = 332,         /* T_FOLLOWER_FROM  */
    T_TO = 333,                    /* T_TO  */
    T_TRENDING_LOOP = 334,         /* T_TRENDING_LOOP  */
    T_UNTIL = 335,                 /* T_UNTIL  */
    T_STOP_THE_STORY = 336,        /* T_STOP_THE_STORY  */
    T_SKIP_THIS_POST = 337,        /* T_SKIP_THIS_POST  */
    T_THE_STORY_OF = 338,          /* T_THE_STORY_OF  */
    T_BEGINS_WITH = 339,           /* T_BEGINS_WITH  */
    T_TELL_BACK = 340,             /* T_TELL_BACK  */
    T_THE_STORY_ENDS = 341,        /* T_THE_STORY_ENDS  */
    T_TELL = 342,                  /* T_TELL  */
    T_ANNOUNCE = 343,              /* T_ANNOUNCE  */
    T_ASK_FOR = 344,               /* T_ASK_FOR  */
    T_DISPLAY = 345,               /* T_DISPLAY  */
    T_CALCULATE_VIRALITY = 346,    /* T_CALCULATE_VIRALITY  */
    T_CALCULATE_ENGAGEMENT = 347,  /* T_CALCULATE_ENGAGEMENT  */
    T_FIND_TOP_POST = 348,         /* T_FIND_TOP_POST  */
    T_FIND_HIGHEST_REACH = 349,    /* T_FIND_HIGHEST_REACH  */
    T_FIND_TOTAL_REACH = 350,      /* T_FIND_TOTAL_REACH  */
    T_COUNT_TOTAL_ENGAGEMENT = 351, /* T_COUNT_TOTAL_ENGAGEMENT  */
    T_CHECK_IF_TRENDING = 352,     /* T_CHECK_IF_TRENDING  */
    T_ANALYZE_GROWTH = 353,        /* T_ANALYZE_GROWTH  */
    T_FIND_MAX_VIRAL_ACCOUNT = 354, /* T_FIND_MAX_VIRAL_ACCOUNT  */
    T_REVERSE_THE_CAPTION = 355,   /* T_REVERSE_THE_CAPTION  */
    T_DETECT_SPAM = 356,           /* T_DETECT_SPAM  */
    T_CLAMP_ENGAGEMENT = 357,      /* T_CLAMP_ENGAGEMENT  */
    T_BETWEEN = 358,               /* T_BETWEEN  */
    T_REVERSE_GROWTH = 359,        /* T_REVERSE_GROWTH  */
    T_ALSO = 360,                  /* T_ALSO  */
    T_EITHER = 361,                /* T_EITHER  */
    T_OPPOSITE = 362,              /* T_OPPOSITE  */
    T_LPAREN = 363,                /* T_LPAREN  */
    T_RPAREN = 364,                /* T_RPAREN  */
    T_LBRACE = 365,                /* T_LBRACE  */
    T_RBRACE = 366,                /* T_RBRACE  */
    T_LBRACKET = 367,              /* T_LBRACKET  */
    T_RBRACKET = 368,              /* T_RBRACKET  */
    T_COMMA = 369,                 /* T_COMMA  */
    T_DOT = 370,                   /* T_DOT  */
    T_COLON = 371,                 /* T_COLON  */
    T_NUMBER = 372,                /* T_NUMBER  */
    T_DECIMAL = 373,               /* T_DECIMAL  */
    T_TEXT = 374,                  /* T_TEXT  */
    T_ID = 375,                    /* T_ID  */
    T_CHAR = 376,                  /* T_CHAR  */
    T_TRUE_STORY = 377,            /* T_TRUE_STORY  */
    T_FALSE_ALARM = 378            /* T_FALSE_ALARM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 120 "socialstory_parser.y"

    int ival;
    float fval;
    char* sval;
    char cval;
    int bval;
    struct ASTNode* node;

#line 196 "socialstory_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SOCIALSTORY_PARSER_TAB_H_INCLUDED  */
