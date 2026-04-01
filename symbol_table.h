#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Init account metrics
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

    // init function data
    entry->function_body = NULL;
    entry->function_params = NULL;

    // add to front of list
    entry->next = symbol_table;
    symbol_table = entry;

    return entry;
}

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

// Wrapper for print_symbol_table (for compatibility) 
void print_symbol_table_to_file(FILE *fp)
{
    FILE *old_output = output_file;
    if (fp)
        output_file = fp;
    print_symbol_table();
    output_file = old_output;
}

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

void check_account_exists(const char *name, int line)
{
    SymbolEntry *symbol = lookup_symbol(name);

    if (!symbol)
    {
        // symbol doesn't exist at all; this is an error 
        fprintf(stderr, "❌ Error line %d: Undeclared symbol '%s'\n", line, name);
        fprintf(output_file, "❌ Error line %d: Undeclared symbol '%s'\n", line, name);
        semantic_errors++;
    }
    else if (symbol->type == SYM_VARIABLE)
    {
    }
    else if (symbol->type == SYM_ACCOUNT)
    {
       
    }
    else if (symbol->type == SYM_FUNCTION)
    {
        fprintf(stderr, "⚠️  Warning line %d: '%s' is a function, not an account or variable\n", line, name);
        fprintf(output_file, "⚠️  Warning line %d: '%s' is a function, not an account or variable\n", line, name);
    }
}

void check_duplicate_account(const char *name, int line)
{
    SymbolEntry *existing = lookup_symbol(name);
    if (existing && existing->type == SYM_ACCOUNT)
    {
        fprintf(stderr, "⚠️  Warning line %d: Account '%s' already exists\n", line, name);
        fprintf(output_file, "⚠️  Warning line %d: Account '%s' already exists\n", line, name);
    }
}

#endif