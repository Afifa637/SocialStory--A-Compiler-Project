# symbol_table.h

## Purpose
Manages the global symbol table for the compiler. Stores accounts, user-defined variables (from `Ask for`), and function definitions. Also performs semantic checks at analysis time.

## Data Structure
Linked list of `SymbolEntry` structs. Each entry holds:
- `name` — string identifier
- `type` — `SYM_ACCOUNT`, `SYM_VARIABLE`, or `SYM_FUNCTION`
- Account metrics: `likes`, `followers`, `views`, `comments`, `shares`, `posts`, `stories` (int); `engagement_rate`, `reach`, `growth_rate` (float)
- Status flags: `is_viral`, `is_trending` (int 0/1)
- Function data: `function_body` (ASTNode*), `function_params` (ASTNode*)

## Key Functions

### `SymbolEntry* lookup_symbol(const char* name)`
Linear search through the linked list. Returns NULL if not found.

### `SymbolEntry* insert_symbol(const char* name, int sym_type)`
Allocates and prepends a new entry.

### `void check_account_exists(const char* name, int line)`
Calls `lookup_symbol`. If NULL, increments `semantic_errors` and prints `❌ Semantic error`.

### `void check_duplicate_account(const char* name, int line)`
If found, prints `⚠️ Warning: duplicate account`.

### `void print_symbol_table(FILE* fp)`
Dumps all entries in the format shown at the end of each output file.

## Global Variables Exposed
- `int semantic_errors` — count of semantic errors detected
