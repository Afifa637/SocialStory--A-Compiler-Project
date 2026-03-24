/* ========================================
 * TAC_GENERATOR.H - Three-Address Code Generation
 * Add this to your socialstory_parser.y file
 * ======================================== */

#ifndef TAC_GENERATOR_H
#define TAC_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TAC Instruction Structure */
typedef struct TACInstruction
{
    char *op;     // Operation: +, -, *, /, =, ifFalse, goto, call, return, param
    char *arg1;   // First argument
    char *arg2;   // Second argument
    char *result; // Result/destination
    int label;    // Label number for jumps (-1 if not a label)
    struct TACInstruction *next;
} TACInstruction;

/* Global TAC Variables */
TACInstruction *tac_head = NULL;
TACInstruction *tac_tail = NULL;
int temp_counter = 0;
int label_counter = 0;

/* ===================================
 * HELPER FUNCTIONS
 * =================================== */

/* Generate new temporary variable */
char *new_temp()
{
    char *temp = (char *)malloc(16);
    sprintf(temp, "t%d", temp_counter++);
    return temp;
}

/* Generate new label */
int new_label()
{
    return label_counter++;
}

/* Check if string is a number */
int is_number(const char *str)
{
    if (!str || *str == '\0')
        return 0;
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

/* ===================================
 * TAC EMISSION
 * =================================== */

/* Emit a TAC instruction */
TACInstruction *emit_tac(const char *op, const char *arg1, const char *arg2, const char *result)
{
    TACInstruction *instr = (TACInstruction *)malloc(sizeof(TACInstruction));
    instr->op = op ? strdup(op) : NULL;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->label = -1;
    instr->next = NULL;

    if (tac_tail)
    {
        tac_tail->next = instr;
        tac_tail = instr;
    }
    else
    {
        tac_head = tac_tail = instr;
    }

    return instr;
}

/* Emit a label */
TACInstruction *emit_label(int label_num)
{
    TACInstruction *instr = emit_tac("label", NULL, NULL, NULL);
    instr->label = label_num;
    return instr;
}

/* ===================================
 * TAC GENERATION FOR EXPRESSIONS
 * =================================== */

/* Generate TAC for expressions */
char *generate_tac_expression(ASTNode *node)
{
    if (!node)
        return NULL;

    switch (node->type)
    {
    case AST_LITERAL_INT:
    {
        char *result = new_temp();
        char value[32];
        sprintf(value, "%d", node->ival);
        emit_tac("=", value, NULL, result);
        return result;
    }

    case AST_LITERAL_FLOAT:
    {
        char *result = new_temp();
        char value[32];
        sprintf(value, "%.2f", node->fval);
        emit_tac("=", value, NULL, result);
        return result;
    }

    case AST_IDENTIFIER:
    case AST_ACCOUNT_REF:
    {
        return strdup(node->sval);
    }

    case AST_FEED_GET:
    {
        char *idx = generate_tac_expression(node->left);
        char *result = new_temp();
        char target[256];
        sprintf(target, "feed[%s].%s", idx ? idx : "0", node->sval ? node->sval : "likes");
        emit_tac("feed_get", target, NULL, result);
        if (idx)
            free(idx);
        return result;
    }

    case AST_FEED_LENGTH:
    {
        char *result = new_temp();
        emit_tac("feed_len", node->sval ? node->sval : "posts", NULL, result);
        return result;
    }

    case AST_METRIC:
    {
        // For account.metric references
        char *temp = new_temp();
        emit_tac("=", node->sval, NULL, temp);
        return temp;
    }

    case AST_BINARY_OP:
    {
        char *left = generate_tac_expression(node->left);
        char *right = generate_tac_expression(node->right);
        char *result = new_temp();

        const char *op;
        switch (node->ival)
        {
        case 0:
            op = "+";
            break; // OP_ADD
        case 1:
            op = "-";
            break; // OP_SUB
        case 2:
            op = "*";
            break; // OP_MUL
        case 3:
            op = "/";
            break; // OP_DIV
        case 4:
            op = "%";
            break; // OP_MOD
        default:
            op = "?";
            break;
        }

        emit_tac(op, left, right, result);
        free(left);
        free(right);
        return result;
    }

    case AST_COMPARISON:
    {
        char *left = generate_tac_expression(node->left);
        char *right = generate_tac_expression(node->right);
        char *result = new_temp();

        const char *op;
        switch (node->ival)
        {
        case 0:
            op = ">";
            break; // CMP_GT
        case 1:
            op = "<";
            break; // CMP_LT
        case 2:
            op = "==";
            break; // CMP_EQ
        case 3:
            op = "!=";
            break; // CMP_NEQ
        case 4:
            op = ">=";
            break; // CMP_GTE
        case 5:
            op = "<=";
            break; // CMP_LTE
        default:
            op = "?";
            break;
        }

        emit_tac(op, left, right, result);
        free(left);
        free(right);
        return result;
    }

    case AST_LOGICAL_OP:
    {
        char *left = generate_tac_expression(node->left);
        char *right = generate_tac_expression(node->right);
        char *result = new_temp();

        const char *op = (node->ival == 0) ? "&&" : "||";
        emit_tac(op, left, right, result);
        free(left);
        free(right);
        return result;
    }

    /* NEW: Unary operations like opposite (NOT) */
    case AST_UNARY_OP:
    {
        char *operand = generate_tac_expression(node->left);
        char *result = new_temp();

        if (node->ival == 0)
        { // NOT operation
            emit_tac("!", operand, NULL, result);
        }
        free(operand);
        return result;
    }

    default:
        return NULL;
    }
}

/* ===================================
 * TAC GENERATION FOR STATEMENTS
 * =================================== */

void generate_tac_statement(ASTNode *node);
void generate_tac_statements(ASTNode *node);

/* Generate TAC for a single statement */
void generate_tac_statement(ASTNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_ACCOUNT_CREATE:
    {
        emit_tac("create_account", node->sval, NULL, NULL);
        break;
    }

    case AST_ACCOUNT_INIT:
    {
        if (node->left && node->left->type == AST_METRIC)
        {
            char dest[256];
            sprintf(dest, "%s.%s", node->sval, node->left->sval);
            if (node->right)
            {
                char *value = generate_tac_expression(node->right);
                emit_tac("=", value, NULL, dest);
                free(value);
            }
            else if ((strcmp(node->left->sval, "engagement rate") == 0 ||
                      strcmp(node->left->sval, "growth rate") == 0 ||
                      strcmp(node->left->sval, "reach") == 0))
            {
                char value[32];
                sprintf(value, "%.2f", node->fval);
                emit_tac("=", value, NULL, dest);
            }
            else
            {
                char value[32];
                sprintf(value, "%d", node->ival);
                emit_tac("=", value, NULL, dest);
            }
        }
        break;
    }

    case AST_ACCOUNT_UPDATE:
    {
        if (node->left && node->left->type == AST_METRIC)
        {
            char account_metric[256];
            sprintf(account_metric, "%s.%s", node->sval, node->left->sval);

            // Get current value
            char *temp1 = new_temp();
            emit_tac("=", account_metric, NULL, temp1);

            // Calculate new value
            char *value_str = node->right ? generate_tac_expression(node->right) : NULL;
            char value_buf[32];
            if (!value_str)
            {
                sprintf(value_buf, "%d", node->ival);
                value_str = strdup(value_buf);
            }
            char *temp2 = new_temp();
            emit_tac(node->ival == -1 ? "-" : "+", temp1, value_str, temp2);

            // Store back
            emit_tac("=", temp2, NULL, account_metric);

            free(temp1);
            free(temp2);
            free(value_str);
        }
        break;
    }

    case AST_FEED_DECLARE:
    {
        char size_str[32];
        sprintf(size_str, "%d", node->ival);
        emit_tac("feed_decl", size_str, node->left && node->left->sval ? node->left->sval : "posts", NULL);
        break;
    }

    case AST_FEED_SET:
    {
        char *idx = generate_tac_expression(node->left);
        char *value = generate_tac_expression(node->right);
        char target[256];
        sprintf(target, "feed[%s].%s", idx ? idx : "0", node->sval ? node->sval : "likes");
        emit_tac("feed_set", value, NULL, target);
        if (idx)
            free(idx);
        if (value)
            free(value);
        break;
    }

    case AST_FEED_DISPLAY:
    {
        if (node->left)
        {
            char *idx = generate_tac_expression(node->left);
            char target[256];
            sprintf(target, "feed[%s].%s", idx ? idx : "0", node->sval ? node->sval : "likes");
            emit_tac("feed_display", target, NULL, NULL);
            if (idx)
                free(idx);
        }
        else
        {
            emit_tac("feed_display", "feed", NULL, NULL);
        }
        break;
    }

    case AST_CONDITIONAL:
    {
        int false_label = new_label();
        int end_label = new_label();

        // Generate condition check
        if (node->condition)
        {
            char *cond = generate_tac_expression(node->condition);
            char label_str[32];
            sprintf(label_str, "L%d", false_label);
            emit_tac("ifFalse", cond, label_str, NULL);
            free(cond);
        }

        // Generate code for true branch
        generate_tac_statements(node->body);

        // Only jump to end if there's an else branch
        if (node->else_body)
        {
            char label_str[32];
            sprintf(label_str, "L%d", end_label);
            emit_tac("goto", label_str, NULL, NULL);
        }

        // False label
        emit_label(false_label);

        // Generate code for else branch
        if (node->else_body)
        {
            if (node->else_body->condition)
            {
                // For Otherwise if blocks, generate the conditional recursively
                generate_tac_statement(node->else_body);
            }
            else if (node->else_body->body)
            {
                // For Otherwise blocks, generate the body statements
                generate_tac_statements(node->else_body->body);
            }
        }

        // End label (only if else exists)
        if (node->else_body)
        {
            emit_label(end_label);
        }
        break;
    }

    case AST_LOOP:
    {
        int start_label = new_label();
        int end_label = new_label();

        // Initialize loop counter
        char counter[32];
        sprintf(counter, "loop_i_%d", start_label);
        char init_val[32];
        sprintf(init_val, "%d", node->ival);
        emit_tac("=", init_val, NULL, counter);

        // Start label
        emit_label(start_label);

        // Check condition: i <= end_value
        char end_val[32];
        sprintf(end_val, "%d", node->ival2);
        char *cond_temp = new_temp();
        emit_tac("<=", counter, end_val, cond_temp);

        // If false, jump to end
        char label_str[32];
        sprintf(label_str, "L%d", end_label);
        emit_tac("ifFalse", cond_temp, label_str, NULL);
        free(cond_temp);

        // Loop body
        generate_tac_statements(node->body);

        // Increment counter
        char step_val[32];
        sprintf(step_val, "%d", node->step);
        char *inc_temp = new_temp();
        emit_tac("+", counter, step_val, inc_temp);
        emit_tac("=", inc_temp, NULL, counter);
        free(inc_temp);

        // Jump back to start
        sprintf(label_str, "L%d", start_label);
        emit_tac("goto", label_str, NULL, NULL);

        // End label
        emit_label(end_label);
        break;
    }

    case AST_LOOP_INCREMENT:
    case AST_LOOP_DECREMENT:
    {
        int start_label = new_label();
        int end_label = new_label();
        char counter[32];
        sprintf(counter, "loop_i_%d", start_label);

        // Initialize
        char init_val[32];
        sprintf(init_val, "%d", node->ival);
        emit_tac("=", init_val, NULL, counter);

        // Start label
        emit_label(start_label);

        // Check condition
        char end_val[32];
        sprintf(end_val, "%d", node->ival2);
        char *cond_temp = new_temp();

        if (node->type == AST_LOOP_INCREMENT)
        {
            emit_tac("<=", counter, end_val, cond_temp);
        }
        else
        {
            emit_tac(">=", counter, end_val, cond_temp);
        }

        char label_str[32];
        sprintf(label_str, "L%d", end_label);
        emit_tac("ifFalse", cond_temp, label_str, NULL);
        free(cond_temp);

        // Body
        generate_tac_statements(node->body);

        // Update counter
        char step_val[32];
        sprintf(step_val, "%d", node->step);
        char *update_temp = new_temp();

        if (node->type == AST_LOOP_INCREMENT)
        {
            emit_tac("+", counter, step_val, update_temp);
        }
        else
        {
            emit_tac("-", counter, step_val, update_temp);
        }

        emit_tac("=", update_temp, NULL, counter);
        free(update_temp);

        // Jump back
        sprintf(label_str, "L%d", start_label);
        emit_tac("goto", label_str, NULL, NULL);

        // End label
        emit_label(end_label);
        break;
    }

    /* NEW: For each follower from A to B range loop */
    case AST_LOOP_RANGE:
    {
        int start_label = new_label();
        int end_label = new_label();
        char counter[32];
        sprintf(counter, "range_i_%d", start_label);

        // Initialize
        char init_val[32];
        sprintf(init_val, "%d", node->ival);
        emit_tac("=", init_val, NULL, counter);

        // Start label
        emit_label(start_label);

        // Check condition
        char end_val[32];
        sprintf(end_val, "%d", node->ival2);
        char *cond_temp = new_temp();
        emit_tac("<=", counter, end_val, cond_temp);

        char label_str[32];
        sprintf(label_str, "L%d", end_label);
        emit_tac("ifFalse", cond_temp, label_str, NULL);
        free(cond_temp);

        // Body
        generate_tac_statements(node->body);

        // Increment counter
        char *inc_temp = new_temp();
        emit_tac("+", counter, "1", inc_temp);
        emit_tac("=", inc_temp, NULL, counter);
        free(inc_temp);

        // Jump back
        sprintf(label_str, "L%d", start_label);
        emit_tac("goto", label_str, NULL, NULL);

        // End label
        emit_label(end_label);
        break;
    }

    /* NEW: trending loop until CONDITION */
    case AST_LOOP_TRENDING:
    {
        int start_label = new_label();

        // Start label
        emit_label(start_label);

        // Check condition - loop UNTIL it's true
        if (node->condition)
        {
            char *cond = generate_tac_expression(node->condition);
            int end_label = new_label();
            char label_str[32];
            sprintf(label_str, "L%d", end_label);
            emit_tac("ifTrue", cond, label_str, NULL);
            free(cond);

            // Body
            generate_tac_statements(node->body);

            // Jump back
            sprintf(label_str, "L%d", start_label);
            emit_tac("goto", label_str, NULL, NULL);

            // End label
            emit_label(end_label);
        }
        break;
    }

    case AST_ANNOUNCE:
    {
        emit_tac("print", node->sval, NULL, NULL);
        break;
    }

    case AST_DISPLAY:
    {
        emit_tac("display", node->sval, NULL, NULL);
        break;
    }

    case AST_FUNCTION_CALL:
    {
        // Generate TAC for parameters
        ASTNode *param = node->param;
        while (param)
        {
            char *param_val = generate_tac_expression(param);
            emit_tac("param", param_val, NULL, NULL);
            free(param_val);
            param = param->next;
        }

        // Call function
        char *result = new_temp();
        emit_tac("call", node->sval, NULL, result);
        free(result);
        break;
    }

    case AST_BUILTIN_CALL:
    {
        if (node->sval2)
        {
            emit_tac(node->sval, node->sval2, NULL, NULL);
        }
        else
        {
            emit_tac(node->sval, NULL, NULL, NULL);
        }
        break;
    }

    case AST_RETURN:
    {
        if (node->left)
        {
            char *ret_val = generate_tac_expression(node->left);
            emit_tac("return", ret_val, NULL, NULL);
            free(ret_val);
        }
        else
        {
            emit_tac("return", NULL, NULL, NULL);
        }
        break;
    }

    case AST_BREAK:
    {
        emit_tac("break", NULL, NULL, NULL);
        break;
    }

    case AST_CONTINUE:
    {
        emit_tac("continue", NULL, NULL, NULL);
        break;
    }

    /* NEW: Ask for user input */
    case AST_ASK_FOR:
    {
        emit_tac("input", node->sval, NULL, NULL);
        break;
    }

    /* NEW: String operations like reverse */
    case AST_STRING_OP:
    {
        emit_tac(node->sval, node->sval2 ? node->sval2 : "", NULL, NULL);
        break;
    }

    default:
        break;
    }
}

/* Generate TAC for a list of statements */
void generate_tac_statements(ASTNode *node)
{
    while (node)
    {
        generate_tac_statement(node);
        node = node->next;
    }
}

/* ===================================
 * TAC OUTPUT & PRINTING
 * =================================== */

/* Print TAC instructions to file */
void print_tac_to_file(FILE *fp)
{
    fprintf(fp, "\n💻 THREE-ADDRESS CODE (TAC):\n");
    fprintf(fp, "========================================\n\n");

    TACInstruction *instr = tac_head;
    int line_num = 1;
    int instruction_count = 0;

    while (instr)
    {
        // Print label
        if (instr->label >= 0)
        {
            fprintf(fp, "L%d:\n", instr->label);
        }
        else
        {
            fprintf(fp, "%4d: ", line_num++);
            instruction_count++;

            // Print instruction
            if (strcmp(instr->op, "=") == 0)
            {
                fprintf(fp, "%s = %s\n", instr->result, instr->arg1);
            }
            else if (strcmp(instr->op, "ifFalse") == 0)
            {
                fprintf(fp, "if %s == false goto %s\n", instr->arg1, instr->arg2);
            }
            else if (strcmp(instr->op, "goto") == 0)
            {
                fprintf(fp, "goto %s\n", instr->arg1);
            }
            else if (strcmp(instr->op, "print") == 0)
            {
                fprintf(fp, "print \"%s\"\n", instr->arg1);
            }
            else if (strcmp(instr->op, "display") == 0)
            {
                fprintf(fp, "display %s\n", instr->arg1);
            }
            else if (strcmp(instr->op, "call") == 0)
            {
                fprintf(fp, "%s = call %s\n", instr->result ? instr->result : "_", instr->arg1);
            }
            else if (strcmp(instr->op, "param") == 0)
            {
                fprintf(fp, "param %s\n", instr->arg1);
            }
            else if (strcmp(instr->op, "return") == 0)
            {
                if (instr->arg1)
                {
                    fprintf(fp, "return %s\n", instr->arg1);
                }
                else
                {
                    fprintf(fp, "return\n");
                }
            }
            else if (strcmp(instr->op, "create_account") == 0)
            {
                fprintf(fp, "create_account %s\n", instr->arg1);
            }
            else if (strcmp(instr->op, "feed_decl") == 0)
            {
                fprintf(fp, "feed_decl size=%s kind=%s\n", instr->arg1, instr->arg2 ? instr->arg2 : "posts");
            }
            else if (strcmp(instr->op, "feed_set") == 0)
            {
                fprintf(fp, "%s = %s\n", instr->result, instr->arg1);
            }
            else if (strcmp(instr->op, "feed_get") == 0)
            {
                fprintf(fp, "%s = %s\n", instr->result, instr->arg1);
            }
            else if (strcmp(instr->op, "feed_len") == 0)
            {
                fprintf(fp, "%s = feed_length(%s)\n", instr->result, instr->arg1 ? instr->arg1 : "posts");
            }
            else if (strcmp(instr->op, "feed_display") == 0)
            {
                fprintf(fp, "display %s\n", instr->arg1 ? instr->arg1 : "feed");
            }
            else if (instr->arg2)
            {
                // Binary operation
                fprintf(fp, "%s = %s %s %s\n",
                        instr->result, instr->arg1, instr->op, instr->arg2);
            }
            else
            {
                // Unary or special operation
                if (instr->result)
                {
                    fprintf(fp, "%s = %s %s\n", instr->result, instr->op, instr->arg1 ? instr->arg1 : "");
                }
                else
                {
                    fprintf(fp, "%s %s\n", instr->op, instr->arg1 ? instr->arg1 : "");
                }
            }
        }

        instr = instr->next;
    }

    fprintf(fp, "\n========================================\n");
    fprintf(fp, "📊 TAC Statistics:\n");
    fprintf(fp, "   Total instructions: %d\n", instruction_count);
    fprintf(fp, "   Temporary variables: %d\n", temp_counter);
    fprintf(fp, "   Labels created: %d\n", label_counter);
    fprintf(fp, "========================================\n");
}

/* Free TAC memory */
void free_tac()
{
    TACInstruction *current = tac_head;
    while (current)
    {
        TACInstruction *next = current->next;
        free(current->op);
        free(current->arg1);
        free(current->arg2);
        free(current->result);
        free(current);
        current = next;
    }
    tac_head = tac_tail = NULL;
}

#endif /* TAC_GENERATOR_H */
