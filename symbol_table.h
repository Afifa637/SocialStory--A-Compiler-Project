/* ========================================
 * SYMBOL_TABLE.H (FIXED FOR INPUT VARIABLES)
 * Symbol Table Management
 *
 * This module handles:
 * - Symbol table operations (insert, lookup)
 * - Account tracking
 * - Function definitions
 * - Semantic checking
 * - Variable support (for Ask for input)
 * ======================================== */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================
 * SYMBOL TABLE OPERATIONS
 * ======================================== */

/* Look up a symbol in the symbol table */
SymbolEntry *lookup_symbol(const char *name)
{
    SymbolEntry *current = symbol_table;
    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Insert a new symbol into the symbol table */
SymbolEntry *insert_symbol(const char *name, int sym_type)
{
    SymbolEntry *entry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
    if (!entry)
    {
        fprintf(stderr, "❌ Memory allocation failed for symbol\n");
        exit(1);
    }

    entry->name = strdup(name);
    entry->type = sym_type;

    // Initialize account metrics
    entry->likes = 0;
    entry->followers = 0;
    entry->views = 0;
    entry->comments = 0;
    entry->shares = 0;
    entry->posts = 0;
    entry->stories = 0;
    entry->engagement_rate = 0.0;
    entry->reach = 0.0;
    entry->growth_rate = 0.0;
    entry->is_viral = 0;
    entry->is_trending = 0;

    // Initialize function data
    entry->function_body = NULL;
    entry->function_params = NULL;

    // Add to front of list
    entry->next = symbol_table;
    symbol_table = entry;

    return entry;
}

/* ========================================
 * SYMBOL TABLE PRINTING
 * ======================================== */

/* Print symbol table to output file */
void print_symbol_table()
{
    fprintf(output_file, "\n📋 Symbol Table:\n");
    fprintf(output_file, "================\n");

    SymbolEntry *current = symbol_table;
    while (current)
    {
        fprintf(output_file, "%-20s | Type: ", current->name);

        switch (current->type)
        {
        case SYM_ACCOUNT:
            fprintf(output_file, "Account | Likes: %d, Followers: %d, Views: %d, Comments: %d, Shares: %d\n",
                    current->likes, current->followers, current->views,
                    current->comments, current->shares);
            break;
        case SYM_FUNCTION:
            fprintf(output_file, "Function\n");
            break;
        case SYM_VARIABLE:
            fprintf(output_file, "Variable | Value: %d (int), %.2f (float)\n",
                    current->likes, current->engagement_rate);
            break;
        }

        current = current->next;
    }
    fprintf(output_file, "================\n");
}

/* Wrapper for print_symbol_table (for compatibility) */
void print_symbol_table_to_file(FILE *fp)
{
    FILE *old_output = output_file;
    if (fp)
        output_file = fp;
    print_symbol_table();
    output_file = old_output;
}

/* ========================================
 * MEMORY MANAGEMENT
 * ======================================== */

/* Free all entries in the symbol table */
void free_symbol_table()
{
    SymbolEntry *current = symbol_table;
    while (current)
    {
        SymbolEntry *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    symbol_table = NULL;
}

/* ========================================
 * SEMANTIC CHECKING (FIXED FOR VARIABLES)
 * ======================================== */

/* Check if a symbol (account OR variable) exists before using it
 * CRITICAL FIX: Now accepts both accounts and variables!
 * This allows variables from "Ask for" to be used in expressions.
 */
void check_account_exists(const char *name, int line)
{
    SymbolEntry *symbol = lookup_symbol(name);

    if (!symbol)
    {
        /* Symbol doesn't exist at all - this is an error */
        fprintf(stderr, "❌ Error line %d: Undeclared symbol '%s'\n", line, name);
        fprintf(output_file, "❌ Error line %d: Undeclared symbol '%s'\n", line, name);
        semantic_errors++;
    }
    else if (symbol->type == SYM_VARIABLE)
    {
        /* Symbol exists as a variable - this is OK!
         * Variables from "Ask for" can be used like account metrics */
        /* No error - silently accept */
    }
    else if (symbol->type == SYM_ACCOUNT)
    {
        /* Symbol exists as an account - perfect! */
        /* No error */
    }
    else if (symbol->type == SYM_FUNCTION)
    {
        /* Symbol is a function - might be unexpected in this context */
        fprintf(stderr, "⚠️  Warning line %d: '%s' is a function, not an account or variable\n", line, name);
        fprintf(output_file, "⚠️  Warning line %d: '%s' is a function, not an account or variable\n", line, name);
    }
}

/* Check for duplicate account declarations */
void check_duplicate_account(const char *name, int line)
{
    SymbolEntry *existing = lookup_symbol(name);
    if (existing && existing->type == SYM_ACCOUNT)
    {
        fprintf(stderr, "⚠️  Warning line %d: Account '%s' already exists\n", line, name);
        fprintf(output_file, "⚠️  Warning line %d: Account '%s' already exists\n", line, name);
    }
}

#endif /* SYMBOL_TABLE_H */