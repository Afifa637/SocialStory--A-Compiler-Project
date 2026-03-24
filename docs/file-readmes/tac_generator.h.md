# tac_generator.h

## Purpose
Generates Three-Address Code (TAC) intermediate representation by walking the AST. TAC is a standard IR where each instruction has at most three addresses (result, arg1, arg2) and one operator.

## TAC Instruction Structure
```c
typedef struct TACInstruction {
    char* op;      // operator: "+", "-", "*", "/", "=", "goto", "if", etc.
    char* arg1;    // left operand or condition
    char* arg2;    // right operand
    char* result;  // destination
    int label;     // label number (-1 if not a label)
    struct TACInstruction* next;
} TACInstruction;
```

## Key Functions

### `char* new_temp()`
Returns next temp name: `t0`, `t1`, `t2`, ...

### `char* new_label()`
Returns next label: `L0`, `L1`, `L2`, ...

### `void emit_tac(char* op, char* arg1, char* arg2, char* result)`
Appends a new instruction to the TAC linked list (`tac_head`/`tac_tail`).

### `char* generate_tac_expression(ASTNode* node)`
Recursively generates TAC for an expression subtree. Returns the name of the temp holding the result.

### `void generate_tac(ASTNode* node, FILE* fp)`
Top-level TAC generation entry point. Walks the full AST and emits all instructions.

## Output Format
```
   1: t0 = 10
   2: t1 = 15
   3: t2 = t0 + t1
   4: Brand.likes = t2
```

## Global Variables
- `int temp_counter` — incremented by `new_temp()`
- `int label_counter` — incremented by `new_label()`
