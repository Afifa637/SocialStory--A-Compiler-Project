%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socialstory_tokens.h"

YYSTYPE yylval;
int error_count = 0;

char* duplicate_string(const char* s) {
    char* copy = (char*)malloc(strlen(s) + 1);
    if (!copy) {
        fprintf(stderr, "Memory allocation failed at line %d\n", yylineno);
        exit(1);
    }
    strcpy(copy, s);
    return copy;
}

char* process_string(const char* str) {
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (!result) return NULL;
    
    int j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\\' && i + 1 < len) {
            i++;
            switch(str[i]) {
                case 'n':  result[j++] = '\n'; break;
                case 't':  result[j++] = '\t'; break;
                case 'r':  result[j++] = '\r'; break;
                case '\\': result[j++] = '\\'; break;
                case '"':  result[j++] = '"'; break;
                case '\'': result[j++] = '\''; break;
                case '0':  result[j++] = '\0'; break;
                default:   result[j++] = str[i]; break;
            }
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

%}

%option noyywrap
%option yylineno

WS          [ \t\r]+
NEWLINE     \n
DIGIT       [0-9]
LETTER      [A-Za-z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+\.{DIGIT}+
SCIENTIFIC  {DIGIT}+(\.{DIGIT}+)?[eE][+-]?{DIGIT}+
HEX         0[xX][0-9a-fA-F]+
OCTAL       0[0-7]+
STRING      \"([^\\\"\n]|\\.)*\"
CHAR        '([^\\'\n]|\\.)' 
UNTERMINATED_STRING  \"([^\\\"\n]|\\.)*
SINGLE_COMMENT  ("//".*|"#".*)
MULTI_COMMENT_START "/*"
MULTI_COMMENT_END "*/"

%x MULTILINE_COMMENT

%%

{MULTI_COMMENT_START}   { BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>{MULTI_COMMENT_END}  { BEGIN(INITIAL); }
<MULTILINE_COMMENT>\n   { }
<MULTILINE_COMMENT>.    { }
<MULTILINE_COMMENT><<EOF>> { 
                          fprintf(stderr, "Error line %d: Unterminated comment\n", yylineno);
                          error_count++;
                          yyterminate();
                        }

"Go live"           { return T_GO_LIVE; }
"End live"          { return T_END_LIVE; }

    // ACCOUNT & ENTITY KEYWORDS
"The account"       { return T_THE_ACCOUNT; }
"was created"       { return T_WAS_CREATED; }
"The post"          { return T_THE_POST; }
"The caption"       { return T_THE_CAPTION; }
"The follower"      { return T_THE_FOLLOWER; }
"The story"         { return T_THE_STORY; }
"posted"            { return T_POSTED; }
"about"             { return T_ABOUT; }
"that had"          { return T_THAT_HAD; }

    //INITIALIZATION VERBS
"started with"      { return T_STARTED_WITH; }
"began at"          { return T_BEGAN_AT; }
"now has"           { return T_NOW_HAS; }
"reads"             { return T_READS; }
"is viral"          { return T_IS_VIRAL; }
"is trending"       { return T_IS_TRENDING; }

    //UPDATE ACTION VERBS
"gained"            { return T_GAINED; }
"lost"              { return T_LOST; }
"increased by"      { return T_INCREASED_BY; }
"decreased by"      { return T_DECREASED_BY; }
"was updated to"    { return T_WAS_UPDATED_TO; }
"became"            { return T_BECAME; }
"multiplied by"     { return T_MULTIPLIED_BY; }
"divided by"        { return T_DIVIDED_BY; }

    //CALCULATION WORDS
"plus"              { return T_PLUS; }
"minus"             { return T_MINUS; }
"times"             { return T_TIMES; }
"divided evenly by" { return T_DIVIDED_EVENLY_BY; }
"modulo"            { return T_MODULO; }
"with"              { return T_WITH; }
"and then"          { return T_AND_THEN; }

    // DATA STRUCTURES 
"the feed"          { return T_THE_FEED; }
"contains"          { return T_CONTAINS; }
"at index"          { return T_AT_INDEX; }

    // TYPE KEYWORDS
"likes"             { return T_LIKES; }
"followers"         { return T_FOLLOWERS; }
"views"             { return T_VIEWS; }
"comments"          { return T_COMMENTS; }
"shares"            { return T_SHARES; }
"posts"             { return T_POSTS; }
"stories"           { return T_STORIES; }
"engagement rate"   { return T_ENGAGEMENT_RATE; }
"reach"             { return T_REACH; }
"growth rate"       { return T_GROWTH_RATE; }

    //CONDITIONALS 
"When"              { return T_WHEN; }
"Otherwise if"      { return T_OTHERWISE_IF; }
"Otherwise"         { return T_OTHERWISE; }
"went viral"        { return T_WENT_VIRAL; }
"reached"           { return T_REACHED; }
"exceeded"          { return T_EXCEEDED; }
"dropped below"     { return T_DROPPED_BELOW; }
"stayed at"         { return T_STAYED_AT; }

    //COMPARISON OPERATORS 
"more than"         { return T_MORE_THAN; }
"less than"         { return T_LESS_THAN; }
"exactly"           { return T_EXACTLY; }
"at least"          { return T_AT_LEAST; }
"at most"           { return T_AT_MOST; }
"different from"    { return T_DIFFERENT_FROM; }
"equal to"          { return T_EQUAL_TO; }
"not equal to"      { return T_NOT_EQUAL_TO; }

    //LOOPS 
"Every day for"     { return T_EVERY_DAY_FOR; }
"Every"             { return T_EVERY; }
"days"              { return T_DAYS; }
"incrementing by"   { return T_INCREMENTING_BY; }
"decrementing by"   { return T_DECREMENTING_BY; }
"For each"          { return T_FOR_EACH; }
"post in"           { return T_POST_IN; }
"story in"          { return T_STORY_IN; }
"follower from"     { return T_FOLLOWER_FROM; }
"to"                { return T_TO; }
"trending loop"     { return T_TRENDING_LOOP; }
"until"             { return T_UNTIL; }

    // LOOP CONTROL 
"Stop the story"    { return T_STOP_THE_STORY; }
"Skip this post"    { return T_SKIP_THIS_POST; }

    //FUNCTIONS 
"The story of"      { return T_THE_STORY_OF; }
"begins with"       { return T_BEGINS_WITH; }
"Tell back"         { return T_TELL_BACK; }
"The story ends"    { return T_THE_STORY_ENDS; }
"Tell"              { return T_TELL; }

    //I/O
"Announce"          { return T_ANNOUNCE; }
"Ask for"           { return T_ASK_FOR; }
"Display"           { return T_DISPLAY; }

    //BUILT-IN FUNCTIONS
"Calculate virality"            { return T_CALCULATE_VIRALITY; }
"Calculate engagement with"     { return T_CALCULATE_ENGAGEMENT; }
"Find top post"                 { return T_FIND_TOP_POST; }
"Find the highest reach in"     { return T_FIND_HIGHEST_REACH; }
"Find the total reach in"       { return T_FIND_TOTAL_REACH; }
"Count total engagement"        { return T_COUNT_TOTAL_ENGAGEMENT; }
"Check if trending"             { return T_CHECK_IF_TRENDING; }
"Analyze growth"                { return T_ANALYZE_GROWTH; }
"Find max viral account"        { return T_FIND_MAX_VIRAL_ACCOUNT; }
"Reverse the caption"           { return T_REVERSE_THE_CAPTION; }
"Detect spam in"                { return T_DETECT_SPAM; }
"Clamp engagement between"      { return T_CLAMP_ENGAGEMENT; }
"between"                       { return T_BETWEEN; }
"Reverse growth"                { return T_REVERSE_GROWTH; }

//Boolean
"true story"        { yylval.bval = 1; return T_TRUE_STORY; }
"false alarm"       { yylval.bval = 0; return T_FALSE_ALARM; }

    //LOGICAL OPERATORS 
"also"              { return T_ALSO; }
"either"            { return T_EITHER; }
"opposite"          { return T_OPPOSITE; }

"("                 { return T_LPAREN; }
")"                 { return T_RPAREN; }
"{"                 { return T_LBRACE; }
"}"                 { return T_RBRACE; }
"["                 { return T_LBRACKET; }
"]"                 { return T_RBRACKET; }
","                 { return T_COMMA; }
"."                 { return T_DOT; }
":"                 { return T_COLON; }

    // NUMERIC LITERALS 
{SCIENTIFIC}        { yylval.fval = atof(yytext); return T_DECIMAL; }
{HEX}               { yylval.ival = (int)strtol(yytext, NULL, 16); return T_NUMBER; }
{OCTAL}             { yylval.ival = (int)strtol(yytext, NULL, 8); return T_NUMBER; }
{FLOAT}             { yylval.fval = atof(yytext); return T_DECIMAL; }
{INTEGER}           { yylval.ival = atoi(yytext); return T_NUMBER; }

    //CHARACTER LITERALS
{CHAR}              {
                      if (yytext[1] == '\\') {
                          switch(yytext[2]) {
                              case 'n': yylval.cval = '\n'; break;
                              case 't': yylval.cval = '\t'; break;
                              case 'r': yylval.cval = '\r'; break;
                              case '\\': yylval.cval = '\\'; break;
                              case '\'': yylval.cval = '\''; break;
                              case '0': yylval.cval = '\0'; break;
                              default: yylval.cval = yytext[2]; break;
                          }
                      } else {
                          yylval.cval = yytext[1];
                      }
                      return T_CHAR;
                    }

    //STRING LITERALS 
{STRING}            {
                      size_t len = strlen(yytext);
                      char* temp = (char*)malloc(len - 1);
                      if (!temp) {
                          fprintf(stderr, "Memory allocation failed at line %d\n", yylineno);
                          exit(1);
                      }
                      strncpy(temp, yytext + 1, len - 2);
                      temp[len - 2] = '\0';
                      yylval.sval = process_string(temp);
                      free(temp);
                      return T_TEXT;
                    }

    //IDENTIFIERS 
{ID}                { yylval.sval = duplicate_string(yytext); return T_ID; }

{WS}                { }
{NEWLINE}           { }
{SINGLE_COMMENT}    { }

    //ERROR HANDLING 
{UNTERMINATED_STRING} {
                      fprintf(stderr, "Error line %d: Unterminated string starting with %s\n", 
                              yylineno, yytext);
                      error_count++;
                    }

.                   { 
                      fprintf(stderr, "Error line %d: Invalid character '%s' (ASCII %d)\n", 
                              yylineno, yytext, (int)yytext[0]);
                      error_count++;
                    }

%%

const char* token_name(int t) {
    switch(t) {
        case T_GO_LIVE: return "T_GO_LIVE";
        case T_END_LIVE: return "T_END_LIVE";
        case T_THE_ACCOUNT: return "T_THE_ACCOUNT";
        case T_WAS_CREATED: return "T_WAS_CREATED";
        case T_THE_POST: return "T_THE_POST";
        case T_THE_CAPTION: return "T_THE_CAPTION";
        case T_THE_FOLLOWER: return "T_THE_FOLLOWER";
        case T_THE_STORY: return "T_THE_STORY";
        case T_POSTED: return "T_POSTED";
        case T_ABOUT: return "T_ABOUT";
        case T_THAT_HAD: return "T_THAT_HAD";
        case T_STARTED_WITH: return "T_STARTED_WITH";
        case T_BEGAN_AT: return "T_BEGAN_AT";
        case T_NOW_HAS: return "T_NOW_HAS";
        case T_READS: return "T_READS";
        case T_IS_VIRAL: return "T_IS_VIRAL";
        case T_IS_TRENDING: return "T_IS_TRENDING";
        case T_GAINED: return "T_GAINED";
        case T_LOST: return "T_LOST";
        case T_INCREASED_BY: return "T_INCREASED_BY";
        case T_DECREASED_BY: return "T_DECREASED_BY";
        case T_WAS_UPDATED_TO: return "T_WAS_UPDATED_TO";
        case T_BECAME: return "T_BECAME";
        case T_MULTIPLIED_BY: return "T_MULTIPLIED_BY";
        case T_DIVIDED_BY: return "T_DIVIDED_BY";
        case T_PLUS: return "T_PLUS";
        case T_MINUS: return "T_MINUS";
        case T_TIMES: return "T_TIMES";
        case T_DIVIDED_EVENLY_BY: return "T_DIVIDED_EVENLY_BY";
        case T_MODULO: return "T_MODULO";
        case T_WITH: return "T_WITH";
        case T_AND_THEN: return "T_AND_THEN";
        case T_THE_FEED: return "T_THE_FEED";
        case T_CONTAINS: return "T_CONTAINS";
        case T_AT_INDEX: return "T_AT_INDEX";
        case T_LIKES: return "T_LIKES";
        case T_FOLLOWERS: return "T_FOLLOWERS";
        case T_VIEWS: return "T_VIEWS";
        case T_COMMENTS: return "T_COMMENTS";
        case T_SHARES: return "T_SHARES";
        case T_POSTS: return "T_POSTS";
        case T_STORIES: return "T_STORIES";
        case T_ENGAGEMENT_RATE: return "T_ENGAGEMENT_RATE";
        case T_REACH: return "T_REACH";
        case T_GROWTH_RATE: return "T_GROWTH_RATE";
        case T_WHEN: return "T_WHEN";
        case T_OTHERWISE_IF: return "T_OTHERWISE_IF";
        case T_OTHERWISE: return "T_OTHERWISE";
        case T_WENT_VIRAL: return "T_WENT_VIRAL";
        case T_REACHED: return "T_REACHED";
        case T_EXCEEDED: return "T_EXCEEDED";
        case T_DROPPED_BELOW: return "T_DROPPED_BELOW";
        case T_STAYED_AT: return "T_STAYED_AT";
        case T_MORE_THAN: return "T_MORE_THAN";
        case T_LESS_THAN: return "T_LESS_THAN";
        case T_EXACTLY: return "T_EXACTLY";
        case T_AT_LEAST: return "T_AT_LEAST";
        case T_AT_MOST: return "T_AT_MOST";
        case T_DIFFERENT_FROM: return "T_DIFFERENT_FROM";
        case T_EQUAL_TO: return "T_EQUAL_TO";
        case T_NOT_EQUAL_TO: return "T_NOT_EQUAL_TO";
        case T_EVERY_DAY_FOR: return "T_EVERY_DAY_FOR";
        case T_EVERY: return "T_EVERY";
        case T_DAYS: return "T_DAYS";
        case T_INCREMENTING_BY: return "T_INCREMENTING_BY";
        case T_DECREMENTING_BY: return "T_DECREMENTING_BY";
        case T_FOR_EACH: return "T_FOR_EACH";
        case T_POST_IN: return "T_POST_IN";
        case T_STORY_IN: return "T_STORY_IN";
        case T_FOLLOWER_FROM: return "T_FOLLOWER_FROM";
        case T_TO: return "T_TO";
        case T_TRENDING_LOOP: return "T_TRENDING_LOOP";
        case T_UNTIL: return "T_UNTIL";
        case T_STOP_THE_STORY: return "T_STOP_THE_STORY";
        case T_SKIP_THIS_POST: return "T_SKIP_THIS_POST";
        case T_THE_STORY_OF: return "T_THE_STORY_OF";
        case T_BEGINS_WITH: return "T_BEGINS_WITH";
        case T_TELL_BACK: return "T_TELL_BACK";
        case T_THE_STORY_ENDS: return "T_THE_STORY_ENDS";
        case T_TELL: return "T_TELL";
        case T_ANNOUNCE: return "T_ANNOUNCE";
        case T_ASK_FOR: return "T_ASK_FOR";
        case T_DISPLAY: return "T_DISPLAY";
        case T_CALCULATE_VIRALITY: return "T_CALCULATE_VIRALITY";
        case T_CALCULATE_ENGAGEMENT: return "T_CALCULATE_ENGAGEMENT";
        case T_FIND_TOP_POST: return "T_FIND_TOP_POST";
        case T_FIND_HIGHEST_REACH: return "T_FIND_HIGHEST_REACH";
        case T_FIND_TOTAL_REACH: return "T_FIND_TOTAL_REACH";
        case T_COUNT_TOTAL_ENGAGEMENT: return "T_COUNT_TOTAL_ENGAGEMENT";
        case T_CHECK_IF_TRENDING: return "T_CHECK_IF_TRENDING";
        case T_ANALYZE_GROWTH: return "T_ANALYZE_GROWTH";
        case T_FIND_MAX_VIRAL_ACCOUNT: return "T_FIND_MAX_VIRAL_ACCOUNT";
        case T_REVERSE_THE_CAPTION: return "T_REVERSE_THE_CAPTION";
        case T_DETECT_SPAM: return "T_DETECT_SPAM";
        case T_CLAMP_ENGAGEMENT: return "T_CLAMP_ENGAGEMENT";
        case T_BETWEEN: return "T_BETWEEN";
        case T_REVERSE_GROWTH: return "T_REVERSE_GROWTH";
        case T_TRUE_STORY: return "T_TRUE_STORY";
        case T_FALSE_ALARM: return "T_FALSE_ALARM";
        case T_ALSO: return "T_ALSO";
        case T_EITHER: return "T_EITHER";
        case T_OPPOSITE: return "T_OPPOSITE";
        case T_LPAREN: return "T_LPAREN";
        case T_RPAREN: return "T_RPAREN";
        case T_LBRACE: return "T_LBRACE";
        case T_RBRACE: return "T_RBRACE";
        case T_LBRACKET: return "T_LBRACKET";
        case T_RBRACKET: return "T_RBRACKET";
        case T_COMMA: return "T_COMMA";
        case T_DOT: return "T_DOT";
        case T_COLON: return "T_COLON";
        case T_NUMBER: return "T_NUMBER";
        case T_DECIMAL: return "T_DECIMAL";
        case T_TEXT: return "T_TEXT";
        case T_CHAR: return "T_CHAR";
        case T_ID: return "T_ID";
        default: return "T_UNKNOWN";
    }
}

int main(int argc, char** argv) {
    FILE *input, *output;
    int token;
    int token_count = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }

    output = fopen(argv[2], "w");
    if (!output) {
        fprintf(stderr, "Error: Cannot open output file '%s'\n", argv[2]);
        fclose(input);
        return 1;
    }

    yyin = input;

    while ((token = yylex()) != 0) {
        token_count++;
        fprintf(output, "%s %s", token_name(token), yytext);
        
        if (token == T_NUMBER) {
            fprintf(output, " %d", yylval.ival);
        } else if (token == T_DECIMAL) {
            fprintf(output, " %g", yylval.fval);
        } else if (token == T_TEXT) {
            fprintf(output, " \"%s\"", yylval.sval);
            free(yylval.sval);
        } else if (token == T_CHAR) {
            fprintf(output, " '%c'", yylval.cval);
        } else if (token == T_ID) {
            fprintf(output, " %s", yylval.sval);
            free(yylval.sval);
        }
        
        fprintf(output, "\n");
    }

    fprintf(output, "\n# Lexical Analysis Summary:\n");
    fprintf(output, "# Total tokens: %d\n", token_count);
    fprintf(output, "# Total lines: %d\n", yylineno);
    fprintf(output, "# Total errors: %d\n", error_count);

    if (error_count > 0) {
        fprintf(stderr, "\nLexical analysis completed with %d error(s)\n", error_count);
    } else {
        printf("\nLexical analysis successful!\n");
        printf("Tokens: %d, Lines: %d\n", token_count, yylineno);
    }

    fclose(input);
    fclose(output);
    return (error_count > 0) ? 1 : 0;
}