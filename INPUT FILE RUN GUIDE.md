# INPUT FILE RUN GUIDE

## What sir should run (single showcase)

Use this input file:
- `INPUT.showcase_all_features.txt`

Quick command:

```bash
make showcase
```

This will:
- run `INPUT.showcase_all_features.txt`
- auto-feed stdin values from `INPUT.showcase_runtime_values.txt`
- write full report to: `OUTPUT.showcase_all_feature.txt`

For evaluation, this single command is enough.
No need to run `make test` unless required.

---

## Manual run (without Makefile)

If already built:

```bash
./socialstory.exe INPUT.showcase_all_features.txt
```

Then enter two values when prompted (example):
- `12`
- `100`

Why these values are needed:
- the input file has `Ask for input_likes.` and `Ask for input_followers.`
- in `make showcase`, these values are read from `INPUT.showcase_runtime_values.txt`
- in manual run, you type them interactively when prompted

Runtime input values file used by `make showcase`:
- `INPUT.showcase_runtime_values.txt`

Current file content (line-by-line stdin):
- line 1 → `12`
- line 2 → `100`

---

## Full manual pipeline (lexer + parser + compile + run)

```bash
bison -Wno-conflicts-sr -d -o socialstory_parser.tab.c socialstory_parser.y
flex -o lex.yy.c socialstory.l
gcc -std=c11 -Wall -Wextra -Werror -O2 -Wno-unused-function -Wno-unused-parameter -o socialstory.exe main.c socialstory_parser.tab.c lex.yy.c -lm
socialstory.exe INPUT.showcase_all_features.txt
```

---

## What sir should expect to see in the report (full checklist)

Open this file after run:
- `OUTPUT.showcase_all_feature.txt`

Expected order/sections in report:

1. Header block
	- compiler report title
	- input file name shown

2. Intentional syntax-error recovery demo
	- multiple syntax errors with recovery lines
	- hint lines for operator/comma/statement syntax

3. Parse confirmation
	- `✅ Parse successful! AST built.`

4. Showcase note
	- line stating syntax errors are intentional

5. Execution log
	- announcement/account/feed operations
	- `Ask for` values shown from runtime input file
	- functions (`Ping`, `AddFive`, `Mix`) calls + returns
	- loops/conditionals/built-ins execution traces
	- final account display output

6. Execution completion summary
	- expected non-zero runtime/semantic error summary for showcase

7. Abstract Syntax Tree section
	- `🌲 ABSTRACT SYNTAX TREE`
	- detailed node tree

8. AST statistics
	- total nodes
	- maximum depth
	- average branching factor

9. Symbol Table section
	- account/function/variable entries

10. Symbol Table statistics
	 - total symbols/accounts/functions/variables

11. Three-Address Code section
	 - `💻 ORIGINAL TAC`
	 - TAC instruction/stat blocks

12. Optimization section
	 - all optimization passes listed:
		- temp constant propagation
		- constant folding
		- algebraic simplification
		- strength reduction
		- copy propagation
		- dead code elimination
	 - optimization summary (before/after/reduction/total applied)

13. Optimized TAC section
	 - `💻 OPTIMIZED TAC`
	 - optimized TAC statistics

14. Final compilation/execution counters (bottom)
	 - lexical errors
	 - syntax errors
	 - semantic errors
	 - TAC temporaries
	 - TAC labels

If all 14 are present, the showcase report is complete and nothing important is missed near the bottom.

---

## Notes for evaluator

- Showcase intentionally includes a small syntax-error section.
- Those errors are intentional to demonstrate parser hints, recovery, and continued execution.
- This is why terminal summary may show non-zero semantic/error count, while full AST/TAC/optimization/execution output still appears in report file.

## About expected test files

- Keep all `*.expected.txt` files.
- They are part of the project’s regression-proof test evidence.
- Removing them can make `make test` fail or look incomplete.

Report file to open after run:
- `OUTPUT.showcase_all_feature.txt`
