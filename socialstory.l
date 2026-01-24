%{
/*
 * SocialStoryScript Lexical Analyzer
 * A unique narrative programming language inspired by social media storytelling
 * Author: Your Name
 * Date: January 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socialstory_tokens.h"

/* Function prototypes */
int yylex(void);
static char* duplicate_string(const char* s);
static void print_token(int token, const char* name);

/* Global variables */
YYSTYPE yylval;
extern FILE *yyin;
FILE *yyout = NULL;

/* String duplication utility */
static char* duplicate_string(const char* s) {
    size_t len = strlen(s) + 1;
    char* copy = (char*)malloc(len);
    if (!copy) {
        fprintf(stderr, "ERROR: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copy, s, len);
    return copy;
}

/* Token printing utility */
static void print_token(int token, const char* name) {
    fprintf(yyout, "%-30s | Line %-4d | Token: %s\n", yytext, yylineno, name);
}

%}

/* Flex options */
%option noyywrap
%option yylineno
%option case-insensitive

/* Regular expression definitions */
WHITESPACE      [ \t\r]+
NEWLINE         \n
DIGIT           [0-9]
LETTER          [A-Za-z]
IDENTIFIER      {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER         {DIGIT}+
DECIMAL         {DIGIT}+\.{DIGIT}+
STRING          \"([^\\\"\n]|\\.)*\"
COMMENT         ("//".*|"#".*)

%%

    /* ==================== PROGRAM STRUCTURE ==================== */
"Go live"(".")?                 { print_token(T_GO_LIVE, "GO_LIVE"); return T_GO_LIVE; }
"End live"(".")?                { print_token(T_END_LIVE, "END_LIVE"); return T_END_LIVE; }

    /* ==================== ACCOUNT & NARRATIVE ==================== */
"The account"                   { print_token(T_THE_ACCOUNT, "THE_ACCOUNT"); return T_THE_ACCOUNT; }
"was created"(".")?             { print_token(T_WAS_CREATED, "WAS_CREATED"); return T_WAS_CREATED; }
"The post"                      { print_token(T_THE_POST, "THE_POST"); return T_THE_POST; }
"The caption"                   { print_token(T_THE_CAPTION, "THE_CAPTION"); return T_THE_CAPTION; }
"The follower"                  { print_token(T_THE_FOLLOWER, "THE_FOLLOWER"); return T_THE_FOLLOWER; }

    /* ==================== INITIALIZATION VERBS ==================== */
"started with"                  { print_token(T_STARTED_WITH, "STARTED_WITH"); return T_STARTED_WITH; }
"began at"                      { print_token(T_BEGAN_AT, "BEGAN_AT"); return T_BEGAN_AT; }
"now has"                       { print_token(T_NOW_HAS, "NOW_HAS"); return T_NOW_HAS; }
"reads"                         { print_token(T_READS, "READS"); return T_READS; }
"is viral"(".")?                { print_token(T_IS_VIRAL, "IS_VIRAL"); return T_IS_VIRAL; }
"is trending"(".")?             { print_token(T_IS_TRENDING, "IS_TRENDING"); return T_IS_TRENDING; }

    /* ==================== UPDATE VERBS ==================== */
"gained"                        { print_token(T_GAINED, "GAINED"); return T_GAINED; }
"lost"                          { print_token(T_LOST, "LOST"); return T_LOST; }
"increased by"                  { print_token(T_INCREASED_BY, "INCREASED_BY"); return T_INCREASED_BY; }
"decreased by"                  { print_token(T_DECREASED_BY, "DECREASED_BY"); return T_DECREASED_BY; }
"was updated to"                { print_token(T_WAS_UPDATED_TO, "WAS_UPDATED_TO"); return T_WAS_UPDATED_TO; }
"became"                        { print_token(T_BECAME, "BECAME"); return T_BECAME; }

    /* ==================== DATA STRUCTURES ==================== */
"contains"                      { print_token(T_CONTAINS, "CONTAINS"); return T_CONTAINS; }
"the feed"                      { print_token(T_THE_FEED, "THE_FEED"); return T_THE_FEED; }
"at index"                      { print_token(T_AT_INDEX, "AT_INDEX"); return T_AT_INDEX; }

    /* ==================== TYPE KEYWORDS ==================== */
"likes"                         { print_token(T_LIKES, "LIKES"); return T_LIKES; }
"followers"                     { print_token(T_FOLLOWERS, "FOLLOWERS"); return T_FOLLOWERS; }
"views"                         { print_token(T_VIEWS, "VIEWS"); return T_VIEWS; }
"comments"                      { print_token(T_COMMENTS, "COMMENTS"); return T_COMMENTS; }
"shares"                        { print_token(T_SHARES, "SHARES"); return T_SHARES; }
"engagement rate"               { print_token(T_ENGAGEMENT_RATE, "ENGAGEMENT_RATE"); return T_ENGAGEMENT_RATE; }
"reach"                         { print_token(T_REACH, "REACH"); return T_REACH; }

    /* ==================== CONDITIONALS ==================== */
"When"                          { print_token(T_WHEN, "WHEN"); return T_WHEN; }
"Otherwise if"                  { print_token(T_OTHERWISE_IF, "OTHERWISE_IF"); return T_OTHERWISE_IF; }
"Otherwise"                     { print_token(T_OTHERWISE, "OTHERWISE"); return T_OTHERWISE; }
"went viral"                    { print_token(T_WENT_VIRAL, "WENT_VIRAL"); return T_WENT_VIRAL; }
"reached"                       { print_token(T_REACHED, "REACHED"); return T_REACHED; }
"exceeded"                      { print_token(T_EXCEEDED, "EXCEEDED"); return T_EXCEEDED; }
"dropped below"                 { print_token(T_DROPPED_BELOW, "DROPPED_BELOW"); return T_DROPPED_BELOW; }
"stayed at"                     { print_token(T_STAYED_AT, "STAYED_AT"); return T_STAYED_AT; }

    /* ==================== COMPARISON OPERATORS ==================== */
"more than"                     { print_token(T_MORE_THAN, "MORE_THAN"); return T_MORE_THAN; }
"less than"                     { print_token(T_LESS_THAN, "LESS_THAN"); return T_LESS_THAN; }
"exactly"                       { print_token(T_EXACTLY, "EXACTLY"); return T_EXACTLY; }
"at least"                      { print_token(T_AT_LEAST, "AT_LEAST"); return T_AT_LEAST; }
"at most"                       { print_token(T_AT_MOST, "AT_MOST"); return T_AT_MOST; }
"different from"                { print_token(T_DIFFERENT_FROM, "DIFFERENT_FROM"); return T_DIFFERENT_FROM; }

    /* ==================== LOOPS ==================== */
"Every day for"                 { print_token(T_EVERY_DAY_FOR, "EVERY_DAY_FOR"); return T_EVERY_DAY_FOR; }
"days"(","|".")?                { print_token(T_DAYS, "DAYS"); return T_DAYS; }
"For each"                      { print_token(T_FOR_EACH, "FOR_EACH"); return T_FOR_EACH; }
"post in"                       { print_token(T_POST_IN, "POST_IN"); return T_POST_IN; }
"follower from"                 { print_token(T_FOLLOWER_FROM, "FOLLOWER_FROM"); return T_FOLLOWER_FROM; }
"to"                            { print_token(T_TO, "TO"); return T_TO; }
"trending loop"                 { print_token(T_TRENDING_LOOP, "TRENDING_LOOP"); return T_TRENDING_LOOP; }
"until"                         { print_token(T_UNTIL, "UNTIL"); return T_UNTIL; }

    /* ==================== LOOP CONTROL ==================== */
"Stop the story"(".")?          { print_token(T_STOP_THE_STORY, "STOP_THE_STORY"); return T_STOP_THE_STORY; }
"Skip this post"(".")?          { print_token(T_SKIP_THIS_POST, "SKIP_THIS_POST"); return T_SKIP_THIS_POST; }

    /* ==================== FUNCTIONS ==================== */
"The story of"                  { print_token(T_THE_STORY_OF, "THE_STORY_OF"); return T_THE_STORY_OF; }
"begins with"                   { print_token(T_BEGINS_WITH, "BEGINS_WITH"); return T_BEGINS_WITH; }
"Tell back"                     { print_token(T_TELL_BACK, "TELL_BACK"); return T_TELL_BACK; }
"The story ends"(".")?          { print_token(T_THE_STORY_ENDS, "THE_STORY_ENDS"); return T_THE_STORY_ENDS; }
"Tell"                          { print_token(T_TELL, "TELL"); return T_TELL; }

    /* ==================== INPUT/OUTPUT ==================== */
"Announce"                      { print_token(T_ANNOUNCE, "ANNOUNCE"); return T_ANNOUNCE; }
"Ask for"                       { print_token(T_ASK_FOR, "ASK_FOR"); return T_ASK_FOR; }
"Display"                       { print_token(T_DISPLAY, "DISPLAY"); return T_DISPLAY; }

    /* ==================== BUILT-IN FUNCTIONS ==================== */
"Calculate virality"            { print_token(T_CALCULATE_VIRALITY, "CALCULATE_VIRALITY"); return T_CALCULATE_VIRALITY; }
"Find top post"                 { print_token(T_FIND_TOP_POST, "FIND_TOP_POST"); return T_FIND_TOP_POST; }
"Count total engagement"        { print_token(T_COUNT_TOTAL_ENGAGEMENT, "COUNT_TOTAL_ENGAGEMENT"); return T_COUNT_TOTAL_ENGAGEMENT; }
"Check if trending"             { print_token(T_CHECK_IF_TRENDING, "CHECK_IF_TRENDING"); return T_CHECK_IF_TRENDING; }
"Analyze growth"                { print_token(T_ANALYZE_GROWTH, "ANALYZE_GROWTH"); return T_ANALYZE_GROWTH; }

    /* ==================== BOOLEAN LITERALS ==================== */
"true story"                    { yylval.bval = 1; print_token(T_TRUE_STORY, "TRUE_STORY"); return T_TRUE_STORY; }
"false alarm"                   { yylval.bval = 0; print_token(T_FALSE_ALARM, "FALSE_ALARM"); return T_FALSE_ALARM; }

    /* ==================== LOGICAL OPERATORS ==================== */
"also"                          { print_token(T_ALSO, "ALSO"); return T_ALSO; }
"either"                        { print_token(T_EITHER, "EITHER"); return T_EITHER; }
"opposite"                      { print_token(T_OPPOSITE, "OPPOSITE"); return T_OPPOSITE; }

    /* ==================== PUNCTUATION ==================== */
"("                             { print_token(T_LPAREN, "LPAREN"); return T_LPAREN; }
")"                             { print_token(T_RPAREN, "RPAREN"); return T_RPAREN; }
"{"                             { print_token(T_LBRACE, "LBRACE"); return T_LBRACE; }
"}"                             { print_token(T_RBRACE, "RBRACE"); return T_RBRACE; }
"["                             { print_token(T_LBRACKET, "LBRACKET"); return T_LBRACKET; }
"]"                             { print_token(T_RBRACKET, "RBRACKET"); return T_RBRACKET; }
","                             { print_token(T_COMMA, "COMMA"); return T_COMMA; }
"."                             { print_token(T_DOT, "DOT"); return T_DOT; }
":"                             { print_token(T_COLON, "COLON"); return T_COLON; }
";"                             { print_token(T_SEMICOLON, "SEMICOLON"); return T_SEMICOLON; }

    /* ==================== ARITHMETIC OPERATORS ==================== */
"+"                             { print_token(T_PLUS, "PLUS"); return T_PLUS; }
"-"                             { print_token(T_MINUS, "MINUS"); return T_MINUS; }
"*"                             { print_token(T_MULTIPLY, "MULTIPLY"); return T_MULTIPLY; }
"/"                             { print_token(T_DIVIDE, "DIVIDE"); return T_DIVIDE; }
"%"                             { print_token(T_PERCENT, "PERCENT"); return T_PERCENT; }

    /* ==================== ASSIGNMENT ==================== */
"="                             { print_token(T_EQUALS, "EQUALS"); return T_EQUALS; }

    /* ==================== LITERALS ==================== */
{DECIMAL}                       { 
                                  yylval.fval = atof(yytext); 
                                  print_token(T_DECIMAL, "DECIMAL"); 
                                  return T_DECIMAL; 
                                }

{INTEGER}                       { 
                                  yylval.ival = atoi(yytext); 
                                  print_token(T_NUMBER, "NUMBER"); 
                                  return T_NUMBER; 
                                }

{STRING}                        { 
                                  size_t len = strlen(yytext);
                                  char* str = (char*)malloc(len - 1);
                                  if (!str) {
                                      fprintf(stderr, "ERROR: Memory allocation failed\n");
                                      exit(EXIT_FAILURE);
                                  }
                                  strncpy(str, yytext + 1, len - 2);
                                  str[len - 2] = '\0';
                                  yylval.sval = str;
                                  print_token(T_TEXT, "TEXT");
                                  return T_TEXT;
                                }

{IDENTIFIER}                    { 
                                  yylval.sval = duplicate_string(yytext); 
                                  print_token(T_ID, "IDENTIFIER"); 
                                  return T_ID; 
                                }

    /* ==================== IGNORE ==================== */
{WHITESPACE}                    { /* Ignore whitespace */ }
{NEWLINE}                       { /* Ignore newlines */ }
{COMMENT}                       { /* Ignore comments */ }

    /* ==================== ERROR HANDLING ==================== */
.                               { 
                                  fprintf(stderr, "\n╔══════════════════════════════════════╗\n");
                                  fprintf(stderr, "║  LEXICAL ERROR DETECTED!            ║\n");
                                  fprintf(stderr, "╠══════════════════════════════════════╣\n");
                                  fprintf(stderr, "║  Line: %-28d ║\n", yylineno);
                                  fprintf(stderr, "║  Unexpected character: '%-11s' ║\n", yytext);
                                  fprintf(stderr, "╚══════════════════════════════════════╝\n\n");
                                  fprintf(yyout, "\nLEXICAL ERROR at line %d: Unexpected '%s'\n", yylineno, yytext);
                                }

%%

/* ==================== MAIN DRIVER ==================== */
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "\n╔═══════════════════════════════════════════════════╗\n");
        fprintf(stderr, "║  SocialStoryScript Lexical Analyzer              ║\n");
        fprintf(stderr, "║  A Narrative Social Media Programming Language   ║\n");
        fprintf(stderr, "╠═══════════════════════════════════════════════════╣\n");
        fprintf(stderr, "║  Usage: %s <input_file> <output_file>     ║\n", argv[0]);
        fprintf(stderr, "╚═══════════════════════════════════════════════════╝\n\n");
        return EXIT_FAILURE;
    }

    /* Open input file */
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "ERROR: Cannot open input file '%s'\n", argv[1]);
        perror("fopen");
        return EXIT_FAILURE;
    }

    /* Open output file */
    yyout = fopen(argv[2], "w");
    if (!yyout) {
        fprintf(stderr, "ERROR: Cannot open output file '%s'\n", argv[2]);
        perror("fopen");
        fclose(yyin);
        return EXIT_FAILURE;
    }

    /* Print header */
    fprintf(yyout, "╔═══════════════════════════════════════════════════════════════════════╗\n");
    fprintf(yyout, "║            SocialStoryScript Lexical Analysis Report                 ║\n");
    fprintf(yyout, "╠═══════════════════════════════════════════════════════════════════════╣\n");
    fprintf(yyout, "║  Input File:  %-56s║\n", argv[1]);
    fprintf(yyout, "║  Output File: %-56s║\n", argv[2]);
    fprintf(yyout, "╚═══════════════════════════════════════════════════════════════════════╝\n\n");
    fprintf(yyout, "%-30s | %-9s | %s\n", "LEXEME", "LINE NO.", "TOKEN TYPE");
    fprintf(yyout, "══════════════════════════════════════════════════════════════════════════\n");

    /* Run lexical analysis */
    int token_count = 0;
    int token;
    while ((token = yylex()) != 0) {
        token_count++;
    }

    /* Print footer */
    fprintf(yyout, "══════════════════════════════════════════════════════════════════════════\n");
    fprintf(yyout, "\n╔═══════════════════════════════════════╗\n");
    fprintf(yyout, "║  Lexical Analysis Complete!          ║\n");
    fprintf(yyout, "╠═══════════════════════════════════════╣\n");
    fprintf(yyout, "║  Total Tokens: %-22d ║\n", token_count);
    fprintf(yyout, "║  Total Lines:  %-22d ║\n", yylineno);
    fprintf(yyout, "╚═══════════════════════════════════════╝\n");

    printf("\n✓ Lexical analysis completed successfully!\n");
    printf("  Tokens analyzed: %d\n", token_count);
    printf("  Lines processed: %d\n", yylineno);
    printf("  Output saved to: %s\n\n", argv[2]);

    /* Cleanup */
    fclose(yyin);
    fclose(yyout);
    
    return EXIT_SUCCESS;
}