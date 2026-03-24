# interpreter.h

## Purpose
Tree-walking runtime interpreter. Executes the program by recursively traversing the AST and dispatching each node type to its handler. Updates the symbol table as execution proceeds and writes output to the report file.

## Execution Entry Point

### `void execute_program(ASTNode* root)`
Called by the compiler pipeline after optimisation. Walks the root node's children sequentially.

## Core Dispatch Functions

### `void execute_statement(ASTNode* node)`
Dispatches on `node->type` to the appropriate handler.

### `int execute_expression(ASTNode* node)`
Evaluates an integer expression recursively. Handles `LITERAL_INT`, `IDENTIFIER`, `ACCOUNT_REF`, `BINARY_OP`, `FEED_GET`, `FEED_LENGTH`.

### `float execute_expression_float(ASTNode* node)`
Same as above but for float expressions (engagement rate, reach, growth rate).

### `int execute_comparison(ASTNode* node)`
Evaluates a comparison node. Returns 0 (false) or 1 (true). Handles all 9 comparison operators and logical AND/OR/NOT.

## Loop Implementation
All five loop types share a common structure:
1. Check condition / counter
2. Execute body (as statement list)
3. Check `loop_break_flag` — if set, exit loop
4. Check `loop_continue_flag` — if set, reset flag and skip remainder of body
5. Update counter / check condition again

## Built-in Function Implementations
Each `calculate_*` / `find_*` / `analyze_*` built-in prints a formatted analytics report to the output file using the account's current symbol table values.

## Output
All `Announce`, `Display`, and built-in function output goes to:
- `output_file` (the structured report)
- `stdout` (the terminal, prefixed with `[Line N]`)
