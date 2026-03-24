/* ========================================
 * STATISTICS.H
 * Compiler Statistics Module
 * 
 * This module handles:
 * - AST node counting
 * - AST depth calculation
 * - Symbol table statistics
 * - Compiler metrics reporting
 * ======================================== */

#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>

/* ========================================
 * AST STATISTICS
 * ======================================== */

/* Count total number of nodes in AST */
int count_ast_nodes(ASTNode* node) {
    if (!node) return 0;
    
    return 1 + 
           count_ast_nodes(node->left) + 
           count_ast_nodes(node->right) +
           count_ast_nodes(node->condition) +
           count_ast_nodes(node->body) +
           count_ast_nodes(node->else_body) +
           count_ast_nodes(node->next) +
           count_ast_nodes(node->param);
}

/* Calculate maximum depth of AST */
int calculate_ast_depth(ASTNode* node, int current_depth) {
    if (!node) return current_depth;
    
    int max_depth = current_depth;
    
    // Calculate depth of all child nodes
    int depths[] = {
        calculate_ast_depth(node->left, current_depth + 1),
        calculate_ast_depth(node->right, current_depth + 1),
        calculate_ast_depth(node->condition, current_depth + 1),
        calculate_ast_depth(node->body, current_depth + 1),
        calculate_ast_depth(node->else_body, current_depth + 1),
        calculate_ast_depth(node->param, current_depth + 1),
        calculate_ast_depth(node->next, current_depth)
    };
    
    // Find maximum depth
    for (int i = 0; i < 7; i++) {
        if (depths[i] > max_depth) {
            max_depth = depths[i];
        }
    }
    
    return max_depth;
}

/* Print AST statistics to file */
void print_ast_statistics(FILE* fp) {
    int total_nodes = count_ast_nodes(ast_root);
    int max_depth = calculate_ast_depth(ast_root, 0);
    
    fprintf(fp, "\n📊 Abstract Syntax Tree Statistics:\n");
    fprintf(fp, "=====================================\n");
    fprintf(fp, "   Total nodes: %d\n", total_nodes);
    fprintf(fp, "   Maximum depth: %d\n", max_depth);
    
    if (max_depth > 0) {
        float avg_branching = (float)total_nodes / max_depth;
        fprintf(fp, "   Average branching factor: %.2f\n", avg_branching);
    }
    
    fprintf(fp, "=====================================\n");
}

/* ========================================
 * SYMBOL TABLE STATISTICS
 * ======================================== */

/* Count symbols by type and print statistics */
void print_symbol_table_stats(FILE* fp) {
    int account_count = 0;
    int function_count = 0;
    int variable_count = 0;
    
    SymbolEntry* sym = symbol_table;
    while (sym) {
        switch (sym->type) {
            case SYM_ACCOUNT:
                account_count++;
                break;
            case SYM_FUNCTION:
                function_count++;
                break;
            case SYM_VARIABLE:
                variable_count++;
                break;
        }
        sym = sym->next;
    }
    
    int total_symbols = account_count + function_count + variable_count;
    
    fprintf(fp, "\n📋 Symbol Table Statistics:\n");
    fprintf(fp, "============================\n");
    fprintf(fp, "   Total symbols: %d\n", total_symbols);
    fprintf(fp, "   Accounts: %d\n", account_count);
    fprintf(fp, "   Functions: %d\n", function_count);
    fprintf(fp, "   Variables: %d\n", variable_count);
    fprintf(fp, "============================\n");
}

#endif /* STATISTICS_H */
