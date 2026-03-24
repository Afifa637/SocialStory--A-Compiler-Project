# SocialStoryScript Compiler — Architecture

## System Overview

SocialStoryScript follows a classic multi-pass compiler pipeline with a tree-walking interpreter as the backend. All six phases are visible in the output for each compilation run.

```
Source file (.txt)
      │
      ▼
  [Phase 1] Lexical Analysis     socialstory.l       → Token stream
      │
      ▼
  [Phase 2] Syntax Analysis      socialstory_parser.y → Abstract Syntax Tree
      │
      ▼
  [Phase 3] Semantic Analysis    symbol_table.h       → Validated AST
      │
      ▼
  [Phase 4] TAC Generation       tac_generator.h      → Three-address code
      │
      ▼
  [Phase 5] Optimisation         optimizer.h          → Optimised TAC
      │
      ▼
  [Phase 6] Execution            interpreter.h        → Program output
```

---

## Phase 1: Lexical Analysis

**File:** `socialstory.l`  
**Tool:** Flex 2.6+

The lexer tokenises the input source character-by-character and converts character sequences into typed tokens. SocialStoryScript uses many multi-word tokens (e.g., `"The account"`, `"started with"`, `"more than"`) which Flex matches via longest-match rules.

### Token categories

| Category | Examples | Count |
|----------|---------|-------|
| Program delimiters | `Go live`, `End live` | 2 |
| Account keywords | `The account`, `was created`, `started with`, `gained`, `lost` | 15+ |
| Metric names | `likes`, `followers`, `views`, `comments`, `shares` | 10 |
| Arithmetic operators | `plus`, `minus`, `times`, `divided by`, `modulo` | 8 (with aliases) |
| Comparison operators | `more than`, `less than`, `at least`, `exceeded`, `went viral` | 11 |
| Logical operators | `also`, `either`, `opposite` | 3 |
| Control flow | `When`, `Otherwise if`, `Otherwise`, `While`, `trending loop` | 8 |
| Loop keywords | `Every day for`, `incrementing by`, `decrementing by`, `For each follower from` | 6 |
| Function keywords | `The story of`, `begins with`, `Tell back`, `The story ends`, `Tell` | 5 |
| Feed keywords | `The feed contains`, `at index`, `now has`, `For each post in the feed` | 6 |
| I/O | `Announce`, `Display`, `Ask for` | 3 |
| Built-in functions | `Calculate virality for`, `Analyze growth for`, `Count total engagement` | 12 |
| Literals | INTEGER, FLOAT, HEX, OCTAL, SCIENTIFIC, STRING, CHAR, BOOL | 8 |
| Identifiers | standard + digit-prefix extended form | 1 |
| **Total** | | **112+** |

### Error handling
- Invalid characters reported with line number and `❌ LEXICAL ERROR` prefix
- Unterminated strings detected before EOF
- Unterminated multi-line comments detected before EOF
- Error count tracked; non-zero count causes non-zero exit

### Special features
- `%option caseless` — case-insensitive keyword matching (input is more user-friendly)
- `%option yylineno` — automatic line tracking
- Extended identifier rule allows `124bro`, `99problems`, `2fast2furious`
- Identifier text is preserved exactly; symbol table comparisons remain strict (`Flow` and `flow` are distinct names)

---

## Phase 2: Syntax Analysis

**File:** `socialstory_parser.y`  
**Tool:** Bison 3.x (LALR parser)

### Grammar size
- 1,387 source lines
- 200+ grammar productions
- 0 shift/reduce conflicts (fully resolved)

### Grammar structure

```
program         → "Go live" "." statements "End live" "."
statements      → statement | statement statements
statement       → account_create
               | account_init
               | account_update
               | conditional
               | loop
               | function_def
               | function_call
               | builtin_call
               | io_statement
               | feed_declaration
               | feed_assignment

conditional     → "When" comparison "{" statements "}" optional_else
optional_else   → ε | "Otherwise" "{" statements "}"
                | "Otherwise if" comparison "{" statements "}" optional_else

loop            → every_day_loop
               | incrementing_loop
               | decrementing_loop
               | range_loop
               | trending_loop

expression      → expression "plus" term | expression "minus" term | term
term            → term "times" factor | term "divided by" factor | factor
factor          → NUMBER | FLOAT | IDENTIFIER | "(" expression ")" | account_metric_ref

comparison      → account_metric_ref comparator expression
               | expression comparator expression
               | account_metric_ref "went viral"
               | comparison "also" comparison
               | comparison "either" comparison
```

### AST node types (34)
`PROGRAM`, `ACCOUNT_CREATE`, `ACCOUNT_INIT`, `ACCOUNT_UPDATE`, `STORY_POST`, `CONDITIONAL`, `LOOP`, `LOOP_INCREMENT`, `LOOP_DECREMENT`, `LOOP_RANGE`, `LOOP_COLLECTION`, `LOOP_TRENDING`, `FUNCTION_DEF`, `FUNCTION_CALL`, `BUILTIN_CALL`, `RETURN`, `BREAK`, `CONTINUE`, `ANNOUNCE`, `DISPLAY`, `ASK_FOR`, `BINARY_OP`, `COMPARISON`, `LOGICAL_OP`, `UNARY_OP`, `LITERAL_INT`, `LITERAL_FLOAT`, `LITERAL_STRING`, `LITERAL_BOOL`, `IDENTIFIER`, `METRIC`, `ACCOUNT_REF`, `STRING_OP`, `FEED_GET`, `FEED_LENGTH`

### Error recovery
Parser uses Bison's built-in error recovery. On a malformed statement, the parser emits a diagnostic with the line number and continues to the next synchronisation point, allowing subsequent valid statements to parse and execute.

---

## Phase 3: Semantic Analysis

**File:** `symbol_table.h`

### Symbol table structure
The symbol table is a linked list of `SymbolEntry` nodes. Each entry stores:
- Name (string)
- Type: `SYM_ACCOUNT`, `SYM_VARIABLE`, or `SYM_FUNCTION`
- All account metrics (int and float)
- Status flags (`is_viral`, `is_trending`)
- Function body AST pointer and parameter list

### Semantic checks performed

| Check | Trigger | Action |
|-------|---------|--------|
| Undeclared variable | `now has`, `gained`, `Display` on unknown name | Increment `semantic_errors`, print error with line |
| Duplicate account | Second `was created` for same name | Print warning, continue |
| Float-to-int conversion | `began at` (float) assigned to int metric like `likes` | Print type warning |
| Division by zero | `/` or `divided by` with literal `0` | Print error, increment `semantic_errors` |
| Feed out-of-bounds | Index >= declared feed size | Print bounds error with index |
| Function arity | `Tell FuncName with` arg count != param count | Print arity error |

### Non-zero exit
If `semantic_errors > 0` after analysis, the compiler exits with code 1. This is the correct behaviour for error-detection tests.

---

## Phase 4: TAC Generation

**File:** `tac_generator.h`

### TAC format
Each instruction: `result = arg1 op arg2`

For unary or assignment: `result = arg1`

For control flow:
```
if arg1 op arg2 goto L0
goto L1
L0:
```

### Expression linearisation example
Source: `The account Brand now has 10 plus 5 times 20 likes.`

Generated TAC:
```
t0 = 10
t1 = 5
t2 = 20
t3 = t1 * t2     # 5 * 20 = 100  (precedence: * before +)
t4 = t0 + t3     # 10 + 100 = 110
Brand.likes = t4
```

### Feed access TAC
```
t0 = 0           # index literal
feed[t0].likes = 1200    # feed assignment
t1 = feed[t0].likes      # feed read
```

Note: the index temp `t0` is embedded in the instruction name string, not referenced as a standalone operand. The DCE pass therefore identifies it as unused and eliminates `t0 = 0`.

### Control flow TAC (conditional example)
```
t0 = Brand.likes
if t0 > 1000 goto L0
goto L1
L0:
    print "viral!"
    goto L2
L1:
    print "not viral"
L2:
```

---

## Phase 5: Optimisation

**File:** `optimizer.h`

### Pass execution order
All 6 passes run sequentially on the same TAC linked list.

```
original_count = count_instructions(tac)

Pass 1: optimize_temp_constant_propagation()
Pass 2: optimize_constant_folding()
Pass 3: optimize_algebraic()
Pass 4: optimize_strength_reduction()
Pass 5: optimize_copy_propagation()
Pass 6: optimize_dead_code()

optimized_count = count_instructions(tac)
reduction = (original_count - optimized_count) / original_count * 100
```

### Pass 1: Constant Folding
Fires when `instr->arg1` and `instr->arg2` are both numeric constant strings (no `t` prefix).
Replaces `t = const1 op const2` with `t = result`.

### Pass 2: Algebraic Simplification
Checks specific constant values in operands:
- `x + 0` → `x` (remove instruction, replace with copy)
- `x * 1` → `x`
- `x * 0` → `0`
- `x - 0` → `x`
- `x / 1` → `x`

### Pass 3: Strength Reduction
Fires for multiplication by power-of-two constants (`2`, `4`, `8`) with non-constant operands.
Transforms examples:
- `t = x * 2` → `t = x + x`
- `t = x * 4` → `t0 = x + x; t = t0 + t0`
- `t = x * 8` → `t0 = x + x; t1 = t0 + t0; t = t1 + t1`

### Pass 4: Copy Propagation
Finds copy assignments `dst = src` and replaces downstream uses of `dst` with `src`
until `dst` is redefined.

### Pass 5: Dead Code Elimination
Two-pass algorithm:
1. Mark all temps that appear as `arg1` or `arg2` in any instruction
2. Remove any `t = value` instruction where `t` is unmarked

This effectively removes:
- Feed index temporaries (embedded in feed instruction strings, never used as standalone args)
- Temporaries overwritten before use
- Intermediate temps from complex expression chains where only the final result is consumed

### Real reduction reporting
```
Instructions before: N
Instructions after:  M
Instructions removed: N-M
Reduction: (N-M)/N * 100.0%
```

---

## Phase 6: Execution

**File:** `interpreter.h`

### Execution model
Tree-walking interpreter. The `execute_program()` function recursively visits each AST node and dispatches to the appropriate handler based on `node->type`.

### Dispatch table (key node types)

| Node Type | Handler Action |
|-----------|---------------|
| `AST_PROGRAM` | Execute all child statements in sequence |
| `AST_ACCOUNT_CREATE` | Insert new SYM_ACCOUNT into symbol table |
| `AST_ACCOUNT_INIT` | Look up account, set metric value |
| `AST_ACCOUNT_UPDATE` | Look up account, add/subtract metric |
| `AST_CONDITIONAL` | Evaluate condition, execute body or else |
| `AST_LOOP` | While-style: repeat body while condition holds |
| `AST_LOOP_INCREMENT` | Count up from start to end by step |
| `AST_LOOP_DECREMENT` | Count down from start to end by step |
| `AST_LOOP_RANGE` | For-each over range [A, B] |
| `AST_LOOP_TRENDING` | Execute body until condition |
| `AST_FUNCTION_DEF` | Store function body + params in symbol table |
| `AST_FUNCTION_CALL` | Bind args to params, execute body, collect return |
| `AST_BUILTIN_CALL` | Execute one of 12 built-in analytics functions |
| `AST_ANNOUNCE` | Print string to output file |
| `AST_DISPLAY` | Print account metrics or single metric |
| `AST_ASK_FOR` | Read integer from stdin, store in symbol table |
| `AST_BINARY_OP` | Evaluate left and right, apply operator |
| `AST_COMPARISON` | Evaluate and compare; return 0 or 1 |
| `AST_LOGICAL_OP` | AND / OR of two comparison results |

### Runtime type handling
Integer and float expressions use separate evaluation paths (`execute_expression` and `execute_expression_float`). When a float is assigned to an integer metric, truncation occurs with a warning logged.

### Break and continue
`loop_break_flag` and `loop_continue_flag` global variables are set by `AST_BREAK` / `AST_CONTINUE` handlers. Each loop body checks these flags after each statement and exits/continues accordingly.

---

## Data Flow Summary

```
Source code
    → [Flex] → Token stream
    → [Bison] → AST (heap-allocated nodes, linked tree)
    → [symbol_table.h] → Symbol table populated, semantic errors counted
    → [tac_generator.h] → TAC linked list (TACInstruction structs)
    → [optimizer.h] → Same linked list modified in place, instructions removed
    → [interpreter.h] → Symbol table updated during execution, output written
    → Output file (output_*.txt) + stdout
```

## Error Handling Summary

| Phase | Error Type | Output |
|-------|-----------|--------|
| Lexical | Invalid character | `❌ LEXICAL ERROR at line N:` |
| Lexical | Unterminated string | `❌ LEXICAL ERROR at line N:` |
| Syntax | Grammar violation | `⚠️ syntax error at line N` + recovery |
| Semantic | Undeclared variable | `❌ Semantic error at line N:` |
| Semantic | Duplicate account | `⚠️ Warning at line N:` |
| Semantic | Type mismatch | `⚠️ Type warning at line N:` |
| Runtime | Division by zero | `❌ Runtime error at line N:` |
| Runtime | Feed out-of-bounds | `❌ Index error at line N:` |
| Runtime | Arity mismatch | `❌ Arity error at line N:` |
