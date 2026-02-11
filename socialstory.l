%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socialstory_tokens.h"

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
%option caseless

WS          [ \t\r]+
NEWLINE     \n
DIGIT       [0-9]
LETTER      [A-Za-z]
IDENTIFIER  ({LETTER}|_)({LETTER}|{DIGIT}|_)*|{DIGIT}+({LETTER}|_)({LETTER}|{DIGIT}|_)*
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

"The account"       { return T_THE_ACCOUNT; }
"was created"       { return T_WAS_CREATED; }
"The post"          { return T_THE_POST; }
"The caption"       { return T_THE_CAPTION; }
"The follower"      { return T_THE_FOLLOWER; }
"The story"         { return T_THE_STORY; }
"posted"            { return T_POSTED; }
"about"             { return T_ABOUT; }
"that had"          { return T_THAT_HAD; }
"another"           { return T_ANOTHER; }

"started with"      { return T_STARTED_WITH; }
"began at"          { return T_BEGAN_AT; }
"now has"           { return T_NOW_HAS; }
"reads"             { return T_READS; }
"is viral"          { return T_IS_VIRAL; }
"is trending"       { return T_IS_TRENDING; }

"gained"            { return T_GAINED; }
"lost"              { return T_LOST; }
"added"             { return T_ADDED; }
"removed"           { return T_REMOVED; }
"increased by"      { return T_INCREASED_BY; }
"decreased by"      { return T_DECREASED_BY; }
"was updated to"    { return T_WAS_UPDATED_TO; }
"became"            { return T_BECAME; }
"multiplied by"     { return T_MULTIPLIED_BY; }
"divided by"        { return T_DIVIDED_BY; }

"plus"              { return T_PLUS; }
"minus"             { return T_MINUS; }
"times"             { return T_TIMES; }
"multiply"          { return T_MULTIPLY; }
"divided evenly by" { return T_DIVIDED_EVENLY_BY; }
"divide"            { return T_DIVIDE; }
"modulo"            { return T_MODULO; }
"with"              { return T_WITH; }
"and then"          { return T_AND_THEN; }
"for"               { return T_FOR; }

"the feed"          { return T_THE_FEED; }
"contains"          { return T_CONTAINS; }
"at index"          { return T_AT_INDEX; }

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

"When"              { return T_WHEN; }
"Otherwise if"      { return T_OTHERWISE_IF; }
"Otherwise"         { return T_OTHERWISE; }
"went viral"        { return T_WENT_VIRAL; }
"reached"           { return T_REACHED; }
"exceeded"          { return T_EXCEEDED; }
"dropped below"     { return T_DROPPED_BELOW; }
"stayed at"         { return T_STAYED_AT; }

"more than"         { return T_MORE_THAN; }
"less than"         { return T_LESS_THAN; }
"exactly"           { return T_EXACTLY; }
"at least"          { return T_AT_LEAST; }
"at most"           { return T_AT_MOST; }
"different from"    { return T_DIFFERENT_FROM; }
"equal to"          { return T_EQUAL_TO; }
"not equal to"      { return T_NOT_EQUAL_TO; }

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

"Stop the story"    { return T_STOP_THE_STORY; }
"Skip this post"    { return T_SKIP_THIS_POST; }

"The story of"      { return T_THE_STORY_OF; }
"begins with"       { return T_BEGINS_WITH; }
"Tell back"         { return T_TELL_BACK; }
"The story ends"    { return T_THE_STORY_ENDS; }
"Tell"              { return T_TELL; }

"Announce"          { return T_ANNOUNCE; }
"Ask for"           { return T_ASK_FOR; }
"Display"           { return T_DISPLAY; }

"Calculate virality"            { return T_CALCULATE_VIRALITY; }
"Calculate engagement"          { return T_CALCULATE_ENGAGEMENT; }
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

"true story"        { yylval.bval = 1; return T_TRUE_STORY; }
"false alarm"       { yylval.bval = 0; return T_FALSE_ALARM; }

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

{SCIENTIFIC}        { yylval.fval = atof(yytext); return T_DECIMAL; }
{HEX}               { yylval.ival = (int)strtol(yytext, NULL, 16); return T_NUMBER; }
{OCTAL}             { yylval.ival = (int)strtol(yytext, NULL, 8); return T_NUMBER; }
{FLOAT}             { yylval.fval = atof(yytext); return T_DECIMAL; }
{INTEGER}           { yylval.ival = atoi(yytext); return T_NUMBER; }
{IDENTIFIER}        { yylval.sval = duplicate_string(yytext); return T_ID; }

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

{WS}                { }
{NEWLINE}           { }
{SINGLE_COMMENT}    { }

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
