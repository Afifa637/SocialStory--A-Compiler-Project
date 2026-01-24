#ifndef SOCIALSTORY_TOKENS_H
#define SOCIALSTORY_TOKENS_H

/* Token definitions for SocialStoryScript Compiler */
enum TokenType {
    /* Program structure */
    T_GO_LIVE = 256,
    T_END_LIVE,
    
    /* Account & Narrative keywords */
    T_THE_ACCOUNT,
    T_WAS_CREATED,
    T_THE_POST,
    T_THE_CAPTION,
    T_THE_FOLLOWER,
    
    /* Variable initialization verbs */
    T_STARTED_WITH,
    T_BEGAN_AT,
    T_NOW_HAS,
    T_READS,
    T_IS_VIRAL,
    T_IS_TRENDING,
    
    /* Update action verbs */
    T_GAINED,
    T_LOST,
    T_INCREASED_BY,
    T_DECREASED_BY,
    T_WAS_UPDATED_TO,
    T_BECAME,
    
    /* Data structure keywords */
    T_CONTAINS,
    T_THE_FEED,
    T_AT_INDEX,
    
    /* Type keywords */
    T_LIKES,
    T_FOLLOWERS,
    T_VIEWS,
    T_COMMENTS,
    T_SHARES,
    T_ENGAGEMENT_RATE,
    T_REACH,
    
    /* Conditional keywords */
    T_WHEN,
    T_OTHERWISE_IF,
    T_OTHERWISE,
    T_WENT_VIRAL,
    T_REACHED,
    T_EXCEEDED,
    T_DROPPED_BELOW,
    T_STAYED_AT,
    
    /* Comparison operators (narrative style) */
    T_MORE_THAN,
    T_LESS_THAN,
    T_EXACTLY,
    T_AT_LEAST,
    T_AT_MOST,
    T_DIFFERENT_FROM,
    
    /* Loop keywords */
    T_EVERY_DAY_FOR,
    T_DAYS,
    T_FOR_EACH,
    T_POST_IN,
    T_FOLLOWER_FROM,
    T_TO,
    T_TRENDING_LOOP,
    T_UNTIL,
    
    /* Loop control */
    T_STOP_THE_STORY,
    T_SKIP_THIS_POST,
    
    /* Function keywords */
    T_THE_STORY_OF,
    T_BEGINS_WITH,
    T_TELL_BACK,
    T_THE_STORY_ENDS,
    T_TELL,
    
    /* I/O keywords */
    T_ANNOUNCE,
    T_ASK_FOR,
    T_DISPLAY,
    
    /* Built-in functions */
    T_CALCULATE_VIRALITY,
    T_FIND_TOP_POST,
    T_COUNT_TOTAL_ENGAGEMENT,
    T_CHECK_IF_TRENDING,
    T_ANALYZE_GROWTH,
    
    /* Boolean literals */
    T_TRUE_STORY,
    T_FALSE_ALARM,
    
    /* Logical operators */
    T_ALSO,      /* and */
    T_EITHER,    /* or */
    T_OPPOSITE,  /* not */
    
    /* Punctuation & Operators */
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_LBRACKET,
    T_RBRACKET,
    T_COMMA,
    T_DOT,
    T_COLON,
    T_SEMICOLON,
    
    /* Arithmetic operators */
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_DIVIDE,
    T_PERCENT,
    
    /* Assignment */
    T_EQUALS,
    
    /* Literals & Identifiers */
    T_ID,
    T_NUMBER,
    T_DECIMAL,
    T_TEXT
};

/* Union for semantic values */
typedef union {
    int    ival;
    double fval;
    char*  sval;
    int    bval;
} YYSTYPE;

extern YYSTYPE yylval;
extern int yylineno;

#endif /* SOCIALSTORY_TOKENS_H */