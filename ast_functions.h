/* ========================================
 * AST_FUNCTIONS.H
 * AST Node Creation and Manipulation
 * ======================================== */

#ifndef AST_FUNCTIONS_H
#define AST_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================
 * AST NODE CREATION FUNCTIONS
 * ======================================== */

/* Create a new AST node */
ASTNode *make_node(ASTNodeType type)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node)
    {
        fprintf(stderr, "❌ Memory allocation failed for AST node\n");
        exit(1);
    }

    node->type = type;
    node->ival = 0;
    node->ival2 = 0;
    node->step = 1;
    node->fval = 0.0;
    node->sval = NULL;
    node->sval2 = NULL;
    node->left = NULL;
    node->right = NULL;
    node->condition = NULL;
    node->body = NULL;
    node->else_body = NULL;
    node->next = NULL;
    node->param = NULL;
    node->line_number = yylineno;

    return node;
}

/* Create node with integer value */
ASTNode *make_node_with_int(ASTNodeType type, int value)
{
    ASTNode *node = make_node(type);
    node->ival = value;
    return node;
}

/* Create node with float value */
ASTNode *make_node_with_float(ASTNodeType type, float value)
{
    ASTNode *node = make_node(type);
    node->fval = value;
    return node;
}

/* Create node with string value */
ASTNode *make_node_with_string(ASTNodeType type, const char *value)
{
    ASTNode *node = make_node(type);
    node->sval = value ? strdup(value) : NULL;
    return node;
}

/* Create binary operation node */
ASTNode *make_binary_op(ASTNodeType type, ASTNode *left, ASTNode *right)
{
    ASTNode *node = make_node(type);
    node->left = left;
    node->right = right;
    return node;
}

/* ========================================
 * AST PRINTING
 * ======================================== */

/* Get node type name for printing */
const char *get_node_type_name(ASTNodeType type)
{
    switch (type)
    {
    case AST_PROGRAM:
        return "PROGRAM";
    case AST_ACCOUNT_CREATE:
        return "ACCOUNT_CREATE";
    case AST_ACCOUNT_INIT:
        return "ACCOUNT_INIT";
    case AST_ACCOUNT_UPDATE:
        return "ACCOUNT_UPDATE";
    case AST_STORY_POST:
        return "STORY_POST";
    case AST_CONDITIONAL:
        return "CONDITIONAL";
    case AST_LOOP:
        return "LOOP";
    case AST_LOOP_INCREMENT:
        return "LOOP_INCREMENT";
    case AST_LOOP_DECREMENT:
        return "LOOP_DECREMENT";
    case AST_LOOP_RANGE:
        return "LOOP_RANGE";
    case AST_LOOP_COLLECTION:
        return "LOOP_COLLECTION";
    case AST_LOOP_TRENDING:
        return "LOOP_TRENDING";
    case AST_FUNCTION_DEF:
        return "FUNCTION_DEF";
    case AST_FUNCTION_CALL:
        return "FUNCTION_CALL";
    case AST_BUILTIN_CALL:
        return "BUILTIN_CALL";
    case AST_RETURN:
        return "RETURN";
    case AST_BREAK:
        return "BREAK";
    case AST_CONTINUE:
        return "CONTINUE";
    case AST_ANNOUNCE:
        return "ANNOUNCE";
    case AST_DISPLAY:
        return "DISPLAY";
    case AST_ASK_FOR:
        return "ASK_FOR";
    case AST_BINARY_OP:
        return "BINARY_OP";
    case AST_COMPARISON:
        return "COMPARISON";
    case AST_LOGICAL_OP:
        return "LOGICAL_OP";
    case AST_UNARY_OP:
        return "UNARY_OP";
    case AST_LITERAL_INT:
        return "LITERAL_INT";
    case AST_LITERAL_FLOAT:
        return "LITERAL_FLOAT";
    case AST_LITERAL_STRING:
        return "LITERAL_STRING";
    case AST_LITERAL_BOOL:
        return "LITERAL_BOOL";
    case AST_IDENTIFIER:
        return "IDENTIFIER";
    case AST_METRIC:
        return "METRIC";
    case AST_ACCOUNT_REF:
        return "ACCOUNT_REF";
    case AST_STRING_OP:
        return "STRING_OP";
    case AST_FEED_DECLARE:
        return "FEED_DECLARE";
    case AST_FEED_SET:
        return "FEED_SET";
    case AST_FEED_GET:
        return "FEED_GET";
    case AST_FEED_LENGTH:
        return "FEED_LENGTH";
    case AST_FEED_DISPLAY:
        return "FEED_DISPLAY";
    default:
        return "UNKNOWN";
    }
}

/* Print AST recursively */
void print_ast_node(ASTNode *node, int indent)
{
    if (!node)
        return;

    for (int i = 0; i < indent; i++)
        fprintf(output_file, "  ");
    fprintf(output_file, "├─ %s", get_node_type_name(node->type));

    if (node->sval)
        fprintf(output_file, " (%s)", node->sval);
    if (node->sval2)
        fprintf(output_file, " [%s]", node->sval2);
    if (node->type == AST_LITERAL_INT || node->type == AST_LITERAL_BOOL)
        fprintf(output_file, " [%d]", node->ival);
    if (node->type == AST_LITERAL_FLOAT)
        fprintf(output_file, " [%.2f]", node->fval);
    if (node->type == AST_LOOP || node->type == AST_LOOP_INCREMENT || node->type == AST_LOOP_DECREMENT)
        fprintf(output_file, " [start:%d, end:%d, step:%d]", node->ival, node->ival2, node->step);
    if (node->type == AST_LOOP_RANGE)
        fprintf(output_file, " [from:%d, to:%d]", node->ival, node->ival2);

    fprintf(output_file, "\n");

    if (node->condition)
    {
        for (int i = 0; i < indent; i++)
            fprintf(output_file, "  ");
        fprintf(output_file, "  Condition:\n");
        print_ast_node(node->condition, indent + 2);
    }

    if (node->body)
    {
        for (int i = 0; i < indent; i++)
            fprintf(output_file, "  ");
        fprintf(output_file, "  Body:\n");
        print_ast_node(node->body, indent + 2);
    }

    if (node->else_body)
    {
        for (int i = 0; i < indent; i++)
            fprintf(output_file, "  ");
        fprintf(output_file, "  Else:\n");
        print_ast_node(node->else_body, indent + 2);
    }

    if (node->left)
        print_ast_node(node->left, indent + 1);
    if (node->right)
        print_ast_node(node->right, indent + 1);
    if (node->param)
        print_ast_node(node->param, indent + 1);
}

/* Print entire AST */
void print_ast(ASTNode *root, int indent)
{
    if (!root)
        return;

    print_ast_node(root, indent);

    // Print all statements in sequence
    if (root->type == AST_PROGRAM && root->body)
    {
        ASTNode *stmt = root->body;
        while (stmt)
        {
            print_ast_node(stmt, indent + 1);
            stmt = stmt->next;
        }
    }
}

/* ========================================
 * AST MEMORY MANAGEMENT
 * ======================================== */

/* Free AST memory recursively */
void free_ast(ASTNode *node)
{
    if (!node)
        return;

    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->condition);
    free_ast(node->body);
    free_ast(node->else_body);
    free_ast(node->next);
    free_ast(node->param);

    if (node->sval)
        free(node->sval);
    if (node->sval2)
        free(node->sval2);

    free(node);
}

#endif /* AST_FUNCTIONS_H */
