# SocialStoryScript Compiler

**SocialStoryScript** is a domain-specific language for modeling social-media growth,
engagement, virality, campaign performance, and feed analytics through readable,
high-level social-media-oriented syntax.

```
Pipeline:  Source → Lex → Parse → AST → TAC → Optimize → Execute
```

---

## Why this language is useful

- Run account-level engagement analysis with readable rules.
- Simulate follower and interaction growth with loop-based scenarios.
- Detect virality/trending signals and strategy thresholds.
- Compare campaign outcomes across multiple accounts.
- Analyze post/feed performance and input-driven planning workflows.

---

## Who this is for

- Students demonstrating compiler engineering on a purposeful DSL
- Social-media analytics learners modeling growth behavior
- Instructors evaluating both language usefulness and implementation quality

---

## Quick Start

```bash
make                                    # build
./socialstory sample_programs/01_account_baseline_report.txt   # run a demo
make test                               # run the full test suite
```

On Windows shells, use `./socialstory.exe` when needed.

---

## Single-file showcase (with explicit runtime input values)

Use:

```bash
make showcase
```

This runs `INPUT.showcase_all_features.txt` and pipes runtime values from:

- `INPUT.showcase_runtime_values.txt`

Current values in that file are:

- line 1: `12` (for `Ask for input_likes.`)
- line 2: `100` (for `Ask for input_followers.`)

Showcase report output file:

- `OUTPUT.showcase_all_feature.txt`

---

## Run these first (evaluator fast path)

1. `sample_programs/01_account_baseline_report.txt` — clear baseline analytics workflow
2. `sample_programs/05_input_driven_strategy.txt` — input-driven decision logic
3. `sample_programs/08_optimizer_meaningful_workload.txt` — meaningful TAC + optimization showcase

Then run:

```bash
make test
```

Rubric-proof quick map:

- `tests/lexical_identifiers_test.txt` → lexical policy, literals, token errors, comments
- `tests/controlflow_loops_test.txt` → control-flow correctness, logical ops, loop behavior
- `tests/arrays_optimizer_integration_test.txt` → feed analytics + intermediate-code optimization evidence

Best 2 quick quality-proof tests (if evaluator time is limited):

- `tests/lexical_identifiers_test.txt` (lexical rigor + error recovery)
- `tests/arrays_optimizer_integration_test.txt` (advanced features: feed analytics, TAC, optimizer, runtime safety)

Flagship 4-test path (full showcase):

- `tests/lexical_identifiers_test.txt`
- `tests/semantic_runtime_safety_test.txt`
- `tests/input_io_test.txt`
- `tests/arrays_optimizer_integration_test.txt`

---

## Why this DSL is useful in practice

This DSL models common social-media analytics tasks that are easy to explain and verify:

- account metric lifecycle tracking (`likes`, `followers`, `views`, etc.)
- growth-policy simulation with conditional branches and looped updates
- feed/post analysis with indexed retrieval and iteration
- input-driven planning for scenario-based strategy decisions
- built-in analytics reports (engagement, virality, trend checks)

The same programs also expose compiler internals (AST, TAC, optimizer), so usefulness and compiler quality are visible together.

---

## Additional demos worth running

1. `sample_programs/01_account_baseline_report.txt`  
    Fast account setup + baseline analytics output.
2. `sample_programs/05_input_driven_strategy.txt`  
    Input-driven decision logic (interactive analysis).
3. `sample_programs/06_feed_weekly_post_analysis.txt`  
    Weekly post/feed analytics workflow.

---

## Use cases at a glance

| Use case | Demo file | Key language features shown |
|---|---|---|
| Baseline account analytics | `sample_programs/01_account_baseline_report.txt` | Account modeling, metrics, built-ins, display |
| Engagement classification | `sample_programs/02_engagement_health_check.txt` | `When` / `Otherwise if` / `Otherwise`, logical operators |
| 30-day growth simulation | `sample_programs/03_30_day_growth_simulation.txt` | Loops, control flow, strategy threshold checks |
| Campaign A/B decision | `sample_programs/04_campaign_a_b_comparison.txt` | Account comparison, conditional branching |
| Interactive planning | `sample_programs/05_input_driven_strategy.txt` | `Ask for`, expression-based updates, decision policy |
| Weekly feed analytics | `sample_programs/06_feed_weekly_post_analysis.txt` | Feed declare/set/get/length/iterate, feed built-ins |
| Built-in analytics report | `sample_programs/07_builtins_analytics_report.txt` | Virality, engagement, growth, spam/clamp/text built-ins |
| Optimization showcase | `sample_programs/08_optimizer_meaningful_workload.txt` | Meaningful metric expressions + TAC optimization output |

---

## What makes it technically strong

- Complete compiler pipeline: lexer, parser, AST, semantic checks, TAC, optimizer, interpreter.
- Deterministic exact-output testing across 8 organized feature groups.
- Runtime safety checks for division by zero, undeclared symbols, and feed bounds.
- Built-in analytics and user-defined functions in one coherent execution model.

---

## Language Overview

SocialStoryScript programs open with `Go live.` and close with `End live.`
Comments use `//` (single-line) or `/* … */` (multi-line).

### Identifiers

The lexer (`socialstory.l`) accepts:

Keyword matching is case-insensitive for usability, while identifier text is preserved. In practice, symbol comparisons remain strict (`Flow` and `flow` are different symbols).

| Pattern | Examples | Valid? |
|---|---|---|
| Letter or `_` start, then letters/digits/`_` | `TechInfluencer`, `_underscore` | ✅ |
| Digit-start followed by at least one letter or `_` | `124bro`, `99problems`, `2fast2furious` | ✅ |
| Pure digits | `42`, `0`, `100` | ✅ (number literal) |
| `@`, `$`, `^`, `&`, `\|`, `!` | `@handle`, `$var` | ❌ lexical error |

### Number Literals

| Form | Example | Produces |
|---|---|---|
| Integer | `100` | `T_NUMBER` |
| Hexadecimal | `0xFF` | `T_NUMBER` (255) |
| Octal | `010` | `T_NUMBER` (8) |
| Float | `3.14` | `T_DECIMAL` |
| Scientific | `1.5e2` | `T_DECIMAL` (150.0) |

### Accounts & Metrics

```
The account MyBrand was created.
The account MyBrand started with 1000 followers.   // integer init
The account MyBrand began at 4.5 engagement rate.  // float init
The account MyBrand gained 200 likes.
The account MyBrand lost 50 followers.
The account MyBrand increased by 10 views.
The account MyBrand decreased by 5 comments.
The account MyBrand was updated to 500 followers.
The account MyBrand became 300 likes.
The account MyBrand is viral.
The account MyBrand is trending.
The account MyBrand posted about "Summer Drop" that had 5000 views.
Display MyBrand likes.
Display MyBrand.
```

Metrics: `likes`, `followers`, `views`, `comments`, `shares`, `posts`,
`stories`, `engagement rate`, `reach`, `growth rate`.

### Arithmetic

```
The account A now has 100 plus 50 likes.
The account A now has 200 minus 30 followers.
The account A now has 10 times 5 views.
The account A now has 100 divided by 4 shares.
The account A now has 17 modulo 5 posts.
```

Operators: `plus` / `+`, `minus` / `-`, `times` / `*`, `divided by` / `/`,
`divided evenly by`, `modulo` / `%`, `multiplied by`, `increased by`, `decreased by`.

### Comparisons (all supported)

```
When A likes more than 1000      { … }
When A followers less than 500   { … }
When A views exceeded 50000      { … }
When A comments dropped below 10 { … }
When A shares reached 200        { … }
When A likes went viral          { … }   // > 1000 threshold
When A posts exactly 7           { … }
When A posts equal to 7          { … }
When A likes at least 500        { … }
When A likes at most 999         { … }
When A posts different from 0    { … }
When A posts not equal to 0      { … }
When A likes stayed at 500       { … }
```

### Conditionals

```
When A likes more than 500
{
    Announce "high engagement".
}
Otherwise if A likes more than 100
{
    Announce "moderate engagement".
}
Otherwise
{
    Announce "low engagement".
}
```

Logical operators: `also` (AND), `either` (OR), `opposite` (NOT).

```
When A likes more than 100 also A followers more than 50   { … }
When A likes more than 500 either A views more than 10000  { … }
When opposite A followers more than 9999                   { … }
```

### Loops (5 types)

```
// 1. Count-controlled (while-style)
Every day for 7 days,
{
    The account A gained 10 likes.
}

// 2. Incrementing step
Every 10 days incrementing by 3
{
    The account A gained 1 posts.
}

// 3. Decrementing step
Every 10 days decrementing by 3
{
    The account A gained 1 shares.
}

// 4. Range
For each follower from 1 to 5
{
    The account A gained 1 comments.
}

// 5. Until condition (while-until)
trending loop until A likes more than 1000
{
    The account A gained 50 likes.
}
```

Loop control: `Stop the story.` (break), `Skip this post.` (continue).

### Functions

```
The story of ScorePost begins with views
{
    Tell back views plus 10.
}
The story ends.

The story of Combine begins with a, b
{
    Tell back a plus b.
}
The story ends.

Tell ScorePost with 90.
Tell Combine with 30, 40.
```

### Built-in Analytics (13 total)

```
Calculate virality for The account MyBrand.
Calculate engagement for The account MyBrand.
Analyze growth for The account MyBrand.
Check if trending for The account MyBrand.
Count total engagement.
Find top post.
Find max viral account.
Reverse growth for The account MyBrand.
Find the highest reach in the feed.
Find the total reach in the feed.
Detect spam in "buy followers now".
Clamp engagement between 10 and then 90.
Reverse the caption ("Hello World").
```

### Feed / Arrays

```
The feed contains 5 posts.
The feed at index 0 now has 120 likes.
The feed at index 1 now has 5 times 40 likes.       // expression value
The account A now has the feed at index 0 likes plus the feed at index 1 likes likes.
The account A now has the feed contains posts followers.   // feed length
Display the feed at index 0 likes.
For each post in the feed { Announce "post". }
```

### Input / Output

```
Ask for myVar.             // reads one integer from stdin
Announce "Hello!".         // print string literal
Display AccountName.       // print full account stats
Display AccountName likes. // print single metric
```

---

## Compiler Phases

| Phase | Component | Description |
|---|---|---|
| 1 | Lexer (`socialstory.l`) | Tokenisation, error detection with hints |
| 2 | Parser (`socialstory_parser.y`) | Grammar, AST construction, error recovery |
| 3 | AST pretty-printer (`ast_functions.h`) | Indented tree dump with node stats |
| 4 | TAC generator (`tac_generator.h`) | Three-address code with temp/label tracking |
| 5 | Optimizer (`optimizer.h`) | 6 passes: temp constant propagation, constant folding, algebraic simplification, strength reduction, copy propagation, dead code elimination |
| 6 | Interpreter (`interpreter.h`) | Tree-walk execution with runtime safety checks |

Each compiler run produces both console output and a structured
`output_<filename>.txt` report that the test suite compares exactly.

---

## Test Suite

The final test suite is **exactly 8 tests**, one per major compiler feature group.
Run with:

```bash
make test           # requires Python 3
python3 tests/run_tests.py ./socialstory   # or directly
```

| # | Test Name | Rubric Coverage |
|---|---|---|
| 1 | `lexical_identifiers_test` | Lexer: all token types, valid/invalid identifiers, hex/octal/scientific literals, comment forms, escape sequences, `@` error with recovery |
| 2 | `syntax_error_recovery_test` | Parser: multi-point error recovery, `$` lexical cascade, partial AST after errors |
| 3 | `semantic_runtime_safety_test` | Semantics/runtime: duplicate account, undeclared symbol, float coercion, divide/modulo-by-zero, feed index type+bounds, arity mismatch |
| 4 | `execution_accounts_metrics_test` | Runtime: full account lifecycle, integer+float init, all update forms, story posting, display, two accounts |
| 5 | `controlflow_loops_test` | All 5 loop types, break, continue, `exceeded`, `opposite` NOT, complex AND/OR in trending condition |
| 6 | `functions_builtins_test` | User functions (0/1/2 params), return, arity mismatch runtime error, all 13 built-ins |
| 7 | `input_io_test` | `Ask for` stdin, variables in expressions, three-branch if/else-if/else from live input |
| 8 | `arrays_optimizer_integration_test` | Feed declaration/assignment/retrieval/iteration, out-of-bounds, TAC optimizer showcase including strength reduction + DCE (before/after reduction) |

---

## Rubric Coverage Table

| Rubric Requirement | Covered By |
|---|---|
| Lexical analysis — tokeniser | tests 1, 2, 3, 4, 5, 6, 7, 8 |
| All identifier rules documented and tested | test 1 |
| Multiple numeric literal forms | test 1 |
| Lexical error detection with message | test 1 |
| Comment forms (single + multi-line) | test 1 |
| Parser / grammar rules | tests 2, 3, 4, 5, 6, 7, 8 |
| Syntax error recovery (multiple points) | test 2 |
| AST construction and display | tests 4, 5, 6, 7, 8 |
| AST statistics | tests 4, 5, 6, 7, 8 |
| Semantic analysis — duplicate declaration | test 3 |
| Semantic analysis — undeclared symbol | test 3 |
| Type coercion / float-to-int warning | test 3 |
| Division by zero guard | test 3 |
| Modulo by zero guard | test 3 |
| Feed index type check (integer required) | test 3 |
| Function arity mismatch (semantic + runtime) | tests 3, 6 |
| Account creation, init, update, display | test 4 |
| Float metric (`began at`) | test 4 |
| Status flags (`is viral`, `is trending`) | test 4 |
| All arithmetic operators | tests 4, 5, 8 |
| All comparison operators (9 forms) | tests 5, 8 |
| If / else-if / else conditional chain | tests 5, 7 |
| AND / OR / NOT logical operators | tests 5, 7 |
| All 5 loop types | test 5 |
| Break and continue | test 5 |
| User-defined functions (0/1/2 params) | test 6 |
| Return value (Tell back) | test 6 |
| All 13 built-in analytics functions | test 6 |
| `Ask for` / stdin input | test 7 |
| Input variables in expressions | test 7 |
| Feed declaration and indexed assignment | test 8 |
| Feed indexed retrieval | test 8 |
| Feed length (`the feed contains posts`) | test 8 |
| For-each-post loop iteration | test 8 |
| Feed out-of-bounds runtime error | test 8 |
| TAC generation (original + optimized print) | tests 4, 5, 6, 7, 8 |
| TAC statistics | tests 4, 5, 6, 7, 8 |
| Optimizer — dead code elimination | test 8 |
| Optimizer — before/after reduction % | test 8 |
| Symbol table display | tests 4, 5, 6, 7, 8 |
| Symbol table statistics | tests 4, 5, 6, 7, 8 |
| Deterministic, exact-output test harness | all 8 |
| stdin file support for interactive tests | test 7 |

---

## File Structure

```
ss_final/
├── Makefile
├── README.md
├── main.c                        compiler driver
├── socialstory.l                 Flex lexer
├── socialstory_parser.y          Bison grammar + semantic actions
├── socialstory_tokens.h          shared token declarations
├── compiler.h                    top-level interface
├── ast_functions.h               AST helpers
├── symbol_table.h                symbol table
├── statistics.h                  AST/symbol stats
├── tac_generator.h               three-address code
├── optimizer.h                   6-pass optimizer
├── interpreter.h                 tree-walk interpreter
├── sample_programs/
│   ├── 01_account_baseline_report.txt
│   ├── 02_engagement_health_check.txt
│   ├── 03_30_day_growth_simulation.txt
│   ├── 04_campaign_a_b_comparison.txt
│   ├── 05_input_driven_strategy.txt
│   ├── 06_feed_weekly_post_analysis.txt
│   ├── 07_builtins_analytics_report.txt
│   └── 08_optimizer_meaningful_workload.txt
├── docs/
│   ├── ARCHITECTURE.md
│   ├── LANGUAGE_SPEC.md
│   └── file-readmes/
└── tests/
    ├── manifest.json             8-test manifest (single source of truth)
    ├── run_tests.py              test runner with timeout + exact comparison
    ├── lexical_identifiers_test.txt + .expected.txt
    ├── syntax_error_recovery_test.txt + .expected.txt
    ├── semantic_runtime_safety_test.txt + .expected.txt
    ├── execution_accounts_metrics_test.txt + .expected.txt
    ├── controlflow_loops_test.txt + .expected.txt
    ├── functions_builtins_test.txt + .expected.txt
    ├── input_io_test.txt + .stdin.txt + .expected.txt
    └── arrays_optimizer_integration_test.txt + .expected.txt
```


<!-- 
cd "/f/Compiler Design/SocialStory_final"

# 1) Toolchain check
make tools-check

# 2) Regenerate parser+lexer from source
make regen

# 3) Clean build
make clean
make build

# 4) Run strict final suite
make test

# 5) Optional manual run
make run INPUT=sample_programs/01_account_baseline_report.


dsl SM analytics

duplicate acc name symbol table

declare na kore symbol use  symbol table

float -> int e rejection  interpreter 135

error hint on syntax error y

error recovery with invalid token y 318

case-insensitive keywords but case-sensitive identifiers symbol table r

built in functions for analytics interpreter e

visible optimization %

feed array analytics with bounds checks interpreter e 124

function arity mismatch semantic + runtime error inter 1214
txt -->