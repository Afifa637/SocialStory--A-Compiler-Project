# ast_functions.h

## Purpose
Utility functions for creating, connecting, and freeing Abstract Syntax Tree nodes. Every parser semantic action calls these helpers — the file is the foundational building block of the AST.

## Key Functions

### `ASTNode* make_node(ASTNodeType type)`
Allocates a zero-initialised AST node of the given type.

### `ASTNode* make_node_with_int(ASTNodeType type, int val)`
Shortcut: allocates node and sets `node->ival = val`.

### `ASTNode* make_node_with_float(ASTNodeType type, float val)`
Shortcut: allocates node and sets `node->fval = val`.

### `ASTNode* make_node_with_string(ASTNodeType type, char* str)`
Shortcut: allocates node and sets `node->sval = strdup(str)`.

### `ASTNode* make_binary_op(ASTNodeType type, ASTNode* left, ASTNode* right)`
Creates a two-child node. Used for binary expressions, comparisons, logical ops.

### `void free_ast(ASTNode* node)`
Recursively frees the entire tree and all string values.

## Integration
- **Called by:** `socialstory_parser.y` in every grammar action
- **Used by:** `tac_generator.h`, `interpreter.h`, `statistics.h`
- **Depends on:** ASTNodeType enum defined in `socialstory_parser.y`
