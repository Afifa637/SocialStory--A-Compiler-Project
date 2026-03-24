/* ========================================
 * INTERPRETER.H
 * Program Execution Engine
 * ======================================== */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* Forward declarations */
void execute_statement(ASTNode *node);
void execute_statements(ASTNode *node);
int execute_expression(ASTNode *node);
float execute_expression_float(ASTNode *node);

/* ===== Function Return Handling ===== */
int return_flag = 0;      /* Set to 1 when Tell back is executed */
int return_value = 0;     /* Holds the integer return value */
float return_value_f = 0; /* Holds the float return value */

/* ===== Feed/Array Runtime Storage ===== */
typedef struct FeedEntry
{
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
} FeedEntry;

FeedEntry *feed_entries = NULL;
int feed_size = 0;
char feed_kind[16] = "posts";

void reset_feed()
{
    if (feed_entries)
    {
        free(feed_entries);
        feed_entries = NULL;
    }
    feed_size = 0;
    strcpy(feed_kind, "posts");
}

int feed_metric_is_float(const char *metric)
{
    return (strcmp(metric, "engagement rate") == 0 ||
            strcmp(metric, "engagement_rate") == 0 ||
            strcmp(metric, "growth rate") == 0 ||
            strcmp(metric, "growth_rate") == 0 ||
            strcmp(metric, "reach") == 0);
}

int feed_metric_is_int(const char *metric)
{
    return !feed_metric_is_float(metric);
}

int get_feed_metric_int(FeedEntry *e, const char *metric)
{
    if (strcmp(metric, "likes") == 0)
        return e->likes;
    if (strcmp(metric, "followers") == 0)
        return e->followers;
    if (strcmp(metric, "views") == 0)
        return e->views;
    if (strcmp(metric, "comments") == 0)
        return e->comments;
    if (strcmp(metric, "shares") == 0)
        return e->shares;
    if (strcmp(metric, "posts") == 0)
        return e->posts;
    if (strcmp(metric, "stories") == 0)
        return e->stories;
    if (strcmp(metric, "reach") == 0)
        return (int)e->reach;
    return 0;
}

float get_feed_metric_float(FeedEntry *e, const char *metric)
{
    if (strcmp(metric, "engagement rate") == 0 || strcmp(metric, "engagement_rate") == 0)
        return e->engagement_rate;
    if (strcmp(metric, "growth rate") == 0 || strcmp(metric, "growth_rate") == 0)
        return e->growth_rate;
    if (strcmp(metric, "reach") == 0)
        return e->reach;
    return (float)get_feed_metric_int(e, metric);
}

void set_feed_metric_int(FeedEntry *e, const char *metric, int value)
{
    if (strcmp(metric, "likes") == 0)
        e->likes = value;
    else if (strcmp(metric, "followers") == 0)
        e->followers = value;
    else if (strcmp(metric, "views") == 0)
        e->views = value;
    else if (strcmp(metric, "comments") == 0)
        e->comments = value;
    else if (strcmp(metric, "shares") == 0)
        e->shares = value;
    else if (strcmp(metric, "posts") == 0)
        e->posts = value;
    else if (strcmp(metric, "stories") == 0)
        e->stories = value;
}

void set_feed_metric_float(FeedEntry *e, const char *metric, float value)
{
    if (strcmp(metric, "engagement rate") == 0 || strcmp(metric, "engagement_rate") == 0)
        e->engagement_rate = value;
    else if (strcmp(metric, "growth rate") == 0 || strcmp(metric, "growth_rate") == 0)
        e->growth_rate = value;
    else if (strcmp(metric, "reach") == 0)
        e->reach = value;
}

int eval_feed_index(ASTNode *idx_expr, int line_number, int *ok)
{
    *ok = 0;
    if (!idx_expr)
    {
        fprintf(stderr, "❌ Runtime Error line %d: Missing feed index expression\n", line_number);
        fprintf(output_file, "❌ Runtime Error line %d: Missing feed index expression\n", line_number);
        semantic_errors++;
        return 0;
    }

    if (idx_expr->type == AST_LITERAL_FLOAT)
    {
        fprintf(stderr, "❌ Runtime Error line %d: Feed index must be integer, got float\n", line_number);
        fprintf(output_file, "❌ Runtime Error line %d: Feed index must be integer\n", line_number);
        semantic_errors++;
        return 0;
    }

    int idx = execute_expression(idx_expr);
    if (idx < 0 || idx >= feed_size)
    {
        fprintf(stderr, "❌ Runtime Error line %d: Feed index %d out of bounds [0, %d)\n", line_number, idx, feed_size);
        fprintf(output_file, "❌ Runtime Error line %d: Feed index %d out of bounds [0, %d)\n", line_number, idx, feed_size);
        semantic_errors++;
        return 0;
    }

    *ok = 1;
    return idx;
}

/* ========================================
 * TYPE CHECKING HELPERS (A+ FEATURE)
 * Detect type mismatches at compile/runtime
 * ======================================== */

/* Check if a metric expects float values */
int is_float_metric(const char *metric_name)
{
    return (strcmp(metric_name, "engagement rate") == 0 ||
            strcmp(metric_name, "engagement_rate") == 0 ||
            strcmp(metric_name, "growth rate") == 0 ||
            strcmp(metric_name, "growth_rate") == 0 ||
            strcmp(metric_name, "reach") == 0);
}

/* Check if a metric expects integer values */
int is_int_metric(const char *metric_name)
{
    return (strcmp(metric_name, "likes") == 0 ||
            strcmp(metric_name, "followers") == 0 ||
            strcmp(metric_name, "views") == 0 ||
            strcmp(metric_name, "comments") == 0 ||
            strcmp(metric_name, "shares") == 0 ||
            strcmp(metric_name, "posts") == 0 ||
            strcmp(metric_name, "stories") == 0);
}

/* ========================================
 * ACCOUNT METRIC ACCESSORS
 * ======================================== */

int get_account_metric(SymbolEntry *acc, const char *metric)
{
    if (strcmp(metric, "likes") == 0)
        return acc->likes;
    if (strcmp(metric, "followers") == 0)
        return acc->followers;
    if (strcmp(metric, "views") == 0)
        return acc->views;
    if (strcmp(metric, "comments") == 0)
        return acc->comments;
    if (strcmp(metric, "shares") == 0)
        return acc->shares;
    if (strcmp(metric, "posts") == 0)
        return acc->posts;
    if (strcmp(metric, "stories") == 0)
        return acc->stories;
    if (strcmp(metric, "reach") == 0)
        return (int)acc->reach;
    return 0;
}

float get_account_metric_float(SymbolEntry *acc, const char *metric)
{
    if (strcmp(metric, "engagement rate") == 0 || strcmp(metric, "engagement_rate") == 0)
        return acc->engagement_rate;
    if (strcmp(metric, "growth rate") == 0 || strcmp(metric, "growth_rate") == 0)
        return acc->growth_rate;
    if (strcmp(metric, "reach") == 0)
        return acc->reach;
    return (float)get_account_metric(acc, metric);
}

void set_account_metric(SymbolEntry *acc, const char *metric, int value)
{
    if (strcmp(metric, "likes") == 0)
        acc->likes = value;
    else if (strcmp(metric, "followers") == 0)
        acc->followers = value;
    else if (strcmp(metric, "views") == 0)
        acc->views = value;
    else if (strcmp(metric, "comments") == 0)
        acc->comments = value;
    else if (strcmp(metric, "shares") == 0)
        acc->shares = value;
    else if (strcmp(metric, "posts") == 0)
        acc->posts = value;
    else if (strcmp(metric, "stories") == 0)
        acc->stories = value;
}

void set_account_metric_float(SymbolEntry *acc, const char *metric, float value)
{
    if (strcmp(metric, "engagement rate") == 0 || strcmp(metric, "engagement_rate") == 0)
        acc->engagement_rate = value;
    else if (strcmp(metric, "growth rate") == 0 || strcmp(metric, "growth_rate") == 0)
        acc->growth_rate = value;
    else if (strcmp(metric, "reach") == 0)
        acc->reach = value;
}

/* ========================================
 * BUILTIN FUNCTIONS
 * ======================================== */

void builtin_calculate_virality(const char *account_name)
{
    SymbolEntry *acc = lookup_symbol(account_name);
    if (!acc)
        return;

    int viral_score = acc->likes + acc->followers + acc->views;
    fprintf(output_file, "[Line %d] 📊 RESULT: Virality score for '%s' = %d%s\n",
            yylineno, account_name, viral_score,
            viral_score > 1000 ? " (VIRAL!)" : "");

    acc->is_viral = (viral_score > 1000);
}

void builtin_calculate_engagement(const char *account_name)
{
    SymbolEntry *acc = lookup_symbol(account_name);
    if (!acc)
        return;

    if (acc->followers > 0)
    {
        acc->engagement_rate = (acc->likes * 100.0) / acc->followers;
        fprintf(output_file, "[Line %d] 📈 RESULT: Engagement rate for '%s' = %.2f%%\n",
                yylineno, account_name, acc->engagement_rate);
    }
}

void builtin_analyze_growth(const char *account_name)
{
    SymbolEntry *acc = lookup_symbol(account_name);
    if (!acc)
        return;

    // Simple growth calculation based on current metrics
    acc->growth_rate = (acc->followers > 500) ? 100.0 : 50.0;
    fprintf(output_file, "[Line %d] 📊 RESULT: Growth rate for '%s' = %.2f%%\n",
            yylineno, account_name, acc->growth_rate);
}

void builtin_find_max_viral()
{
    SymbolEntry *max_acc = NULL;
    int max_score = -1;

    SymbolEntry *current = symbol_table;
    while (current)
    {
        if (current->type == SYM_ACCOUNT)
        {
            int score = current->likes + current->followers + current->views;
            if (score > max_score)
            {
                max_score = score;
                max_acc = current;
            }
        }
        current = current->next;
    }

    if (max_acc)
    {
        fprintf(output_file, "[Line %d] 🏆 RESULT: Most viral account is '%s' with viral score: %d\n",
                yylineno, max_acc->name, max_score);
    }
}

/* ========================================
 * EXPRESSION EVALUATION
 * ======================================== */

int execute_expression(ASTNode *node)
{
    if (!node)
        return 0;

    switch (node->type)
    {
    case AST_LITERAL_INT:
        return node->ival;

    case AST_LITERAL_FLOAT:
        return (int)node->fval;

    case AST_LITERAL_BOOL:
        return node->ival;

    case AST_METRIC:
    {
        // Sum across all accounts
        int total = 0;
        SymbolEntry *current = symbol_table;
        while (current)
        {
            if (current->type == SYM_ACCOUNT)
            {
                total += get_account_metric(current, node->sval);
            }
            current = current->next;
        }
        return total;
    }

    case AST_ACCOUNT_REF:
    {
        // Get metric for specific account
        if (node->sval && node->sval2)
        {
            SymbolEntry *acc = lookup_symbol(node->sval);
            if (acc)
            {
                return get_account_metric(acc, node->sval2);
            }
        }
        return 0;
    }

    case AST_BINARY_OP:
    {
        int left = execute_expression(node->left);
        int right = execute_expression(node->right);

        switch (node->ival)
        {
        case OP_ADD:
            return left + right;
        case OP_SUB:
            return left - right;
        case OP_MUL:
            return left * right;
        case OP_DIV:
            if (right == 0)
            {
                fprintf(stderr, "❌ Runtime Error line %d: Division by zero\n", node->line_number);
                fprintf(output_file, "❌ Runtime Error line %d: Division by zero\n", node->line_number);
                semantic_errors++; // COUNT THIS ERROR
                return 0;
            }
            return left / right;
        case OP_MOD:
            if (right == 0)
            {
                fprintf(stderr, "❌ Runtime Error line %d: Modulo by zero\n", node->line_number);
                fprintf(output_file, "❌ Runtime Error line %d: Modulo by zero\n", node->line_number);
                semantic_errors++; // COUNT THIS ERROR
                return 0;
            }
            return left % right;
        }
        return 0;
    }

    case AST_COMPARISON:
    {
        int left = execute_expression(node->left);
        int right = execute_expression(node->right);

        switch (node->ival)
        {
        case CMP_GT:
            return left > right;
        case CMP_LT:
            return left < right;
        case CMP_EQ:
            return left == right;
        case CMP_NEQ:
            return left != right;
        case CMP_GTE:
            return left >= right;
        case CMP_LTE:
            return left <= right;
        }
        return 0;
    }

    case AST_LOGICAL_OP:
    {
        int left = execute_expression(node->left);
        int right = execute_expression(node->right);

        if (node->ival == 0)
            return left && right; // AND
        else
            return left || right; // OR
    }

    /* NEW: Unary operations like opposite (NOT) */
    case AST_UNARY_OP:
    {
        int operand = execute_expression(node->left);
        if (node->ival == 0)
            return !operand; // NOT
        return operand;
    }

    /* Variable lookup (for Ask for / user-defined variables) */
    case AST_IDENTIFIER:
    {
        if (node->sval)
        {
            SymbolEntry *var = lookup_symbol(node->sval);
            if (var)
                return var->likes;
        }
        return 0;
    }

    case AST_FEED_GET:
    {
        if (!feed_entries || feed_size <= 0)
        {
            fprintf(stderr, "❌ Runtime Error line %d: Feed is not declared\n", node->line_number);
            fprintf(output_file, "❌ Runtime Error line %d: Feed is not declared\n", node->line_number);
            semantic_errors++;
            return 0;
        }
        int ok = 0;
        int idx = eval_feed_index(node->left, node->line_number, &ok);
        if (!ok)
            return 0;
        if (!node->sval)
            return 0;
        return get_feed_metric_int(&feed_entries[idx], node->sval);
    }

    case AST_FEED_LENGTH:
        return feed_size;

    default:
        return 0;
    }

    return 0;
}

float execute_expression_float(ASTNode *node)
{
    if (!node)
        return 0.0;

    switch (node->type)
    {
    case AST_LITERAL_FLOAT:
        return node->fval;

    case AST_LITERAL_INT:
        return (float)node->ival;

    case AST_ACCOUNT_REF:
    {
        if (node->sval && node->sval2)
        {
            SymbolEntry *acc = lookup_symbol(node->sval);
            if (acc)
            {
                return get_account_metric_float(acc, node->sval2);
            }
        }
        return 0.0;
    }

    case AST_FEED_GET:
    {
        if (!feed_entries || feed_size <= 0)
            return 0.0f;
        int ok = 0;
        int idx = eval_feed_index(node->left, node->line_number, &ok);
        if (!ok)
            return 0.0f;
        if (!node->sval)
            return 0.0f;
        return get_feed_metric_float(&feed_entries[idx], node->sval);
    }

    case AST_FEED_LENGTH:
        return (float)feed_size;

    case AST_BINARY_OP:
    {
        float left = execute_expression_float(node->left);
        float right = execute_expression_float(node->right);

        switch (node->ival)
        {
        case OP_ADD:
            return left + right;
        case OP_SUB:
            return left - right;
        case OP_MUL:
            return left * right;
        case OP_DIV:
            if (right == 0.0)
            {
                fprintf(stderr, "❌ Runtime Error line %d: Division by zero\n", node->line_number);
                fprintf(output_file, "❌ Runtime Error line %d: Division by zero\n", node->line_number);
                return 0.0;
            }
            return left / right;
        }
        return 0.0;
    }

    case AST_LITERAL_BOOL:
        return (float)node->ival;

    default:
        return (float)execute_expression(node);
    }
}

/* ========================================
 * STATEMENT EXECUTION
 * ======================================== */

void execute_statement(ASTNode *node)
{
    if (!node || loop_break_flag || return_flag)
        return;

    switch (node->type)
    {
    case AST_ACCOUNT_CREATE:
    {
        fprintf(output_file, "[Line %d] ✨ Created account: %s\n",
                node->line_number, node->sval);
        break;
    }

    case AST_ACCOUNT_INIT:
    {
        SymbolEntry *acc = lookup_symbol(node->sval);
        if (acc && node->left)
        {
            const char *metric = node->left->sval;
            int has_expr = (node->right != NULL);
            int has_float_literal = (node->right && node->right->type == AST_LITERAL_FLOAT) ||
                                    (!has_expr && fabs(node->fval) > 0.000001f);
            int int_value = has_expr ? execute_expression(node->right) : node->ival;
            float float_value = has_expr ? execute_expression_float(node->right) : node->fval;

            /* ========================================
             * TYPE CHECKING (A+ FEATURE)
             * Detect float→int and string→numeric errors
             * ======================================== */

            // Check for float value assigned to integer metric
            if (has_float_literal && is_int_metric(metric))
            {
                fprintf(stderr, "❌ Type Error at line %d: Cannot assign float value %.2f to integer metric '%s'\n",
                        node->line_number, float_value, metric);
                fprintf(output_file, "❌ Type Error at line %d: Float→Int conversion not allowed for '%s' (attempted %.2f)\n",
                        node->line_number, metric, float_value);
                semantic_errors++;
                break; // Don't execute this assignment
            }

            // Warn about int→float conversion (allowed but warn)
            if (is_float_metric(metric) && !has_float_literal)
            {
                fprintf(output_file, "⚠️  Warning at line %d: Implicitly converting int %d to float for '%s'\n",
                        node->line_number, int_value, metric);
                float_value = (float)int_value; // Auto-convert
            }

            /* ======================================== */

            // Check if it's a float metric
            if (strcmp(metric, "engagement rate") == 0 ||
                strcmp(metric, "engagement_rate") == 0 ||
                strcmp(metric, "growth rate") == 0 ||
                strcmp(metric, "growth_rate") == 0 ||
                strcmp(metric, "reach") == 0)
            {
                set_account_metric_float(acc, metric, float_value);
                fprintf(output_file, "[Line %d] 📊 %s began at %.2f %s\n",
                        node->line_number, node->sval, float_value, metric);
            }
            else
            {
                set_account_metric(acc, metric, int_value);

                const char *emoji = "📊";
                if (strcmp(metric, "followers") == 0)
                    emoji = "👥";
                else if (strcmp(metric, "views") == 0)
                    emoji = "👁️ ";

                fprintf(output_file, "[Line %d] %s %s started with %d %s\n",
                        node->line_number, emoji, node->sval, int_value, metric);
            }
        }
        break;
    }

    case AST_ACCOUNT_UPDATE:
    {
        SymbolEntry *acc = lookup_symbol(node->sval);
        if (acc && node->left)
        {
            const char *metric = node->left->sval;
            int old_value = get_account_metric(acc, metric);
            int new_value;

            /* Evaluate the expression amount (node->right holds expression tree) */
            int amount = node->right ? execute_expression(node->right) : node->ival;

            if (node->ival2 == 1)
            {
                /* multiply */
                new_value = old_value * amount;
                set_account_metric(acc, metric, new_value);
                fprintf(output_file, "[Line %d] ✖️  %s multiplied %s by %d (now: %d)\n",
                        node->line_number, node->sval, metric, amount, new_value);
            }
            else if (node->ival2 == 2)
            {
                /* divide */
                if (amount != 0)
                {
                    new_value = old_value / amount;
                    set_account_metric(acc, metric, new_value);
                    fprintf(output_file, "[Line %d] ➗ %s divided %s by %d (now: %d)\n",
                            node->line_number, node->sval, metric, amount, new_value);
                }
                else
                {
                    fprintf(stderr, "\n❌ RUNTIME ERROR at line %d:\n   Division by zero in account update for '%s'\n   Fix: Ensure the divisor is not 0.\n\n", node->line_number, node->sval);
                    fprintf(output_file, "[Line %d] ❌ RUNTIME ERROR: Division by zero for '%s'\n", node->line_number, node->sval);
                    semantic_errors++;
                }
            }
            else if (node->ival2 == 3)
            {
                /* set viral */
                acc->is_viral = 1;
                fprintf(output_file, "[Line %d] 🔥 %s is now VIRAL!\n",
                        node->line_number, node->sval);
            }
            else if (node->ival2 == 4)
            {
                /* set trending */
                acc->is_trending = 1;
                fprintf(output_file, "[Line %d] 📈 %s is now TRENDING!\n",
                        node->line_number, node->sval);
            }
            else if (node->ival == -1)
            {
                /* subtract (lost / decreased by) — clamp to 0, metrics can't go negative */
                new_value = old_value - amount;
                if (new_value < 0)
                {
                    fprintf(stderr, "\n⚠️  WARNING at line %d:\n   '%s' tried to subtract %d from %s (was %d) — clamped to 0.\n   A social media metric cannot go below zero.\n\n",
                            node->line_number, node->sval, amount, metric, old_value);
                    fprintf(output_file, "[Line %d] ⚠️  CLAMP: %s %s would go negative (%d - %d) → set to 0\n",
                            node->line_number, node->sval, metric, old_value, amount);
                    new_value = 0;
                }
                set_account_metric(acc, metric, new_value);
                fprintf(output_file, "[Line %d] 📉 %s lost/decreased %s by %d: %d → %d\n",
                        node->line_number, node->sval, metric, amount, old_value, new_value);
            }
            else
            {
                /* normal add (gained / increased by) */
                new_value = old_value + amount;
                set_account_metric(acc, metric, new_value);

                const char *emoji = "📊";
                if (strcmp(metric, "likes") == 0)
                    emoji = "❤️ ";
                else if (strcmp(metric, "followers") == 0)
                    emoji = "👥";
                else if (strcmp(metric, "views") == 0)
                    emoji = "👁️ ";

                fprintf(output_file, "[Line %d] %s %s gained/increased %s by %d (now: %d)\n",
                        node->line_number, emoji, node->sval, metric, amount, new_value);
            }
        }
        break;
    }

    case AST_STORY_POST:
    {
        SymbolEntry *acc = lookup_symbol(node->sval);
        if (acc)
        {
            int views = node->ival > 0 ? node->ival : 5000;
            acc->views += views; // FIX BUG #4: Store views in account
            acc->stories++;

            const char *caption = (node->left && node->left->type == AST_LITERAL_STRING)
                                      ? node->left->sval
                                      : "Untitled";

            fprintf(output_file, "[Line %d] 📱 %s posted story: \"%s\" (%d views)\n",
                    node->line_number, node->sval, caption, views);
        }
        break;
    }

    case AST_CONDITIONAL:
    {
        if (!node->condition)
        {
            execute_statements(node->body);
            break;
        }

        int cond_result = execute_expression(node->condition);
        if (cond_result)
        {
            execute_statements(node->body);
        }
        else if (node->else_body)
        {
            execute_statement(node->else_body);
        }
        break;
    }

    case AST_LOOP:
    {
        fprintf(output_file, "[Line %d] 🔄 Loop: days %d to %d, step %d\n",
                node->line_number, node->ival, node->ival2, node->step);

        for (int i = node->ival; i <= node->ival2 && !loop_break_flag; i += node->step)
        {
            loop_continue_flag = 0;
            ASTNode *stmt = node->body;
            while (stmt && !loop_break_flag)
            {
                if (!loop_continue_flag)
                {
                    execute_statement(stmt);
                }
                stmt = stmt->next;
            }
        }
        loop_break_flag = 0;
        break;
    }

    case AST_LOOP_INCREMENT:
    {
        fprintf(output_file, "[Line %d] 🔄 Loop incrementing: start %d, end %d, step %d\n",
                node->line_number, node->ival, node->ival2, node->step);

        for (int i = node->ival; i <= node->ival2 && !loop_break_flag; i += node->step)
        {
            loop_continue_flag = 0;
            ASTNode *stmt = node->body;
            while (stmt && !loop_break_flag)
            {
                if (!loop_continue_flag)
                {
                    execute_statement(stmt);
                }
                stmt = stmt->next;
            }
        }
        loop_break_flag = 0;
        break;
    }

    case AST_LOOP_DECREMENT:
    {
        fprintf(output_file, "[Line %d] 🔄 Loop decrementing: start %d, end %d, step %d\n",
                node->line_number, node->ival, node->ival2, node->step);

        for (int i = node->ival; i >= node->ival2 && !loop_break_flag; i -= node->step)
        {
            loop_continue_flag = 0;
            ASTNode *stmt = node->body;
            while (stmt && !loop_break_flag)
            {
                if (!loop_continue_flag)
                {
                    execute_statement(stmt);
                }
                stmt = stmt->next;
            }
        }
        loop_break_flag = 0;
        break;
    }

    case AST_LOOP_RANGE:
    {
        fprintf(output_file, "[Line %d] 🔄 Loop range: from %d to %d\n",
                node->line_number, node->ival, node->ival2);

        for (int i = node->ival; i <= node->ival2 && !loop_break_flag; i++)
        {
            loop_continue_flag = 0;
            ASTNode *stmt = node->body;
            while (stmt && !loop_break_flag)
            {
                if (!loop_continue_flag)
                {
                    execute_statement(stmt);
                }
                stmt = stmt->next;
            }
        }
        loop_break_flag = 0;
        break;
    }

    /* NEW: trending loop until CONDITION */
    case AST_LOOP_TRENDING:
    {
        fprintf(output_file, "[Line %d] 🔄 Trending loop until condition met\n",
                node->line_number);

        int max_iterations = 1000; // Safety limit
        int iterations = 0;

        while (iterations < max_iterations && !loop_break_flag)
        {
            // Check condition - loop UNTIL it's true
            if (node->condition && execute_expression(node->condition))
            {
                break; // Condition met, exit loop
            }

            loop_continue_flag = 0;
            ASTNode *stmt = node->body;
            while (stmt && !loop_break_flag)
            {
                if (!loop_continue_flag)
                {
                    execute_statement(stmt);
                }
                stmt = stmt->next;
            }
            iterations++;
        }
        loop_break_flag = 0;
        break;
    }

    /* NEW: String operations */
    case AST_STRING_OP:
    {
        if (strcmp(node->sval, "reverse") == 0 && node->sval2)
        {
            int len = strlen(node->sval2);
            char *reversed = (char *)malloc(len + 1);
            for (int i = 0; i < len; i++)
            {
                reversed[i] = node->sval2[len - 1 - i];
            }
            reversed[len] = '\0';

            fprintf(output_file, "[Line %d] 🔄 Reversed caption: \"%s\"\n",
                    node->line_number, reversed);
            free(reversed);
        }
        else if (strcmp(node->sval, "detect_spam") == 0 && node->sval2)
        {
            /* Simple spam detection: check for spam keywords */
            const char *spam_words[] = {"spam", "free", "click", "win", "prize", "buy now", NULL};
            int is_spam = 0;
            char lower_text[512];
            strncpy(lower_text, node->sval2, 511);
            lower_text[511] = '\0';
            for (int i = 0; lower_text[i]; i++)
                lower_text[i] = tolower(lower_text[i]);
            for (int i = 0; spam_words[i]; i++)
            {
                if (strstr(lower_text, spam_words[i]))
                {
                    is_spam = 1;
                    break;
                }
            }
            fprintf(output_file, "[Line %d] 🔍 Spam detection for \"%s\": %s\n",
                    node->line_number, node->sval2, is_spam ? "⚠️ SPAM DETECTED!" : "✅ Clean");
        }
        break;
    }

    case AST_FEED_DECLARE:
    {
        int requested = node->ival;
        if (requested < 0)
        {
            fprintf(stderr, "❌ Runtime Error line %d: Feed size cannot be negative\n", node->line_number);
            fprintf(output_file, "❌ Runtime Error line %d: Feed size cannot be negative\n", node->line_number);
            semantic_errors++;
            break;
        }

        reset_feed();
        feed_size = requested;
        if (feed_size > 0)
        {
            feed_entries = (FeedEntry *)calloc((size_t)feed_size, sizeof(FeedEntry));
            if (!feed_entries)
            {
                fprintf(stderr, "❌ Runtime Error line %d: Memory allocation failed for feed\n", node->line_number);
                fprintf(output_file, "❌ Runtime Error line %d: Memory allocation failed for feed\n", node->line_number);
                semantic_errors++;
                feed_size = 0;
                break;
            }
        }

        if (node->left && node->left->sval)
        {
            strncpy(feed_kind, node->left->sval, sizeof(feed_kind) - 1);
            feed_kind[sizeof(feed_kind) - 1] = '\0';
        }

        fprintf(output_file, "[Line %d] 🧱 Feed declared: %d %s\n",
                node->line_number, feed_size, feed_kind);
        break;
    }

    case AST_FEED_SET:
    {
        if (!feed_entries || feed_size <= 0)
        {
            fprintf(stderr, "❌ Runtime Error line %d: Feed is not declared\n", node->line_number);
            fprintf(output_file, "❌ Runtime Error line %d: Feed is not declared\n", node->line_number);
            semantic_errors++;
            break;
        }

        int ok = 0;
        int idx = eval_feed_index(node->left, node->line_number, &ok);
        if (!ok)
            break;

        if (!node->sval)
        {
            fprintf(stderr, "❌ Runtime Error line %d: Missing feed metric in assignment\n", node->line_number);
            fprintf(output_file, "❌ Runtime Error line %d: Missing feed metric in assignment\n", node->line_number);
            semantic_errors++;
            break;
        }

        if (feed_metric_is_float(node->sval))
        {
            float value = execute_expression_float(node->right);
            set_feed_metric_float(&feed_entries[idx], node->sval, value);
            fprintf(output_file, "[Line %d] 📝 feed[%d].%s = %.2f\n",
                    node->line_number, idx, node->sval, value);
        }
        else
        {
            int value = execute_expression(node->right);
            set_feed_metric_int(&feed_entries[idx], node->sval, value);
            fprintf(output_file, "[Line %d] 📝 feed[%d].%s = %d\n",
                    node->line_number, idx, node->sval, value);
        }
        break;
    }

    case AST_FEED_DISPLAY:
    {
        if (!feed_entries || feed_size <= 0)
        {
            fprintf(output_file, "[Line %d] 📦 Feed is empty or not declared\n", node->line_number);
            break;
        }

        if (!node->left)
        {
            fprintf(output_file, "[Line %d] 📦 Feed summary: size=%d, kind=%s\n",
                    node->line_number, feed_size, feed_kind);
            break;
        }

        int ok = 0;
        int idx = eval_feed_index(node->left, node->line_number, &ok);
        if (!ok)
            break;

        const char *metric = node->sval ? node->sval : "likes";
        if (feed_metric_is_float(metric))
        {
            float value = get_feed_metric_float(&feed_entries[idx], metric);
            fprintf(output_file, "[Line %d] 📦 feed[%d].%s = %.2f\n",
                    node->line_number, idx, metric, value);
        }
        else
        {
            int value = get_feed_metric_int(&feed_entries[idx], metric);
            fprintf(output_file, "[Line %d] 📦 feed[%d].%s = %d\n",
                    node->line_number, idx, metric, value);
        }
        break;
    }

    case AST_LOOP_COLLECTION:
    {
        /* For each post/story in the feed */
        int count = feed_size;
        fprintf(output_file, "[Line %d] 🔄 Collection loop (%s) - %d iterations\n",
                node->line_number, node->sval ? node->sval : "item", count);
        for (int i = 0; i < count && !loop_break_flag; i++)
        {
            loop_continue_flag = 0;
            ASTNode *stmt = node->body;
            while (stmt && !loop_break_flag)
            {
                if (!loop_continue_flag)
                    execute_statement(stmt);
                stmt = stmt->next;
            }
        }
        loop_break_flag = 0;
        break;
    }

    case AST_BREAK:
        loop_break_flag = 1;
        break;

    case AST_CONTINUE:
        loop_continue_flag = 1;
        break;

    case AST_ANNOUNCE:
    {
        fprintf(output_file, "[Line %d] 📢 Announcement: %s\n",
                node->line_number, node->sval);
        break;
    }

    case AST_DISPLAY:
    {
        SymbolEntry *acc = lookup_symbol(node->sval);
        if (acc && acc->type == SYM_ACCOUNT)
        {
            if (node->sval2)
            {
                if (is_float_metric(node->sval2))
                {
                    fprintf(output_file, "[Line %d] 📊 %s.%s = %.2f\n",
                            node->line_number, node->sval, node->sval2,
                            get_account_metric_float(acc, node->sval2));
                }
                else
                {
                    fprintf(output_file, "[Line %d] 📊 %s.%s = %d\n",
                            node->line_number, node->sval, node->sval2,
                            get_account_metric(acc, node->sval2));
                }
                break;
            }

            fprintf(output_file, "[Line %d] 📊 Account %s: Likes=%d, Followers=%d, Views=%d, Comments=%d, Shares=%d\n",
                    node->line_number, node->sval, acc->likes, acc->followers,
                    acc->views, acc->comments, acc->shares);

            // FIX BUG #5: Display float metrics even if not explicitly computed
            if (acc->engagement_rate > 0.001)
            {
                fprintf(output_file, "        Engagement Rate: %.2f%%\n", acc->engagement_rate);
            }
            if (acc->growth_rate > 0.001)
            {
                fprintf(output_file, "        Growth Rate: %.2f%%\n", acc->growth_rate);
            }
        }
        else if (acc && acc->type == SYM_VARIABLE)
        {
            fprintf(output_file, "[Line %d] 📊 Variable %s = %d\n",
                    node->line_number, node->sval, acc->likes);
        }
        break;
    }

    case AST_ASK_FOR:
    {
        if (node->sval)
        {
            /* Print prompt to both console and terminal */
            printf("\n🎤 INPUT REQUIRED: Enter value for '%s': ", node->sval);
            fflush(stdout);

            char input_buf[256];
            if (fgets(input_buf, sizeof(input_buf), stdin))
            {
                /* Try to parse as integer first, then float */
                char *endptr;
                long int_val = strtol(input_buf, &endptr, 10);

                SymbolEntry *var = lookup_symbol(node->sval);
                if (!var)
                {
                    var = insert_symbol(node->sval, SYM_VARIABLE);
                }

                if (*endptr == '\n' || *endptr == '\0' || *endptr == '\r')
                {
                    /* Valid integer */
                    var->likes = (int)int_val;
                    printf("   ✅ Stored: %s = %d\n\n", node->sval, (int)int_val);
                    fprintf(output_file, "[Line %d] 🎤 INPUT: %s = %d (integer)\n",
                            node->line_number, node->sval, (int)int_val);
                }
                else
                {
                    float f_val = strtof(input_buf, &endptr);
                    if (*endptr == '\n' || *endptr == '\0' || *endptr == '\r')
                    {
                        /* Valid float */
                        var->engagement_rate = f_val;
                        printf("   ✅ Stored: %s = %.2f\n\n", node->sval, f_val);
                        fprintf(output_file, "[Line %d] 🎤 INPUT: %s = %.2f (float)\n",
                                node->line_number, node->sval, f_val);
                    }
                    else
                    {
                        /* Treat as string: store length as value */
                        input_buf[strcspn(input_buf, "\r\n")] = 0;
                        var->likes = (int)strlen(input_buf);
                        printf("   ✅ Stored string: %s = \"%s\"\n\n", node->sval, input_buf);
                        fprintf(output_file, "[Line %d] 🎤 INPUT: %s = \"%s\" (string, length stored)\n",
                                node->line_number, node->sval, input_buf);
                    }
                }
            }
            else
            {
                fprintf(stderr, "⚠️  Warning: Could not read input for '%s'. Defaulting to 0.\n", node->sval);
                fprintf(output_file, "[Line %d] ⚠️  INPUT FAILED for '%s': defaulting to 0\n",
                        node->line_number, node->sval);
            }
        }
        break;
    }

    /* ========================================
     * FUNCTION DEFINITION
     * Store function body and params in symbol table
     * ======================================== */
    case AST_FUNCTION_DEF:
    {
        if (node->sval)
        {
            SymbolEntry *func = lookup_symbol(node->sval);
            if (!func)
            {
                func = insert_symbol(node->sval, SYM_FUNCTION);
            }
            else
            {
                func->type = SYM_FUNCTION;
            }
            func->function_body = node->body;
            func->function_params = node->param;
            fprintf(output_file, "[Line %d] 📖 Defined function: '%s'",
                    node->line_number, node->sval);
            /* Count params */
            int pcount = 0;
            ASTNode *p = node->param;
            while (p)
            {
                pcount++;
                p = p->next;
            }
            if (pcount > 0)
                fprintf(output_file, " (params: %d)", pcount);
            fprintf(output_file, "\n");
        }
        break;
    }

    /* ========================================
     * FUNCTION CALL
     * Execute stored function body with arguments
     * ======================================== */
    case AST_FUNCTION_CALL:
    {
        if (node->sval)
        {
            SymbolEntry *func = lookup_symbol(node->sval);
            if (!func || func->type != SYM_FUNCTION)
            {
                fprintf(stderr, "\n❌ RUNTIME ERROR at line %d:\n", node->line_number);
                fprintf(stderr, "   Undefined function: '%s'\n", node->sval);
                fprintf(stderr, "   Fix: Define it first with: The story of %s begins with ...\n\n", node->sval);
                fprintf(output_file, "[Line %d] ❌ RUNTIME ERROR: Undefined function '%s'\n",
                        node->line_number, node->sval);
                break;
            }

            fprintf(output_file, "[Line %d] 📞 Calling function: '%s'\n",
                    node->line_number, node->sval);

            int expected_arity = 0;
            ASTNode *ptmp = func->function_params;
            while (ptmp)
            {
                expected_arity++;
                ptmp = ptmp->next;
            }

            int actual_arity = 0;
            ASTNode *atmp = node->param;
            while (atmp)
            {
                actual_arity++;
                atmp = atmp->next;
            }

            if (expected_arity != actual_arity)
            {
                fprintf(stderr, "❌ Runtime Error line %d: Function '%s' expects %d argument(s), got %d\n",
                        node->line_number, node->sval, expected_arity, actual_arity);
                fprintf(output_file, "[Line %d] ❌ RUNTIME ERROR: Function '%s' expects %d argument(s), got %d\n",
                        node->line_number, node->sval, expected_arity, actual_arity);
                semantic_errors++;
                break;
            }

            /* Bind arguments to parameter names in symbol table */
            ASTNode *param = func->function_params;
            ASTNode *arg = node->param;

            /* Save old values of param names so we can restore after call */
            typedef struct
            {
                char *name;
                int old_likes;
            } SavedParam;
            SavedParam saved[16];
            int saved_count = 0;

            while (param && saved_count < 16)
            {
                if (param->sval)
                {
                    SymbolEntry *pvar = lookup_symbol(param->sval);
                    if (!pvar)
                        pvar = insert_symbol(param->sval, SYM_VARIABLE);

                    saved[saved_count].name = param->sval;
                    saved[saved_count].old_likes = pvar->likes;
                    saved_count++;

                    /* Evaluate argument and bind */
                    if (arg)
                    {
                        int val = execute_expression(arg);
                        pvar->likes = val;
                        fprintf(output_file, "   Bound param '%s' = %d\n", param->sval, val);
                    }

                    param = param->next;
                    if (arg)
                        arg = arg->next;
                }
                else
                    break;
            }

            /* Execute function body */
            return_flag = 0;
            return_value = 0;
            if (func->function_body)
            {
                execute_statements(func->function_body);
            }

            if (return_flag)
            {
                fprintf(output_file, "   Returned: %d\n", return_value);
                return_flag = 0;
            }

            /* Restore old parameter values */
            for (int i = 0; i < saved_count; i++)
            {
                SymbolEntry *pvar = lookup_symbol(saved[i].name);
                if (pvar)
                    pvar->likes = saved[i].old_likes;
            }
        }
        break;
    }

    /* ========================================
     * RETURN (Tell back VALUE)
     * ======================================== */
    case AST_RETURN:
    {
        return_value = execute_expression(node->left);
        return_value_f = execute_expression_float(node->left);
        return_flag = 1;
        fprintf(output_file, "[Line %d] ↩️  Return value: %d\n",
                node->line_number, return_value);
        break;
    }

    case AST_BUILTIN_CALL:
    {
        if (strcmp(node->sval, "calculate_virality") == 0 && node->sval2)
        {
            builtin_calculate_virality(node->sval2);
        }
        else if (strcmp(node->sval, "calculate_engagement") == 0 && node->sval2)
        {
            builtin_calculate_engagement(node->sval2);
        }
        else if (strcmp(node->sval, "analyze_growth") == 0 && node->sval2)
        {
            builtin_analyze_growth(node->sval2);
        }
        else if (strcmp(node->sval, "find_max_viral_account") == 0)
        {
            builtin_find_max_viral();
        }
        else if (strcmp(node->sval, "check_if_trending") == 0)
        {
            /* Check trending: engagement_rate > 5.0 or views > 10000 */
            if (node->sval2)
            {
                SymbolEntry *acc = lookup_symbol(node->sval2);
                if (acc)
                {
                    int is_trend = (acc->engagement_rate > 5.0f || acc->views > 10000);
                    acc->is_trending = is_trend;
                    fprintf(output_file, "[Line %d] 📈 RESULT: '%s' is %s\n",
                            node->line_number, node->sval2,
                            is_trend ? "TRENDING! 🔥" : "not trending yet");
                }
            }
            else
            {
                /* Check all accounts */
                SymbolEntry *cur = symbol_table;
                while (cur)
                {
                    if (cur->type == SYM_ACCOUNT)
                    {
                        int is_trend = (cur->engagement_rate > 5.0f || cur->views > 10000);
                        cur->is_trending = is_trend;
                        fprintf(output_file, "[Line %d] 📈 %s: %s\n",
                                node->line_number, cur->name,
                                is_trend ? "TRENDING! 🔥" : "not trending");
                    }
                    cur = cur->next;
                }
            }
        }
        else if (strcmp(node->sval, "count_total_engagement") == 0)
        {
            int total = 0;
            SymbolEntry *cur = symbol_table;
            while (cur)
            {
                if (cur->type == SYM_ACCOUNT)
                {
                    total += cur->likes + cur->comments + cur->shares;
                }
                cur = cur->next;
            }
            fprintf(output_file, "[Line %d] 💬 RESULT: Total engagement across all accounts = %d\n",
                    node->line_number, total);
        }
        else if (strcmp(node->sval, "find_top_post") == 0)
        {
            SymbolEntry *top = NULL;
            int max_views = -1;
            SymbolEntry *cur = symbol_table;
            while (cur)
            {
                if (cur->type == SYM_ACCOUNT && cur->views > max_views)
                {
                    max_views = cur->views;
                    top = cur;
                }
                cur = cur->next;
            }
            if (top)
            {
                fprintf(output_file, "[Line %d] 🏆 RESULT: Top performing post is from '%s' with %d views\n",
                        node->line_number, top->name, max_views);
            }
        }
        else if (strcmp(node->sval, "find_highest_reach") == 0)
        {
            float max_reach = -1;
            char *max_name = NULL;
            SymbolEntry *cur = symbol_table;
            while (cur)
            {
                if (cur->type == SYM_ACCOUNT && cur->reach > max_reach)
                {
                    max_reach = cur->reach;
                    max_name = cur->name;
                }
                cur = cur->next;
            }
            if (max_name)
            {
                fprintf(output_file, "[Line %d] 📡 RESULT: Highest reach = %.2f (account: %s)\n",
                        node->line_number, max_reach, max_name);
            }
        }
        else if (strcmp(node->sval, "find_total_reach") == 0)
        {
            float total = 0;
            SymbolEntry *cur = symbol_table;
            while (cur)
            {
                if (cur->type == SYM_ACCOUNT)
                    total += cur->reach;
                cur = cur->next;
            }
            fprintf(output_file, "[Line %d] 📡 RESULT: Total reach in feed = %.2f\n",
                    node->line_number, total);
        }
        else if (strcmp(node->sval, "clamp_engagement") == 0)
        {
            float min_v = (float)node->ival;
            float max_v = (float)node->ival2;
            SymbolEntry *cur = symbol_table;
            while (cur)
            {
                if (cur->type == SYM_ACCOUNT)
                {
                    float old = cur->engagement_rate;
                    if (cur->engagement_rate < min_v)
                        cur->engagement_rate = min_v;
                    if (cur->engagement_rate > max_v)
                        cur->engagement_rate = max_v;
                    fprintf(output_file, "[Line %d] 🔧 Clamped %s engagement: %.2f → %.2f\n",
                            node->line_number, cur->name, old, cur->engagement_rate);
                }
                cur = cur->next;
            }
        }
        else if (strcmp(node->sval, "reverse_growth") == 0)
        {
            if (node->sval2)
            {
                SymbolEntry *acc = lookup_symbol(node->sval2);
                if (acc)
                {
                    acc->growth_rate = -acc->growth_rate;
                    fprintf(output_file, "[Line %d] 📉 Reversed growth for '%s': now %.2f%%\n",
                            node->line_number, node->sval2, acc->growth_rate);
                }
            }
            else
            {
                SymbolEntry *cur = symbol_table;
                while (cur)
                {
                    if (cur->type == SYM_ACCOUNT)
                    {
                        cur->growth_rate = -cur->growth_rate;
                        fprintf(output_file, "[Line %d] 📉 Reversed growth for '%s': now %.2f%%\n",
                                node->line_number, cur->name, cur->growth_rate);
                    }
                    cur = cur->next;
                }
            }
        }
        break;
    }

    default:
        break;
    }
}

/* ========================================
 * EXECUTE A LINKED LIST OF STATEMENTS
 * Respects return_flag and loop_break_flag
 * ======================================== */
void execute_statements(ASTNode *node)
{
    while (node && !loop_break_flag && !return_flag)
    {
        execute_statement(node);
        node = node->next;
    }
}

/* ========================================
 * MAIN EXECUTION FUNCTION
 * ======================================== */

void execute(ASTNode *root)
{
    fprintf(output_file, "\n🎬 Executing SocialStoryScript Program...\n");
    fprintf(output_file, "==========================================\n");
    reset_feed();

    if (root && root->body)
    {
        ASTNode *stmt = root->body;
        while (stmt)
        {
            execute_statement(stmt);
            stmt = stmt->next;
        }
    }

    reset_feed();
    fprintf(output_file, "==========================================\n");
    if (semantic_errors == 0)
    {
        fprintf(output_file, "✅ Program execution complete with no runtime/semantic errors.\n");
    }
    else
    {
        fprintf(output_file, "❌ Program execution completed with %d runtime/semantic error(s).\n", semantic_errors);
    }
}

#endif /* INTERPRETER_H */