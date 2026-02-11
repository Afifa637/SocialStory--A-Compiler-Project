%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "socialstory_tokens.h"

/* Forward declarations */
void yyerror(const char *s);
int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern int error_count;
extern char* yytext;

/* Output file for structured output */
FILE* output_file = NULL;

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
    AST_METRIC,
    AST_ACCOUNT_REF
} ASTNodeType;

/* AST Node Structure */
typedef struct ASTNode {
    ASTNodeType type;
    
    /* Value holders */
    int ival;
    int ival2;  /* For loop end value */
    int step;   /* For loop step */
    float fval;
    char* sval;
    char* sval2; /* For additional string (like account name in builtin) */
    
    /* Node connections */
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* condition;
    struct ASTNode* body;
    struct ASTNode* else_body;
    struct ASTNode* next;
    struct ASTNode* param;  /* For function parameters */
    
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
void print_symbol_table_to_file(FILE* fp);
void free_symbol_table();

/* Semantic analysis */
void check_account_exists(const char* name, int line);
void check_duplicate_account(const char* name, int line);

/* Interpreter */
void execute(ASTNode* node);
void execute_statements(ASTNode* node);
int evaluate_expression(ASTNode* node);

/* Output functions */
void output_to_terminal(const char* format, ...);
void output_to_file(const char* format, ...);

%}

%union {
    int ival;
    float fval;
    char* sval;
    char cval;
    int bval;
    struct ASTNode* node;
}

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
%type <node> comparison
%type <node> metric literal
%type <node> optional_else else_if_chain
%type <node> account_ref

/* Operator precedence */
%left T_ALSO T_EITHER
%left T_MORE_THAN T_LESS_THAN T_EXACTLY T_AT_LEAST T_AT_MOST T_DIFFERENT_FROM
%left T_PLUS T_MINUS
%left T_TIMES T_MULTIPLY T_DIVIDE T_DIVIDED_EVENLY_BY T_MODULO
%right T_OPPOSITE
%%

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
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* temp = $1;
            while (temp->next != NULL) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        }
    }
    | statement
    {
        $$ = $1;
    }
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
    | function_call T_DOT { $$ = $1; }
    | builtin_call T_DOT { $$ = $1; }
    | io_statement { $$ = $1; }
    | T_DOT
    {
        $$ = NULL;
    }
    | error T_DOT
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Invalid statement near '%s'", yytext);
        yyerror(msg);
        yyerrok;
        $$ = NULL;
    }
    ;

/* Account operations */
account_create:
    T_THE_ACCOUNT T_ID T_WAS_CREATED T_DOT
    {
        check_duplicate_account($2, yylineno);
        $$ = make_node(AST_ACCOUNT_CREATE);
        $$->sval = $2;
        $$->line_number = yylineno;
        insert_symbol($2, SYM_ACCOUNT);
    }
    ;

account_init:
    T_THE_ACCOUNT T_ID T_STARTED_WITH T_NUMBER metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    | T_THE_ACCOUNT T_ID T_BEGAN_AT T_DECIMAL metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->fval = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    | T_THE_ACCOUNT T_ID T_NOW_HAS T_NUMBER metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_INIT);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    ;

account_update:
    T_THE_ACCOUNT T_ID T_GAINED T_NUMBER metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    | T_THE_ACCOUNT T_ID T_LOST T_NUMBER metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival = -$4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    | T_THE_ACCOUNT T_ID T_INCREASED_BY T_NUMBER metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival = $4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    | T_THE_ACCOUNT T_ID T_DECREASED_BY T_NUMBER metric T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_ACCOUNT_UPDATE);
        $$->sval = $2;
        $$->ival = -$4;
        $$->left = $5;
        $$->line_number = yylineno;
    }
    ;

story_post:
    T_THE_ACCOUNT T_ID T_POSTED T_ABOUT T_TEXT T_THAT_HAD T_NUMBER T_VIEWS T_DOT
    {
        check_account_exists($2, yylineno);
        $$ = make_node(AST_STORY_POST);
        $$->sval = $2;
        $$->left = make_node_with_string(AST_LITERAL_STRING, $5);
        $$->ival = $7;
        $$->line_number = yylineno;
    }
    ;

/* Conditionals */
conditional:
    T_WHEN comparison T_LBRACE statements T_RBRACE optional_else
    {
        $$ = make_node(AST_CONDITIONAL);
        $$->condition = $2;
        $$->body = $4;
        $$->else_body = $6;
        $$->line_number = yylineno;
    }
    ;

optional_else:
    /* empty */ { $$ = NULL; }
    | T_OTHERWISE T_LBRACE statements T_RBRACE
    {
        $$ = $3;
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

/* Loops - FIXED with proper start, end, step */
loop:
    T_EVERY_DAY_FOR T_NUMBER T_DAYS T_COMMA T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP);
        $$->ival = 1;        /* start */
        $$->ival2 = $2;      /* end */
        $$->step = 1;        /* step */
        $$->body = $6;
        $$->line_number = yylineno;
    }
    | T_EVERY T_NUMBER T_DAYS T_INCREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_INCREMENT);
        $$->ival = 1;        /* start at 1 */
        $$->ival2 = $2;      /* end at this value */
        $$->step = $5;       /* increment by this */
        $$->body = $7;
        $$->line_number = yylineno;
    }
    | T_EVERY T_NUMBER T_DAYS T_DECREMENTING_BY T_NUMBER T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_DECREMENT);
        $$->ival = $2;       /* start at this value */
        $$->ival2 = 1;       /* end at 1 */
        $$->step = $5;       /* decrement by this */
        $$->body = $7;
        $$->line_number = yylineno;
    }
    | T_FOR_EACH T_FOLLOWER_FROM T_NUMBER T_TO T_NUMBER T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_RANGE);
        $$->ival = $3;       /* start */
        $$->ival2 = $5;      /* end */
        $$->step = 1;        /* step */
        $$->body = $7;
        $$->line_number = yylineno;
    }
    | T_FOR_EACH T_POST_IN T_THE_FEED T_LBRACE statements T_RBRACE
    {
        $$ = make_node(AST_LOOP_COLLECTION);
        $$->sval = strdup("posts");
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

/* Account reference for builtin functions */
account_ref:
    T_FOR T_THE_ACCOUNT T_ID
    {
        check_account_exists($3, yylineno);
        $$ = make_node(AST_ACCOUNT_REF);
        $$->sval = $3;
        $$->line_number = yylineno;
    }
    ;

/* Functions */
function_def:
    T_THE_STORY_OF T_ID T_BEGINS_WITH T_ID T_LBRACE statements T_RBRACE T_THE_STORY_ENDS T_DOT
    {
        $$ = make_node(AST_FUNCTION_DEF);
        $$->sval = $2;
        $$->left = make_node_with_string(AST_IDENTIFIER, $4);
        $$->body = $6;
        $$->line_number = yylineno;
        insert_symbol($2, SYM_FUNCTION);
    }
    ;

function_call:
    T_TELL T_ID T_LPAREN expression T_RPAREN
    {
        $$ = make_node(AST_FUNCTION_CALL);
        $$->sval = $2;
        $$->left = $4;
        $$->line_number = yylineno;
    }
    ;

/* Built-in functions - FIXED to require account parameters */
builtin_call:
    T_CALCULATE_VIRALITY account_ref
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("calculate_virality");
        $$->sval2 = $2->sval;  /* account name */
        $$->line_number = yylineno;
        free($2);
    }
    | T_CALCULATE_ENGAGEMENT account_ref
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("calculate_engagement");
        $$->sval2 = $2->sval;  /* account name */
        $$->line_number = yylineno;
        free($2);
    }
    | T_FIND_TOP_POST account_ref
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_top_post");
        $$->sval2 = $2->sval;  /* account name */
        $$->line_number = yylineno;
        free($2);
    }
    | T_FIND_MAX_VIRAL_ACCOUNT
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_max_viral_account");
        $$->sval2 = NULL;  /* works on all accounts */
        $$->line_number = yylineno;
    }
    | T_REVERSE_THE_CAPTION account_ref
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("reverse_caption");
        $$->sval2 = $2->sval;  /* account name */
        $$->line_number = yylineno;
        free($2);
    }
    | T_ANALYZE_GROWTH account_ref
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("analyze_growth");
        $$->sval2 = $2->sval;  /* account name */
        $$->line_number = yylineno;
        free($2);
    }
    | T_FIND_HIGHEST_REACH account_ref
    {
        $$ = make_node(AST_BUILTIN_CALL);
        $$->sval = strdup("find_highest_reach");
        $$->sval2 = $2->sval;  /* account name */
        $$->line_number = yylineno;
        free($2);
    }
    ;

/* I/O */
io_statement:
    T_ANNOUNCE T_TEXT T_DOT
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
    | T_ASK_FOR T_ID T_DOT
    {
        $$ = make_node(AST_ASK_FOR);
        $$->sval = $2;
        $$->line_number = yylineno;
    }
    ;

/* Expressions */
expression:
    expression T_PLUS term
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = '+';
    }
    | expression T_MINUS term
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = '-';
    }
    | term { $$ = $1; }
    ;

term:
    term T_TIMES factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = '*';
    }
    | term T_DIVIDE factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = '/';
    }
    | term T_MODULO factor
    {
        $$ = make_binary_op(AST_BINARY_OP, $1, $3);
        $$->ival = '%';
    }
    | factor { $$ = $1; }
    ;

factor:
    T_LPAREN expression T_RPAREN { $$ = $2; }
    | literal { $$ = $1; }
    | T_ID
    {
        $$ = make_node(AST_IDENTIFIER);
        $$->sval = $1;
    }
    | metric { $$ = $1; }
    ;

/* Comparisons */
comparison:
    expression T_MORE_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = '>';
    }
    | expression T_LESS_THAN expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = '<';
    }
    | expression T_EXACTLY expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = '=';
    }
    | expression T_AT_LEAST expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = 'G';
    }
    | expression T_AT_MOST expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = 'L';
    }
    | expression T_DIFFERENT_FROM expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = '!';
    }
    | expression T_EXCEEDED expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = '>';
    }
    | expression T_DROPPED_BELOW expression
    {
        $$ = make_binary_op(AST_COMPARISON, $1, $3);
        $$->ival = '<';
    }
    | expression T_WENT_VIRAL
    {
        $$ = make_node(AST_COMPARISON);
        $$->left = $1;
        $$->ival = 'V';
    }
    | metric T_MORE_THAN T_NUMBER
    {
        $$ = make_binary_op(AST_COMPARISON, $1, make_node_with_int(AST_LITERAL_INT, $3));
        $$->ival = '>';
    }
    | metric T_LESS_THAN T_NUMBER
    {
        $$ = make_binary_op(AST_COMPARISON, $1, make_node_with_int(AST_LITERAL_INT, $3));
        $$->ival = '<';
    }
    ;

/* Metrics */
metric:
    T_LIKES { $$ = make_node_with_string(AST_METRIC, strdup("likes")); }
    | T_FOLLOWERS { $$ = make_node_with_string(AST_METRIC, strdup("followers")); }
    | T_VIEWS { $$ = make_node_with_string(AST_METRIC, strdup("views")); }
    | T_COMMENTS { $$ = make_node_with_string(AST_METRIC, strdup("comments")); }
    | T_SHARES { $$ = make_node_with_string(AST_METRIC, strdup("shares")); }
    | T_POSTS { $$ = make_node_with_string(AST_METRIC, strdup("posts")); }
    | T_STORIES { $$ = make_node_with_string(AST_METRIC, strdup("stories")); }
    | T_ENGAGEMENT_RATE { $$ = make_node_with_string(AST_METRIC, strdup("engagement_rate")); }
    | T_REACH { $$ = make_node_with_string(AST_METRIC, strdup("reach")); }
    | T_GROWTH_RATE { $$ = make_node_with_string(AST_METRIC, strdup("growth_rate")); }
    ;

/* Literals */
literal:
    T_NUMBER { $$ = make_node_with_int(AST_LITERAL_INT, $1); }
    | T_DECIMAL { $$ = make_node_with_float(AST_LITERAL_FLOAT, $1); }
    | T_TEXT { $$ = make_node_with_string(AST_LITERAL_STRING, $1); }
    | T_TRUE_STORY { $$ = make_node_with_int(AST_LITERAL_BOOL, 1); }
    | T_FALSE_ALARM { $$ = make_node_with_int(AST_LITERAL_BOOL, 0); }
    ;
%%

/* Error handler with line numbers */
void yyerror(const char *s) {
    fprintf(stderr, "❌ Syntax Error at line %d: %s\n", yylineno, s);
    fprintf(output_file, "❌ Syntax Error at line %d: %s\n", yylineno, s);
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
        fprintf(output_file, "❌ Semantic Error (line %d): Account '%s' not declared\n", line, name);
        semantic_errors++;
    }
}

void check_duplicate_account(const char* name, int line) {
    if (lookup_symbol(name) != NULL) {
        fprintf(stderr, "❌ Semantic Error (line %d): Account '%s' already exists\n", line, name);
        fprintf(output_file, "❌ Semantic Error (line %d): Account '%s' already exists\n", line, name);
        semantic_errors++;
    }
}

void print_symbol_table() {
    fprintf(output_file, "\n📋 Symbol Table:\n");
    fprintf(output_file, "================\n");
    SymbolEntry* current = symbol_table;
    while (current != NULL) {
        fprintf(output_file, "%-20s | Type: ", current->name);
        switch (current->type) {
            case SYM_ACCOUNT: fprintf(output_file, "Account"); break;
            case SYM_VARIABLE: fprintf(output_file, "Variable"); break;
            case SYM_FUNCTION: fprintf(output_file, "Function"); break;
        }
        if (current->type == SYM_ACCOUNT) {
            fprintf(output_file, " | Likes: %d, Followers: %d, Views: %d, Comments: %d, Shares: %d",
                    current->likes, current->followers, current->views, current->comments, current->shares);
            if (current->engagement_rate > 0) {
                fprintf(output_file, ", Engagement: %.2f%%", current->engagement_rate);
            }
            if (current->growth_rate > 0) {
                fprintf(output_file, ", Growth: %.2f%%", current->growth_rate);
            }
        }
        fprintf(output_file, "\n");
        current = current->next;
    }
    fprintf(output_file, "================\n");
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
        case AST_ACCOUNT_REF: return "ACCOUNT_REF";
        default: return "UNKNOWN";
    }
}

void print_ast(ASTNode* node, int depth) {
    if (node == NULL) return;
    
    for (int i = 0; i < depth; i++) fprintf(output_file, "  ");
    fprintf(output_file, "├─ %s", node_type_name(node->type));
    
    if (node->sval) fprintf(output_file, " (%s)", node->sval);
    if (node->sval2) fprintf(output_file, " [Account: %s]", node->sval2);
    if (node->type == AST_LITERAL_INT) fprintf(output_file, " [%d]", node->ival);
    if (node->type == AST_LITERAL_FLOAT) fprintf(output_file, " [%.2f]", node->fval);
    if (node->type == AST_BINARY_OP) fprintf(output_file, " ['%c']", (char)node->ival);
    if (node->type == AST_LOOP || node->type == AST_LOOP_INCREMENT || node->type == AST_LOOP_DECREMENT) {
        fprintf(output_file, " [start:%d, end:%d, step:%d]", node->ival, node->ival2, node->step);
    }
    
    fprintf(output_file, "\n");
    
    if (node->condition) {
        for (int i = 0; i < depth + 1; i++) fprintf(output_file, "  ");
        fprintf(output_file, "Condition:\n");
        print_ast(node->condition, depth + 2);
    }
    
    if (node->body) {
        for (int i = 0; i < depth + 1; i++) fprintf(output_file, "  ");
        fprintf(output_file, "Body:\n");
        print_ast(node->body, depth + 2);
    }
    
    if (node->else_body) {
        for (int i = 0; i < depth + 1; i++) fprintf(output_file, "  ");
        fprintf(output_file, "Else:\n");
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
    if (node->sval2) free(node->sval2);
    free(node);
}

/* Helper function to get metric value from account */
int get_metric_value(SymbolEntry* account, const char* metric_name) {
    if (strcmp(metric_name, "likes") == 0) return account->likes;
    if (strcmp(metric_name, "followers") == 0) return account->followers;
    if (strcmp(metric_name, "views") == 0) return account->views;
    if (strcmp(metric_name, "comments") == 0) return account->comments;
    if (strcmp(metric_name, "shares") == 0) return account->shares;
    if (strcmp(metric_name, "posts") == 0) return account->posts;
    if (strcmp(metric_name, "stories") == 0) return account->stories;
    return 0;
}

/* Interpreter */
int evaluate_expression(ASTNode* node) {
    if (node == NULL) return 0;
    
    switch (node->type) {
        case AST_LITERAL_INT:
            return node->ival;
        case AST_LITERAL_BOOL:
            return node->ival;
        case AST_METRIC: {
            /* Metrics evaluate to their current value - need context */
            return 0;  /* Will be handled in context */
        }
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
            printf("\n╔════════════════════════════════════════════════╗\n");
            printf("║   🎬 SocialStoryScript Program Execution     ║\n");
            printf("╚════════════════════════════════════════════════╝\n\n");
            fprintf(output_file, "\n🎬 Executing SocialStoryScript Program...\n");
            fprintf(output_file, "==========================================\n");
            execute_statements(node->body);
            fprintf(output_file, "==========================================\n");
            fprintf(output_file, "✅ Program execution complete!\n");
            printf("\n╔════════════════════════════════════════════════╗\n");
            printf("║        ✅ Program Execution Complete!         ║\n");
            printf("╚════════════════════════════════════════════════╝\n\n");
            break;
            
        case AST_ACCOUNT_CREATE: {
            SymbolEntry* account = lookup_symbol(node->sval);
            if (account) {
                fprintf(output_file, "[Line %d] ✨ Created account: %s\n", node->line_number, node->sval);
            }
            break;
        }
            
        case AST_ACCOUNT_INIT: {
            SymbolEntry* account = lookup_symbol(node->sval);
            if (account && node->left && node->left->sval) {
                const char* metric = node->left->sval;
                if (strcmp(metric, "likes") == 0) {
                    account->likes = node->ival;
                    fprintf(output_file, "[Line %d] 📊 %s started with %d likes\n", node->line_number, node->sval, node->ival);
                } else if (strcmp(metric, "followers") == 0) {
                    account->followers = node->ival;
                    fprintf(output_file, "[Line %d] 👥 %s started with %d followers\n", node->line_number, node->sval, node->ival);
                } else if (strcmp(metric, "views") == 0) {
                    account->views = node->ival;
                    fprintf(output_file, "[Line %d] 👁️  %s started with %d views\n", node->line_number, node->sval, node->ival);
                } else if (strcmp(metric, "comments") == 0) {
                    account->comments = node->ival;
                    fprintf(output_file, "[Line %d] 💬 %s started with %d comments\n", node->line_number, node->sval, node->ival);
                } else if (strcmp(metric, "shares") == 0) {
                    account->shares = node->ival;
                    fprintf(output_file, "[Line %d] 🔄 %s started with %d shares\n", node->line_number, node->sval, node->ival);
                } else if (strcmp(metric, "engagement_rate") == 0) {
                    account->engagement_rate = node->fval;
                    fprintf(output_file, "[Line %d] 📈 %s began at %.2f%% engagement rate\n", node->line_number, node->sval, node->fval);
                } else if (strcmp(metric, "growth_rate") == 0) {
                    account->growth_rate = node->fval;
                    fprintf(output_file, "[Line %d] 📊 %s began at %.2f%% growth rate\n", node->line_number, node->sval, node->fval);
                }
            }
            break;
        }
            
        case AST_ACCOUNT_UPDATE: {
            SymbolEntry* account = lookup_symbol(node->sval);
            if (account && node->left && node->left->sval) {
                const char* metric = node->left->sval;
                const char* action = (node->ival > 0) ? "gained" : "lost";
                int abs_val = abs(node->ival);
                
                if (strcmp(metric, "likes") == 0) {
                    account->likes += node->ival;
                    printf("[Line %d] ❤️  %s %s %d likes (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->likes);
                    fprintf(output_file, "[Line %d] ❤️  %s %s %d likes (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->likes);
                } else if (strcmp(metric, "followers") == 0) {
                    account->followers += node->ival;
                    printf("[Line %d] 👥 %s %s %d followers (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->followers);
                    fprintf(output_file, "[Line %d] 👥 %s %s %d followers (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->followers);
                } else if (strcmp(metric, "views") == 0) {
                    account->views += node->ival;
                    fprintf(output_file, "[Line %d] 👁️  %s %s %d views (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->views);
                } else if (strcmp(metric, "comments") == 0) {
                    account->comments += node->ival;
                    fprintf(output_file, "[Line %d] 💬 %s %s %d comments (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->comments);
                } else if (strcmp(metric, "shares") == 0) {
                    account->shares += node->ival;
                    fprintf(output_file, "[Line %d] 🔄 %s %s %d shares (now: %d)\n", 
                           node->line_number, node->sval, action, abs_val, account->shares);
                }
            }
            break;
        }
            
        case AST_STORY_POST:
            if (node->left && node->left->sval) {
                printf("[Line %d] 📱 %s posted story: \"%s\" (%d views)\n", 
                       node->line_number, node->sval, node->left->sval, node->ival);
                fprintf(output_file, "[Line %d] 📱 %s posted story: \"%s\" (%d views)\n", 
                       node->line_number, node->sval, node->left->sval, node->ival);
            }
            break;
            
        case AST_CONDITIONAL: {
            int cond_result = evaluate_expression(node->condition);
            if (cond_result) {
                execute_statements(node->body);
            } else if (node->else_body) {
                execute(node->else_body);
            }
            break;
        }
            
        case AST_LOOP:
            fprintf(output_file, "[Line %d] 🔄 Loop: days %d to %d, step %d\n", 
                   node->line_number, node->ival, node->ival2, node->step);
            for (int i = node->ival; i <= node->ival2; i += node->step) {
                execute_statements(node->body);
            }
            break;
            
        case AST_LOOP_INCREMENT:
            fprintf(output_file, "[Line %d] 🔄 Loop incrementing: start %d, end %d, step %d\n", 
                   node->line_number, node->ival, node->ival2, node->step);
            for (int i = node->ival; i <= node->ival2; i += node->step) {
                execute_statements(node->body);
            }
            break;
            
        case AST_LOOP_DECREMENT:
            fprintf(output_file, "[Line %d] 🔄 Loop decrementing: start %d, end %d, step %d\n", 
                   node->line_number, node->ival, node->ival2, node->step);
            for (int i = node->ival; i >= node->ival2; i -= node->step) {
                execute_statements(node->body);
            }
            break;
            
        case AST_ANNOUNCE:
            printf("📢 %s\n", node->sval);
            fprintf(output_file, "[Line %d] 📢 Announcement: %s\n", node->line_number, node->sval);
            break;
            
        case AST_DISPLAY: {
            SymbolEntry* sym = lookup_symbol(node->sval);
            if (sym && sym->type == SYM_ACCOUNT) {
                fprintf(output_file, "[Line %d] 📊 Account %s: Likes=%d, Followers=%d, Views=%d, Comments=%d, Shares=%d\n",
                       node->line_number, node->sval, sym->likes, sym->followers, sym->views, 
                       sym->comments, sym->shares);
                if (sym->engagement_rate > 0) {
                    fprintf(output_file, "        Engagement Rate: %.2f%%\n", sym->engagement_rate);
                }
                if (sym->growth_rate > 0) {
                    fprintf(output_file, "        Growth Rate: %.2f%%\n", sym->growth_rate);
                }
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
                    printf("🏆 Most viral account: %s (viral score: %d)\n", max->name, max_score);
                    fprintf(output_file, "[Line %d] 🏆 RESULT: Most viral account is '%s' with viral score: %d\n", 
                           node->line_number, max->name, max_score);
                }
            } else if (strcmp(node->sval, "calculate_virality") == 0 && node->sval2) {
                SymbolEntry* account = lookup_symbol(node->sval2);
                if (account) {
                    int virality = account->likes + account->followers + account->views;
                    account->is_viral = (virality > 1000);
                    printf("📊 Virality score for %s: %d %s\n", 
                           node->sval2, virality, account->is_viral ? "(VIRAL!)" : "");
                    fprintf(output_file, "[Line %d] 📊 RESULT: Virality score for '%s' = %d %s\n", 
                           node->line_number, node->sval2, virality, account->is_viral ? "(VIRAL!)" : "");
                }
            } else if (strcmp(node->sval, "calculate_engagement") == 0 && node->sval2) {
                SymbolEntry* account = lookup_symbol(node->sval2);
                if (account && account->followers > 0) {
                    float engagement = ((float)(account->likes + account->comments + account->shares) / account->followers) * 100.0;
                    account->engagement_rate = engagement;
                    printf("📈 Engagement rate for %s: %.2f%%\n", node->sval2, engagement);
                    fprintf(output_file, "[Line %d] 📈 RESULT: Engagement rate for '%s' = %.2f%%\n", 
                           node->line_number, node->sval2, engagement);
                }
            } else if (strcmp(node->sval, "analyze_growth") == 0 && node->sval2) {
                SymbolEntry* account = lookup_symbol(node->sval2);
                if (account) {
                    float growth = ((float)account->followers / 100.0) * 10.0;  /* Simulated growth */
                    account->growth_rate = growth;
                    printf("📊 Growth rate for %s: %.2f%%\n", node->sval2, growth);
                    fprintf(output_file, "[Line %d] 📊 RESULT: Growth rate for '%s' = %.2f%%\n", 
                           node->line_number, node->sval2, growth);
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
    
    /* Create output file */
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "output_%s", argv[1]);
    output_file = fopen(output_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot create output file\n");
        fclose(input);
        return 1;
    }
    
    yyin = input;
    
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║       🚀 SocialStoryScript Compiler           ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("Parsing: %s\n", argv[1]);
    printf("Output:  %s\n", output_filename);
    printf("════════════════════════════════════════════════\n\n");
    
    fprintf(output_file, "🚀 SocialStoryScript Compiler\n");
    fprintf(output_file, "==============================\n");
    fprintf(output_file, "Parsing: %s\n", argv[1]);
    fprintf(output_file, "==============================\n\n");
    
    int parse_result = yyparse();
    
    if (parse_result == 0 && semantic_errors == 0) {
        fprintf(output_file, "\n🌲 Abstract Syntax Tree:\n");
        print_ast(ast_root, 0);
        
        print_symbol_table();
        
        execute(ast_root);
        
        fprintf(output_file, "\n✅ Compilation successful!\n");
        fprintf(output_file, "   Lexical errors: %d\n", error_count);
        fprintf(output_file, "   Syntax errors: 0\n");
        fprintf(output_file, "   Semantic errors: %d\n", semantic_errors);
        
        printf("\n✅ Compilation successful!\n");
        printf("   Lexical errors: %d\n", error_count);
        printf("   Syntax errors: 0\n");
        printf("   Semantic errors: %d\n", semantic_errors);
        printf("\nDetailed output saved to: %s\n", output_filename);
    } else {
        fprintf(output_file, "\n❌ Compilation failed with errors.\n");
        fprintf(output_file, "   Lexical errors: %d\n", error_count);
        fprintf(output_file, "   Semantic errors: %d\n", semantic_errors);
        
        printf("\n❌ Compilation failed with errors.\n");
        printf("   Lexical errors: %d\n", error_count);
        printf("   Semantic errors: %d\n", semantic_errors);
    }
    
    free_ast(ast_root);
    free_symbol_table();
    fclose(input);
    fclose(output_file);
    
    return (parse_result == 0 && semantic_errors == 0) ? 0 : 1;
}
