%{
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

%}

/* ========================================
 * BISON DECLARATIONS
 * ======================================== */
%union {
    int ival;
    float fval;
    char* sval;
    char cval;
    int bval;
    struct ASTNode* node;
}

/* Free discarded string semantic values during error recovery */
%destructor { free($$); } <sval>

/* Terminal tokens */
%token T_GO_LIVE T_END_LIVE
%token T_THE_ACCOUNT T_WAS_CREATED T_THE_POST T_THE_CAPTION T_THE_FOLLOWER T_THE_STORY
%token T_POSTED T_ABOUT T_THAT_HAD T_ANOTHER
%token T_STARTED_WITH T_BEGAN_AT T_NOW_HAS T_READS T_IS_VIRAL T_IS_TRENDING
%token T_GAINED T_LOST T_ADDED T_REMOVED T_INCREASED_BY T_DECREASED_BY
%token T_WAS_UPDATED_TO T_BECAME T_MULTIPLIED_BY T_DIVIDED_BY
%token T_PLUS T_MINUS T_TIMES T_MULTIPLY T_DIVIDED_EVENLY_BY T_DIVIDE T_MODULO
%token T_WITH T_AND_THEN T_FOR
%token T_THE_FEED T_CONTAINS T_AT_INDEX
%token T_LIKES T_FOLLOWERS T_VIEWS T_COMMENTS T_SHARES T_POSTS T_STORIES
%token T_ENGAGEMENT_RATE T_REACH T_GROWTH_RATE
%token T_WHEN T_OTHERWISE_IF T_OTHERWISE
%token T_WENT_VIRAL T_REACHED T_EXCEEDED T_DROPPED_BELOW T_STAYED_AT
%token T_MORE_THAN T_LESS_THAN T_EXACTLY T_AT_LEAST T_AT_MOST T_DIFFERENT_FROM
%token T_EQUAL_TO T_NOT_EQUAL_TO
%token T_EVERY_DAY_FOR T_EVERY T_DAYS T_INCREMENTING_BY T_DECREMENTING_BY
%token T_FOR_EACH T_POST_IN T_STORY_IN T_FOLLOWER_FROM T_TO
%token T_TRENDING_LOOP T_UNTIL
%token T_STOP_THE_STORY T_SKIP_THIS_POST
%token T_THE_STORY_OF T_BEGINS_WITH T_TELL_BACK T_THE_STORY_ENDS T_TELL
%token T_ANNOUNCE T_ASK_FOR T_DISPLAY
%token T_CALCULATE_VIRALITY T_CALCULATE_ENGAGEMENT T_FIND_TOP_POST
%token T_FIND_HIGHEST_REACH T_FIND_TOTAL_REACH T_COUNT_TOTAL_ENGAGEMENT
%token T_CHECK_IF_TRENDING T_ANALYZE_GROWTH T_FIND_MAX_VIRAL_ACCOUNT
%token T_REVERSE_THE_CAPTION T_DETECT_SPAM T_CLAMP_ENGAGEMENT
%token T_BETWEEN T_REVERSE_GROWTH
%token T_ALSO T_EITHER T_OPPOSITE
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_LBRACKET T_RBRACKET
%token T_COMMA T_DOT T_COLON

%token <ival> T_NUMBER
%token <fval> T_DECIMAL
%token <sval> T_TEXT T_ID
%token <cval> T_CHAR
%token <bval> T_TRUE_STORY T_FALSE_ALARM

/* Non-terminal types */
%type <node> program statements statement
%type <node> account_create account_init account_update story_post
%type <node> conditional loop loop_control
%type <node> function_def function_call builtin_call
%type <node> io_statement
%type <node> expression term factor
%type <node> comparison account_metric_ref
%type <node> metric literal
%type <node> optional_else else_if_chain
%type <node> param_list arg_list
%type <node> account_update_ext feed_statement

/* Operator precedence */
%nonassoc LOWER_THAN_OTHERWISE
%nonassoc T_OTHERWISE T_OTHERWISE_IF
%left T_ALSO T_EITHER
%right T_OPPOSITE
%left T_MORE_THAN T_LESS_THAN T_EXACTLY T_AT_LEAST T_AT_MOST T_DIFFERENT_FROM T_EQUAL_TO T_NOT_EQUAL_TO
%left T_PLUS T_MINUS
%left T_TIMES T_MULTIPLY T_DIVIDE T_DIVIDED_BY T_DIVIDED_EVENLY_BY T_MODULO

%%

/* ========================================
 * GRAMMAR RULES
 * ======================================== */

program:
    T_GO_LIVE T_DOT statements T_END_LIVE T_DOT
    {
        ast_root = make_node(AST_PROGRAM);
        ast_root->body = $3;
        $$ = ast_root;
        fprintf(output_file, "\n✅ Parse successful! AST built.\n");
    }
    | T_GO_LIVE T_DOT T_END_LIVE T_DOT
    {
        ast_root = make_node(AST_PROGRAM);
        ast_root->body = NULL;
        $$ = ast_root;
        fprintf(output_file, "\n✅ Parse successful! Empty program.\n");
    }
    ;

statements:
    statements statement
    {
        if ($1) {
            ASTNode* temp = $1;
            while (temp->next) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    | statement { $$ = $1; }
    ;

statement:
    account_create { $$ = $1; }
    | account_init { $$ = $1; }
    | account_update { $$ = $1; }
    | story_post { $$ = $1; }
    | conditional { $$ = $1; }
    | loop { $$ = $1; }
    | loop_control { $$ = $1; }
    | function_def { $$ = $1; }
    | function_call { $$ = $1; }
    | builtin_call { $$ = $1; }
    | io_statement { $$ = $1; }
    | account_update_ext { $$ = $1; }
    | feed_statement { $$ = $1; }
    | error T_DOT {
        fprintf(stderr, "⚠️ Syntax error at line %d: Skipping to next statement\n", yylineno);
        fprintf(output_file, "⚠️ Syntax error at line %d: Recovered\n", yylineno);
        yyerrok;
        semantic_errors++;
        $$ = NULL;
    }
    ;

account_create:
    T_THE_ACCOUNT T_ID T_WAS_CREATED T_DOT
    {
        $$ = make_node(AST_ACCOUNT_CREATE);
        $$->sval = $2;
        $$->line_number = yylineno;
        check_duplicate_account($2, yylineno);
        {
            SymbolEntry *existing = lookup_symbol($2);
            if (!(existing && existing->type == SYM_ACCOUNT))
            {
                insert_symbol($2, SYM_ACCOUNT);
            }
        }
    }
    ;

account_init:
    T_THE_ACCOUNT T_ID T_STARTED_WITH T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_NOW_HAS T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_BEGAN_AT T_DECIMAL metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->fval = $4;
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_NOW_HAS expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->left = $5;
        $$->right = $4;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    ;

account_update:
    T_THE_ACCOUNT T_ID T_GAINED expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->right = $4;   /* expression node */
        $$->ival = 0;     /* 0 = add */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_LOST expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->right = $4;   /* expression node */
        $$->ival = -1;    /* -1 = subtract */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_INCREASED_BY expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->right = $4;
        $$->ival = 0;
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_DECREASED_BY expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->right = $4;
        $$->ival = -1;    /* -1 = subtract */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    ;

story_post:
    T_THE_ACCOUNT T_ID T_POSTED T_ABOUT T_TEXT T_THAT_HAD T_NUMBER T_VIEWS T_DOT
    {
        $$ = make_node(AST_STORY_POST);
        $$->sval = $2;
        $$->left = make_node_with_string(AST_LITERAL_STRING, $5);
        $$->ival = $7;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_POSTED T_ABOUT T_TEXT T_DOT
    {
        $$ = make_node(AST_STORY_POST);
        $$->sval = $2;
        $$->left = make_node_with_string(AST_LITERAL_STRING, $5);
        $$->ival = 5000; // Default views
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    ;

conditional:
    T_WHEN comparison T_LBRACE statements T_RBRACE optional_else
    {
        $$ = make_node(AST_CONDITIONAL);
        $$->condition = $2;
        $$->body = $4;
        $$->else_body = $6;
        $$->line_number = yylineno;
    }
    | T_WHEN T_OPPOSITE comparison T_LBRACE statements T_RBRACE optional_else
    {
        /* NEW FEATURE: opposite (logical NOT) */
        $$ = make_node(AST_CONDITIONAL);
        ASTNode* not_node = make_node(AST_UNARY_OP);
        not_node->ival = 0; // NOT operation
        not_node->left = $3;
        $$->condition = not_node;
        $$->body = $5;
        $$->else_body = $7;
        $$->line_number = yylineno;
    }
    /* NEW FEATURE: Empty conditional blocks (A+ enhancement) */
    | T_WHEN comparison T_LBRACE T_RBRACE optional_else
    {
        $$ = make_node(AST_CONDITIONAL);
        $$->condition = $2;
        $$->body = NULL;  // Empty body allowed
        $$->else_body = $5;
        $$->line_number = yylineno;
        
        fprintf(output_file, "⚠️  Note at line %d: Empty conditional block detected\n", yylineno);
    }
    | T_WHEN T_OPPOSITE comparison T_LBRACE T_RBRACE optional_else
    {
        /* Empty conditional with opposite */
        $$ = make_node(AST_CONDITIONAL);
        ASTNode* not_node = make_node(AST_UNARY_OP);
        not_node->ival = 0; // NOT operation
        not_node->left = $3;
        $$->condition = not_node;
        $$->body = NULL;  // Empty body allowed
        $$->else_body = $6;
        $$->line_number = yylineno;
        
        fprintf(output_file, "⚠️  Note at line %d: Empty conditional block detected\n", yylineno);
    }
    | T_WHEN error T_LBRACE statements T_RBRACE {
        fprintf(stderr, "⚠️ Invalid condition at line %d\n", yylineno);
        yyerrok;
        semantic_errors++;
        $$ = NULL;
    }
    ;

optional_else:
    /* empty */ %prec LOWER_THAN_OTHERWISE { $$ = NULL; }
    | T_OTHERWISE T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_CONDITIONAL);
        $$->body = $3;
        $$->line_number = yylineno;
    }
    | else_if_chain { $$ = $1; }
    ;

else_if_chain:
    T_OTHERWISE_IF comparison T_LBRACE statements T_RBRACE optional_else
    {
        $$ = make_node(AST_CONDITIONAL);
        $$->condition = $2;
        $$->body = $4;
        $$->else_body = $6;
        $$->line_number = yylineno;
    }
    ;

comparison:
    /* NEW FEATURE: Account-specific comparisons */
    account_metric_ref T_MORE_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_GT;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_LESS_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_LT;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_EXACTLY expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_EQUAL_TO expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_NOT_EQUAL_TO expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_NEQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_AT_LEAST expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_GTE;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_AT_MOST expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_LTE;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_EXCEEDED expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_GT;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_DROPPED_BELOW expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_LT;
        $$->line_number = yylineno;
    }
    /* Global metric comparison (backward compatibility) */
    | metric T_MORE_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_GT;
        $$->line_number = yylineno;
    }
    | metric T_LESS_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_LT;
        $$->line_number = yylineno;
    }
    | metric T_EXACTLY expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    /* Expression comparisons (for modulo, arithmetic, etc.) */
    | expression T_MORE_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_GT;
        $$->line_number = yylineno;
    }
    | expression T_LESS_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_LT;
        $$->line_number = yylineno;
    }
    | expression T_EXACTLY expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    | expression T_EQUAL_TO expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    | expression T_NOT_EQUAL_TO expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_NEQ;
        $$->line_number = yylineno;
    }
    | expression T_AT_LEAST expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_GTE;
        $$->line_number = yylineno;
    }
    | expression T_AT_MOST expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_LTE;
        $$->line_number = yylineno;
    }
    | expression T_DIFFERENT_FROM expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_NEQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_DIFFERENT_FROM expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_NEQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_STAYED_AT expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_REACHED expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = CMP_EQ;
        $$->line_number = yylineno;
    }
    | account_metric_ref T_WENT_VIRAL
    {
        /* When likes went viral => likes > 1000 */
        ASTNode* threshold = make_node_with_int(AST_LITERAL_INT, 1000);
        $$ = make_binary_op(AST_COMPARISON, $1, threshold);
        $$->ival = CMP_GT;
        $$->line_number = yylineno;
    }
    | comparison T_ALSO comparison
    {
        $$ = make_binary_op(AST_LOGICAL_OP, $1, $3);
        $$->ival = 0; // AND
        $$->line_number = yylineno;
    }
    | comparison T_EITHER comparison
    {
        $$ = make_binary_op(AST_LOGICAL_OP, $1, $3);
        $$->ival = 1; // OR
        $$->line_number = yylineno;
    }
    ;

/* NEW: Account-specific metric reference */
account_metric_ref:
    T_ID metric
    {
        $$ = make_node(AST_ACCOUNT_REF);
        $$->sval = $1;
        $$->sval2 = $2->sval;
        $$->line_number = yylineno;
        check_account_exists($1, yylineno);
        free($2); // Free the temporary metric node
    }
    ;

loop:
    T_EVERY_DAY_FOR T_NUMBER T_DAYS T_COMMA T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP);
        $$->ival = 1;
        $$->ival2 = $2;
        $$->step = 1;
        $$->body = $6;
        $$->line_number = yylineno;
    }
    | T_EVERY T_NUMBER T_DAYS T_INCREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_INCREMENT);
        $$->ival = 1;
        $$->ival2 = $2;
        $$->step = $5;
        $$->body = $7;
        $$->line_number = yylineno;
    }
    | T_EVERY T_NUMBER T_DAYS T_DECREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_DECREMENT);
        $$->ival = $2;
        $$->ival2 = 1;
        $$->step = $5;
        $$->body = $7;
        $$->line_number = yylineno;
    }
    /* NEW FEATURE: For each follower from A to B range loop */
    | T_FOR_EACH T_FOLLOWER_FROM T_NUMBER T_TO T_NUMBER T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_RANGE);
        $$->ival = $3;
        $$->ival2 = $5;
        $$->step = 1;
        $$->body = $7;
        $$->line_number = yylineno;
    }
    /* NEW FEATURE: trending loop until CONDITION */
    | T_TRENDING_LOOP T_UNTIL comparison T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_TRENDING);
        $$->condition = $3;
        $$->body = $5;
        $$->line_number = yylineno;
    }
    ;

loop_control:
    T_STOP_THE_STORY T_DOT
    {
        $$ = make_node(AST_BREAK);
        $$->line_number = yylineno;
    }
    | T_SKIP_THIS_POST T_DOT
    {
        $$ = make_node(AST_CONTINUE);
        $$->line_number = yylineno;
    }
    ;

/* NEW FEATURE: Multiple function parameters */
function_def:
    T_THE_STORY_OF T_ID T_BEGINS_WITH param_list T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT
    {
        $$ = make_node(AST_FUNCTION_DEF);
        $$->sval = $2;
        $$->param = $4;
        $$->body = $6;
        $$->line_number = yylineno;
    }
    | T_THE_STORY_OF T_ID T_BEGINS_WITH T_ID T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT
    {
        $$ = make_node(AST_FUNCTION_DEF);
        $$->sval = $2;
        $$->param = make_node_with_string(AST_IDENTIFIER, $4);
        $$->body = $6;
        $$->line_number = yylineno;
    }
    | T_THE_STORY_OF T_ID T_BEGINS_WITH T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT
    {
        $$ = make_node(AST_FUNCTION_DEF);
        $$->sval = $2;
        $$->body = $5;
        $$->line_number = yylineno;
    }
    ;

param_list:
    T_ID T_COMMA param_list
    {
        $$ = make_node_with_string(AST_IDENTIFIER, $1);
        $$->next = $3;
    }
    | T_ID
    {
        $$ = make_node_with_string(AST_IDENTIFIER, $1);
    }
    ;

function_call:
    T_TELL T_ID T_WITH arg_list T_DOT
    {
        $$ = make_node(AST_FUNCTION_CALL);
        $$->sval = $2;
        $$->param = $4;
        $$->line_number = yylineno;
    }
    | T_TELL T_ID T_LPAREN arg_list T_RPAREN T_DOT
    {
        $$ = make_node(AST_FUNCTION_CALL);
        $$->sval = $2;
        $$->param = $4;
        $$->line_number = yylineno;
    }
    | T_TELL T_ID T_DOT
    {
        $$ = make_node(AST_FUNCTION_CALL);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    | T_TELL_BACK expression T_DOT
    {
        $$ = make_node(AST_RETURN);
        $$->left = $2;
        $$->line_number = yylineno;
    }
    ;

arg_list:
    expression T_COMMA arg_list
    {
        $$ = $1;
        $$->next = $3;
    }
    | expression
    {
        $$ = $1;
    }
    ;

builtin_call:
    T_CALCULATE_VIRALITY T_FOR T_THE_ACCOUNT T_ID T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("calculate_virality");
        $$->sval2 = $4;
        $$->line_number = yylineno;
    }
    | T_CALCULATE_VIRALITY T_LPAREN T_ID T_RPAREN T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("calculate_virality");
        $$->sval2 = $3;
        $$->line_number = yylineno;
    }
    | T_CALCULATE_ENGAGEMENT T_FOR T_THE_ACCOUNT T_ID T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("calculate_engagement");
        $$->sval2 = $4;
        $$->line_number = yylineno;
    }
    | T_ANALYZE_GROWTH T_FOR T_THE_ACCOUNT T_ID T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("analyze_growth");
        $$->sval2 = $4;
        $$->line_number = yylineno;
    }
    | T_ANALYZE_GROWTH T_LPAREN T_ID T_RPAREN T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("analyze_growth");
        $$->sval2 = $3;
        $$->line_number = yylineno;
    }
    | T_FIND_MAX_VIRAL_ACCOUNT T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_max_viral_account");
        $$->line_number = yylineno;
    }
    | T_FIND_MAX_VIRAL_ACCOUNT T_LPAREN T_ID T_COMMA T_ID T_RPAREN T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_max_viral_account");
        $$->line_number = yylineno;
    }
    /* NEW FEATURE: Reverse the caption */
    | T_REVERSE_THE_CAPTION T_LPAREN T_TEXT T_RPAREN T_DOT
    {
        $$ = make_node(AST_STRING_OP);
        $$->sval = strdup("reverse");
        $$->sval2 = $3;
        $$->line_number = yylineno;
    }
    /* Check if trending */
    | T_CHECK_IF_TRENDING T_FOR T_THE_ACCOUNT T_ID T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("check_if_trending");
        $$->sval2 = $4;
        $$->line_number = yylineno;
    }
    | T_CHECK_IF_TRENDING T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("check_if_trending");
        $$->line_number = yylineno;
    }
    /* Count total engagement */
    | T_COUNT_TOTAL_ENGAGEMENT T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("count_total_engagement");
        $$->line_number = yylineno;
    }
    /* Find top post */
    | T_FIND_TOP_POST T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_top_post");
        $$->line_number = yylineno;
    }
    /* Find the highest reach in the feed */
    | T_FIND_HIGHEST_REACH T_THE_FEED T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_highest_reach");
        $$->line_number = yylineno;
    }
    /* Find the total reach in the feed */
    | T_FIND_TOTAL_REACH T_THE_FEED T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_total_reach");
        $$->line_number = yylineno;
    }
    /* Detect spam in "TEXT" */
    | T_DETECT_SPAM T_TEXT T_DOT
    {
        $$ = make_node(AST_STRING_OP);
        $$->sval = strdup("detect_spam");
        $$->sval2 = $2;
        $$->line_number = yylineno;
    }
    /* Clamp engagement between MIN and MAX */
    | T_CLAMP_ENGAGEMENT T_NUMBER T_AND_THEN T_NUMBER T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("clamp_engagement");
        $$->ival = $2;
        $$->ival2 = $4;
        $$->line_number = yylineno;
    }
    | T_CLAMP_ENGAGEMENT T_DECIMAL T_AND_THEN T_DECIMAL T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("clamp_engagement");
        $$->fval = $2;
        $$->ival2 = (int)$4;
        $$->line_number = yylineno;
    }
    /* Reverse growth */
    | T_REVERSE_GROWTH T_FOR T_THE_ACCOUNT T_ID T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("reverse_growth");
        $$->sval2 = $4;
        $$->line_number = yylineno;
    }
    | T_REVERSE_GROWTH T_DOT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("reverse_growth");
        $$->line_number = yylineno;
    }
    ;

io_statement:
    T_ANNOUNCE T_TEXT T_DOT
    {
        $$ = make_node(AST_ANNOUNCE);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    | T_DISPLAY T_TEXT T_DOT
    {
        $$ = make_node(AST_ANNOUNCE);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    | T_DISPLAY T_ID T_DOT
    {
        $$ = make_node(AST_DISPLAY);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    | T_DISPLAY T_ID metric T_DOT
    {
        $$ = make_node(AST_DISPLAY);
        $$->sval = $2;
        $$->sval2 = $3->sval;
        $$->line_number = yylineno;
        free($3);
    }
    /* NEW FEATURE: Ask for VARIABLE (user input) */
    | T_ASK_FOR T_ID T_DOT
    {
        $$ = make_node(AST_ASK_FOR);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    | T_ANNOUNCE T_ID T_DOT
    {
        /* Display a variable's value via Announce */
        $$ = make_node(AST_DISPLAY);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    | T_DISPLAY T_THE_FEED T_AT_INDEX expression metric T_DOT
    {
        $$ = make_node(AST_FEED_DISPLAY);
        $$->left = $4;           /* index expression */
        $$->sval = $5->sval;     /* metric */
        $$->line_number = yylineno;
        free($5);
    }
    | T_DISPLAY T_THE_FEED T_DOT
    {
        $$ = make_node(AST_FEED_DISPLAY);
        $$->line_number = yylineno;
    }
    ;

/* ========================================
 * EXTENDED ACCOUNT UPDATE RULES
 * was updated to, became, multiplied by, divided by
 * Caption, viral/trending status
 * ======================================== */
account_update_ext:
    T_THE_ACCOUNT T_ID T_WAS_UPDATED_TO T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_BECAME T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_MULTIPLIED_BY T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival = $4;
        $$->ival2 = 1; /* flag: multiply */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_MULTIPLIED_BY expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->right = $4;
        $$->ival2 = 1; /* flag: multiply */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_DIVIDED_BY T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival = $4;
        $$->ival2 = 2; /* flag: divide */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_DIVIDED_BY expression metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->right = $4;
        $$->ival2 = 2; /* flag: divide */
        $$->left = $5;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_CAPTION T_READS T_TEXT T_DOT
    {
        /* Caption assignment */
        $$ = make_node(AST_ANNOUNCE);
        $$->sval = $3;
        $$->line_number = yylineno;
    }
    | T_THE_ACCOUNT T_ID T_IS_VIRAL T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival2 = 3; /* flag: set viral */
        $$->left = make_node_with_int(AST_LITERAL_INT, 1);
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("viral");
        $$->left = m;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_ACCOUNT T_ID T_IS_TRENDING T_DOT
    {
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival2 = 4; /* flag: set trending */
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("trending");
        $$->left = m;
        $$->line_number = yylineno;
        check_account_exists($2, yylineno);
    }
    | T_THE_POST T_ID T_STARTED_WITH T_NUMBER metric T_DOT
    {
        /* Post metrics (reuse account_init semantics) */
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    | T_THE_POST T_ID T_NOW_HAS T_NUMBER metric T_DOT
    {
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    ;

/* ========================================
 * FEED / COLLECTION STATEMENTS
 * The feed contains N posts/stories
 * For each post in the feed
 * For each story in the feed
 * ======================================== */
feed_statement:
    T_THE_FEED T_CONTAINS T_NUMBER T_POSTS T_DOT
    {
        $$ = make_node(AST_FEED_DECLARE);
        $$->ival = $3;
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("posts");
        $$->left = m;
        $$->line_number = yylineno;
    }
    | T_THE_FEED T_CONTAINS T_NUMBER T_STORIES T_DOT
    {
        $$ = make_node(AST_FEED_DECLARE);
        $$->ival = $3;
        ASTNode* m = make_node(AST_METRIC);
        m->sval = strdup("stories");
        $$->left = m;
        $$->line_number = yylineno;
    }
    | T_THE_FEED T_AT_INDEX expression T_NOW_HAS expression metric T_DOT
    {
        $$ = make_node(AST_FEED_SET);
        $$->left = $3;            /* index expression */
        $$->right = $5;           /* value expression */
        $$->sval = $6->sval;      /* metric */
        $$->line_number = yylineno;
        free($6);
    }
    | T_THE_FEED T_AT_INDEX expression T_STARTED_WITH expression metric T_DOT
    {
        $$ = make_node(AST_FEED_SET);
        $$->left = $3;            /* index expression */
        $$->right = $5;           /* value expression */
        $$->sval = $6->sval;      /* metric */
        $$->line_number = yylineno;
        free($6);
    }
    | T_FOR_EACH T_POST_IN T_THE_FEED T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_COLLECTION);
        $$->sval = strdup("post");
        $$->body = $5;
        $$->line_number = yylineno;
    }
    | T_FOR_EACH T_STORY_IN T_THE_FEED T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_COLLECTION);
        $$->sval = strdup("story");
        $$->body = $5;
        $$->line_number = yylineno;
    }
    ;

expression:
    term { $$ = $1; }
    | expression T_PLUS term
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_ADD;
        $$->line_number = yylineno;
    }
    | expression T_MINUS term
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_SUB;
        $$->line_number = yylineno;
    }
    ;

term:
    factor { $$ = $1; }
    | term T_TIMES factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_MUL;
        $$->line_number = yylineno;
    }
    | term T_MULTIPLY factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_MUL;
        $$->line_number = yylineno;
    }
    | term T_DIVIDED_BY factor
    {
    $$ = make_binary_op(AST_BINARY_OP, $1, $3);
    $$->ival = OP_DIV;
    $$->line_number = yylineno;
    }
    | term T_DIVIDE factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_DIV;
        $$->line_number = yylineno;
    }
    | term T_DIVIDED_EVENLY_BY factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_DIV;
        $$->line_number = yylineno;
    }
    | term T_MODULO factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = OP_MOD;
        $$->line_number = yylineno;
    }
    ;

factor:
    literal { $$ = $1; }
    | account_metric_ref { $$ = $1; } 
    | metric { $$ = $1; }
    | T_ID { $$ = make_node_with_string(AST_IDENTIFIER, $1); }
    | T_THE_FEED T_AT_INDEX expression metric
    {
        $$ = make_node(AST_FEED_GET);
        $$->left = $3;           /* index expression */
        $$->sval = $4->sval;     /* metric */
        $$->line_number = yylineno;
        free($4);
    }
    | T_THE_FEED T_CONTAINS T_POSTS
    {
        $$ = make_node(AST_FEED_LENGTH);
        $$->sval = strdup("posts");
        $$->line_number = yylineno;
    }
    | T_THE_FEED T_CONTAINS T_STORIES
    {
        $$ = make_node(AST_FEED_LENGTH);
        $$->sval = strdup("stories");
        $$->line_number = yylineno;
    }
    | T_LPAREN expression T_RPAREN { $$ = $2; }
    ;

metric:
    T_LIKES
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("likes");
        $$->line_number = yylineno;
    }
    | T_FOLLOWERS
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("followers");
        $$->line_number = yylineno;
    }
    | T_VIEWS
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("views");
        $$->line_number = yylineno;
    }
    | T_COMMENTS
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("comments");
        $$->line_number = yylineno;
    }
    | T_SHARES
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("shares");
        $$->line_number = yylineno;
    }
    | T_REACH
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("reach");
        $$->line_number = yylineno;
    }
    | T_ENGAGEMENT_RATE
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("engagement rate");
        $$->line_number = yylineno;
    }
    | T_GROWTH_RATE
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("growth rate");
        $$->line_number = yylineno;
    }
    | T_POSTS
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("posts");
        $$->line_number = yylineno;
    }
    | T_STORIES
    {
        $$ = make_node(AST_METRIC);
        $$->sval = strdup("stories");
        $$->line_number = yylineno;
    }
    ;

literal:
    T_NUMBER
    {
        $$ = make_node_with_int(AST_LITERAL_INT, $1);
        $$->line_number = yylineno;
    }
    | T_DECIMAL
    {
        $$ = make_node_with_float(AST_LITERAL_FLOAT, $1);
        $$->line_number = yylineno;
    }
    | T_TEXT
    {
        $$ = make_node_with_string(AST_LITERAL_STRING, $1);
        $$->line_number = yylineno;
    }
    | T_TRUE_STORY
    {
        $$ = make_node_with_int(AST_LITERAL_BOOL, 1);
        $$->line_number = yylineno;
    }
    | T_FALSE_ALARM
    {
        $$ = make_node_with_int(AST_LITERAL_BOOL, 0);
        $$->line_number = yylineno;
    }
    ;

%%

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

/* ========================================
 * MAIN FUNCTION
 * ======================================== */
/* main() has been moved to main.c for cleaner code organization. */

/* ============================================================
 * compiler_run() — Full compiler pipeline
 * Called by main.c after files are opened.
 * Returns 0 on success, 1 on error.
 * ============================================================ */
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
