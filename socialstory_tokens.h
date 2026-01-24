#ifndef SOCIALSTORY_TOKENS_H
#define SOCIALSTORY_TOKENS_H

enum TokenType {
    // Program structure 
    T_GO_LIVE = 256,
    T_END_LIVE,
    
    // Account & Entity keywords 
    T_THE_ACCOUNT,
    T_WAS_CREATED,
    T_THE_POST,
    T_THE_CAPTION,
    T_THE_FOLLOWER,
    T_THE_STORY,
    T_POSTED,
    T_ABOUT,
    T_THAT_HAD,
    
    // Variable initialization verbs 
    T_STARTED_WITH,
    T_BEGAN_AT,
    T_NOW_HAS,
    T_READS,
    T_IS_VIRAL,
    T_IS_TRENDING,
    
    // Update action verbs 
    T_GAINED,
    T_LOST,
    T_INCREASED_BY,
    T_DECREASED_BY,
    T_WAS_UPDATED_TO,
    T_BECAME,
    
    // Data structure keywords 
    T_CONTAINS,
    T_THE_FEED,
    T_AT_INDEX,
    
    // Type keywords 
    T_LIKES,
    T_FOLLOWERS,
    T_VIEWS,
    T_COMMENTS,
    T_SHARES,
    T_POSTS,
    T_STORIES,
    T_ENGAGEMENT_RATE,
    T_REACH,
    T_GROWTH_RATE,
    
    // Conditional keywords 
    T_WHEN,
    T_OTHERWISE_IF,
    T_OTHERWISE,
    T_WENT_VIRAL,
    T_REACHED,
    T_EXCEEDED,
    T_DROPPED_BELOW,
    T_STAYED_AT,
    
    // Comparison operators (narrative style) 
    T_MORE_THAN,
    T_LESS_THAN,
    T_EXACTLY,
    T_AT_LEAST,
    T_AT_MOST,
    T_DIFFERENT_FROM,
    
    // Loop keywords 
    T_EVERY_DAY_FOR,
    T_EVERY,
    T_DAYS,
    T_INCREMENTING_BY,
    T_DECREMENTING_BY,
    T_FOR_EACH,
    T_POST_IN,
    T_STORY_IN,
    T_FOLLOWER_FROM,
    T_TO,
    T_TRENDING_LOOP,
    T_UNTIL,
    
    // Loop control 
    T_STOP_THE_STORY,
    T_SKIP_THIS_POST,
    
    // Function keywords 
    T_THE_STORY_OF,
    T_BEGINS_WITH,
    T_TELL_BACK,
    T_THE_STORY_ENDS,
    T_TELL,
    
    // I/O keywords 
    T_ANNOUNCE,
    T_ASK_FOR,
    T_DISPLAY,
    
    // Built-in functions - Analytics 
    T_CALCULATE_VIRALITY,
    T_CALCULATE_ENGAGEMENT,
    T_FIND_TOP_POST,
    T_FIND_HIGHEST_REACH,
    T_FIND_TOTAL_REACH,
    T_COUNT_TOTAL_ENGAGEMENT,
    T_CHECK_IF_TRENDING,
    T_ANALYZE_GROWTH,
    T_FIND_MAX_VIRAL_ACCOUNT,
    
    // Built-in functions - String operations 
    T_REVERSE_THE_CAPTION,
    T_DETECT_SPAM,
    
    // Built-in functions - Utility
    T_CLAMP_ENGAGEMENT,
    T_BETWEEN,
    T_REVERSE_GROWTH,
    
    // Boolean literals 
    T_TRUE_STORY,
    T_FALSE_ALARM,
    
    // Logical operators 
    T_ALSO,      // and 
    T_EITHER,    // or 
    T_OPPOSITE,  // not 
    
    // Punctuation & Operators 
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
    
    // Arithmetic operators 
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_DIVIDE,
    T_PERCENT,
    
    // Assignment and compound operators 
    T_EQUALS,
    T_PLUS_EQUALS,
    T_MINUS_EQUALS,
    T_MULT_EQUALS,
    T_DIV_EQUALS,
    T_INCREMENT,
    T_DECREMENT,
    
    // Relational operators (C-style) 
    T_EQ,
    T_NEQ,
    T_LT,
    T_GT,
    T_LTE,
    T_GTE,
    
    // Logical operators (C-style) 
    T_AND,
    T_OR,
    T_NOT,
    
    // Literals & Identifiers 
    T_ID,
    T_NUMBER,
    T_DECIMAL,
    T_TEXT,
    T_CHAR
};

 // Union for semantic values 
typedef union {
    int    ival;
    double fval;
    char*  sval;
    char   cval;
    int    bval;
} YYSTYPE;

extern YYSTYPE yylval;
extern int yylineno;

#endif 