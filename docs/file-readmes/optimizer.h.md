# optimizer.h

## Purpose
Implements 6 optimisation passes on the TAC linked list. Passes are run in order. The list is modified in place. Before and after instruction counts are measured and the real reduction percentage is printed.

## Pass 1: Temp Constant Propagation (`optimize_temp_constant_propagation`)
**Trigger:** A temp is assigned from a constant (`t1 = 10`), then used by later instructions.
**Action:** Rewrites later `arg1`/`arg2` temp uses to literal constants where safe.
**Example:** `t1 = 10`, `t2 = t1 + 5` → `t2 = 10 + 5`

## Pass 2: Constant Folding (`optimize_constant_folding`)
**Trigger:** `instr->arg1` and `instr->arg2` are both numeric literal strings.
**Action:** Evaluates the expression at compile time, replaces with `result = computed_value`.
**Example:** `t2 = 5 + 3` → `t2 = 8`

## Pass 3: Algebraic Simplification (`optimize_algebraic`)
**Trigger:** One operand is a specific constant (`0`, `1`).
**Rules:** `x + 0` → `x`, `x * 1` → `x`, `x * 0` → `0`, `x - 0` → `x`, `x / 1` → `x`
**Example:** `t2 = t0 + 0` → `t2 = t0`

## Pass 4: Strength Reduction (`optimize_strength_reduction`)
**Trigger:** `op == "*"` and one operand is a power-of-two constant (`2`, `4`, `8`) while the other operand is non-constant.
**Action:** Rewrites multiplication into doubling chains using addition.
**Examples:**
- `t = x * 2` → `t = x + x`
- `t = x * 4` → `t0 = x + x; t = t0 + t0`
- `t = x * 8` → `t0 = x + x; t1 = t0 + t0; t = t1 + t1`

## Pass 5: Copy Propagation (`optimize_copy_propagation`)
**Trigger:** `dst = src` copy assignment.
**Action:** Replaces downstream uses of `dst` with `src` until `dst` is redefined.

## Pass 6: Dead Code Elimination (`optimize_dead_code`)
**Algorithm:**
1. First pass: mark every temp that appears as `arg1` or `arg2` in any instruction.
2. Second pass: remove any `result = value` where `result` is unmarked.

**Key insight for feed arrays:** Index temps (e.g., `t0 = 0`) are embedded in feed instruction strings (`feed[t0].likes = ...`). The DCE pass scans only standalone `arg1`/`arg2` fields, so these embedded index temps are never marked as "used" and are eliminated.

## Reporting
```
Instructions before: 48
Instructions after:  41
Instructions removed: 7
Reduction: 14.6%
```
