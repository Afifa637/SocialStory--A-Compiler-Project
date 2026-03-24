# SocialStoryScript Language Specification v1.0

## 1. Introduction

SocialStoryScript (SSS) is a compiled domain-specific language for modeling social media analytics. It provides a narrative syntax designed around social media concepts — accounts, followers, engagement, viral events — while implementing a complete compiler pipeline including lexical analysis, parsing, semantic checks, TAC generation, optimisation, and tree-walking interpretation.

### 1.1 Design Goals
- **Domain clarity:** Syntax mirrors how social media analysts describe their work
- **Type safety:** Compile-time and runtime type checking
- **Expressiveness:** Enough control flow to model real campaign scenarios
- **Teachability:** Demonstrates all major compiler phases clearly

---

## 2. Lexical Structure

### 2.1 Source encoding
UTF-8. Identifiers use ASCII characters only.

### 2.2 Comments
```
# single-line comment (hash)
// single-line comment (double slash)
/* multi-line comment */
```

### 2.3 Whitespace
Spaces, tabs, and newlines are ignored between tokens. Multi-word keywords match as a single token via Flex longest-match rules.

### 2.4 Identifiers
```
IDENT ::= ([A-Za-z_][A-Za-z0-9_]*)
        | ([0-9]+[A-Za-z_][A-Za-z0-9_]*)   # digit-prefixed extended form
```
Examples: `TechBrand`, `_underscore`, `124bro`, `2fast2furious`

### 2.5 Numeric Literals
```
INTEGER    ::= [0-9]+
FLOAT      ::= [0-9]+\.[0-9]+
HEX        ::= 0[xX][0-9a-fA-F]+
OCTAL      ::= 0[0-7]+
SCIENTIFIC ::= [0-9]+(\.[0-9]+)?[eE][+-]?[0-9]+
```

### 2.6 String Literals
```
STRING ::= '"' ([^\\"\n] | ESCAPE)* '"'
ESCAPE ::= '\\' [ntr\\"'0]
```

### 2.7 Boolean Literals
```
BOOL ::= "true" | "false"
```

### 2.8 Invalid Tokens
Any character not matching a valid token pattern is reported as a lexical error with the source line number. The compiler continues scanning after the error.

---

## 3. Type System

### 3.1 Primitive types

| Type | Storage | Used For |
|------|---------|---------|
| `int` | 32-bit signed | likes, followers, views, comments, shares, posts, stories |
| `float` | 32-bit IEEE 754 | engagement rate, reach, growth rate |
| `string` | heap char* | string literals, announce messages |
| `bool` | int (0/1) | is_viral, is_trending flags |

### 3.2 Account type
An `account` is a compound object containing all 10 metrics plus 2 status flags. Accounts are declared and stored in the symbol table.

### 3.3 Implicit type conversions
- `int` → `float`: automatic when assigning an integer value to a float metric. No warning.
- `float` → `int`: automatic with truncation. Emits a type warning at compile time.

Example:
```
# float-to-int: warning emitted
The account Brand began at 2.5 likes.    # likes is int; 2.5 truncated to 2
```

### 3.4 Type checking
Performed during semantic analysis. Function return values are untyped at the language level — functions return whatever expression appears in `Tell back`.

---

## 4. Expressions

### 4.1 Arithmetic expressions
```
expr  ::= expr "plus" term | expr "minus" term | term
term  ::= term "times" factor
        | term "multiply" factor
        | term "divided by" factor
        | term "divide" factor
        | term "modulo" factor
        | factor
factor ::= INTEGER | FLOAT | IDENTIFIER
         | "(" expr ")"
         | account_metric_ref
         | feed_access
         | feed_length
```

### 4.2 Operator precedence (highest first)
1. Parentheses `( )`
2. `times`, `multiply`, `divided by`, `divide`, `modulo`
3. `plus`, `minus`

### 4.3 Comparison expressions
```
comparison ::= account_metric_ref comparator expr
             | expr comparator expr
             | account_metric_ref "went viral"
             | comparison "also" comparison          # AND
             | comparison "either" comparison        # OR

comparator ::= "more than" | "less than" | "at least" | "at most"
             | "exactly" | "equal to" | "not equal to" | "different from"
             | "exceeded" | "dropped below" | "reached" | "stayed at"
```

### 4.4 Logical operators
```
"also"     # binary AND: comparison also comparison
"either"   # binary OR:  comparison either comparison
"opposite" # unary NOT:  When opposite comparison { ... }
```

### 4.5 Account metric references
```
account_metric_ref ::= IDENTIFIER metric
                     | IDENTIFIER "engagement rate"
                     | IDENTIFIER "growth rate"

metric ::= "likes" | "followers" | "views" | "comments" | "shares"
         | "posts" | "stories" | "reach"
```

---

## 5. Statements

### 5.1 Program wrapper
```
"Go live" "."
    statements
"End live" "."
```

### 5.2 Account creation
```
"The account" IDENTIFIER "was created" "."
```

### 5.3 Account initialisation
```
"The account" IDENTIFIER "started with" expr metric "."
"The account" IDENTIFIER "now has" expr metric "."
"The account" IDENTIFIER "began at" expr metric "."
```

### 5.4 Account update
```
"The account" IDENTIFIER "gained" expr metric "."
"The account" IDENTIFIER "lost" expr metric "."
"The account" IDENTIFIER "increased by" expr metric "."
"The account" IDENTIFIER "decreased by" expr metric "."
```

### 5.5 Story posting
```
"The account" IDENTIFIER "posted about" STRING "that had" expr "views" "."
```

### 5.6 Status flags
```
"The account" IDENTIFIER "is viral" "."
"The account" IDENTIFIER "is trending" "."
```

### 5.7 Display
```
"Display" IDENTIFIER "."                    # full account summary
"Display" IDENTIFIER metric "."             # single metric
"Display the feed at index" expr metric "." # feed slot display
```

### 5.8 Announce (output)
```
"Announce" STRING "."
```

### 5.9 Ask for (input)
```
"Ask for" IDENTIFIER "."
```
Reads one integer from stdin, stores in symbol table as `SYM_VARIABLE`.

### 5.10 Conditional statement
```
"When" comparison "{" statements "}" optional_else

optional_else ::= ε
               | "Otherwise" "{" statements "}"
               | "Otherwise if" comparison "{" statements "}" optional_else
```

Supports arbitrarily deep nesting and chaining.

Also supported:
```
"When" "opposite" comparison "{" statements "}" optional_else
```

### 5.11 Loop statements

**Every-day loop (while-style):**
```
"Every day for" INTEGER "days" ","
"{" statements "}"
```
Executes body exactly N times.

**Incrementing loop:**
```
"Every" INTEGER "days incrementing by" INTEGER
"{" statements "}"
```
Counts from 1 to N (first arg) in steps of K (second arg).

**Decrementing loop:**
```
"Every" INTEGER "days decrementing by" INTEGER
"{" statements "}"
```
Counts from N down to 1 in steps of K.

**Range loop:**
```
"For each follower from" expr "to" expr
"{" statements "}"
```
Iterates from start to end inclusive.

**Trending loop:**
```
"trending loop until" comparison
"{" statements "}"
```
Executes body until condition becomes true.

**Loop control:**
```
"Skip this post" "."    # continue: skip to next iteration
"Stop the story" "."    # break: exit loop immediately
```

### 5.12 Function definition
```
"The story of" IDENTIFIER "begins with" param_list
"{" statements "}"
"The story ends" "."

param_list ::= ε                       # zero parameters
             | IDENTIFIER              # one parameter
             | IDENTIFIER "," param_list  # two or more
```

### 5.13 Function call
```
"Tell" IDENTIFIER "."                            # zero arguments
"Tell" IDENTIFIER "with" arg_list "."            # one or more arguments

arg_list ::= expr | expr "," arg_list
```

### 5.14 Return statement
```
"Tell back" expr "."
```
Only valid inside a function body.

### 5.15 Built-in function calls
```
"Calculate virality for The account" IDENTIFIER "."
"Calculate virality for" IDENTIFIER "."
"Calculate engagement for The account" IDENTIFIER "."
"Analyze growth for The account" IDENTIFIER "."
"Check if trending for The account" IDENTIFIER "."
"Count total engagement" "."
"Find top post" "."
"Find max viral account" "."
"Reverse growth for The account" IDENTIFIER "."
```

### 5.16 Feed / array statements

**Declaration:**
```
"The feed contains" INTEGER "posts" "."
"The feed contains" INTEGER "stories" "."
```

**Indexed assignment:**
```
"The feed at index" expr "now has" expr metric "."
```

**Feed value in account expression:**
```
"the feed at index" expr metric    # used as an expr within now has / started with
```

**Feed length in expression:**
```
"the feed contains" ( "posts" | "stories" )   # returns feed size as int
```

**Collection iteration:**
```
"For each post in the feed" "{" statements "}"
"For each story in the feed" "{" statements "}"
```

---

## 6. Semantic Rules

### 6.1 Declaration before use
Every account or variable must be declared before it appears as an operand. Violation increments `semantic_errors` and prints a diagnostic.

### 6.2 Duplicate declarations
Declaring the same account twice with `was created` emits a warning but does not terminate compilation.

### 6.3 Function scope
Functions are defined at the top (program) level and callable from anywhere after their definition. There are no nested functions or local scopes — all symbols share a single global symbol table.

### 6.4 Parameter binding
On a function call, the runtime binds each argument value to the corresponding parameter name in the symbol table. Parameter names shadow any global with the same name for the duration of the call.

### 6.5 Arity checking
If the number of arguments in a `Tell` call does not match the number of parameters in the function definition, a semantic/runtime error is emitted.

### 6.6 Division by zero
Division or modulo by a literal `0` is detected at semantic analysis time. Division by a zero-valued variable is detected at runtime.

### 6.7 Feed bounds
Accessing `the feed at index N` where `N >= declared_size` emits a bounds error with the violating index.

---

## 7. Execution Model

Programs execute sequentially top-to-bottom. Control flow statements may alter the order. Functions execute their body when called and return to the call site.

The interpreter is a recursive tree-walker. Each AST node type has a corresponding handler. The symbol table is mutated in place during execution.

---

## 8. Error Categories

| Category | Phase | Exit Code |
|----------|-------|-----------|
| Lexical error | Scanning | 1 |
| Syntax error | Parsing | 1 (with recovery) |
| Semantic error | Analysis | 1 |
| Runtime error | Execution | 1 |
| Success | — | 0 |

---

## 9. Grammar Summary (EBNF)

```ebnf
program         = "Go live" "." statements "End live" "." ;
statements      = { statement } ;
statement       = account_create | account_init | account_update
                | story_post | status_flag
                | conditional | loop | loop_control
                | function_def | function_call | builtin_call
                | io_stmt | feed_decl | feed_assign | display ;

account_create  = "The account" ID "was created" "." ;
account_init    = "The account" ID ("started with"|"now has"|"began at") expr metric "." ;
account_update  = "The account" ID ("gained"|"lost"|"increased by"|"decreased by") expr metric "." ;
story_post      = "The account" ID "posted about" STRING "that had" expr "views" "." ;
status_flag     = "The account" ID ("is viral"|"is trending") "." ;

conditional     = "When" ["opposite"] comparison "{" statements "}" optional_else ;
optional_else   = [ "Otherwise" ( "{" statements "}" | "if" comparison "{" statements "}" optional_else ) ] ;

loop            = every_loop | incr_loop | decr_loop | range_loop | trending_loop ;
every_loop      = "Every day for" INT "days" "," "{" statements "}" ;
incr_loop       = "Every" INT "days incrementing by" INT "{" statements "}" ;
decr_loop       = "Every" INT "days decrementing by" INT "{" statements "}" ;
range_loop      = "For each follower from" expr "to" expr "{" statements "}" ;
trending_loop   = "trending loop until" comparison "{" statements "}" ;
loop_control    = ("Skip this post"|"Stop the story") "." ;

function_def    = "The story of" ID "begins with" [param_list] "{" statements "}" "The story ends" "." ;
param_list      = ID { "," ID } ;
function_call   = "Tell" ID ["with" arg_list] "." ;
return_stmt     = "Tell back" expr "." ;
arg_list        = expr { "," expr } ;

io_stmt         = ("Announce" STRING | "Ask for" ID | display) "." ;
display         = "Display" ID [metric] | "Display the feed at index" expr metric ;

feed_decl       = "The feed contains" INT ("posts"|"stories") "." ;
feed_assign     = "The feed at index" expr "now has" expr metric "." ;

expr    = term { ("plus"|"minus") term } ;
term    = factor { ("times"|"divided by"|"modulo") factor } ;
factor  = INT | FLOAT | ID | "(" expr ")" | account_metric_ref | feed_access | feed_length ;

comparison      = account_metric_ref comparator expr
                | expr comparator expr
                | account_metric_ref "went viral"
                | comparison ("also"|"either") comparison ;

comparator      = "more than" | "less than" | "at least" | "at most"
                | "exactly" | "not equal to" | "different from"
                | "exceeded" | "dropped below" | "reached" | "stayed at" ;

metric          = "likes"|"followers"|"views"|"comments"|"shares"|"posts"|"stories"
                | "engagement rate"|"reach"|"growth rate" ;
```

---

## 10. Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | March 2026 | Initial release — full pipeline, 5 optimisation passes, 18 tests |
