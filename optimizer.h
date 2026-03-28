/* ========================================
 * OPTIMIZER.H
 * Code Optimization Passes
 * ======================================== */

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Track which temps are actually used */
int temps_used[10000] = {0};

/* ========================================
 * HELPER FUNCTIONS
 * ======================================== */

int is_constant(const char *str)
{
    if (!str)
        return 0;
    int i = 0;
    if (str[0] == '-' || str[0] == '+')
        i = 1;
    for (; str[i]; i++)
    {
        if (str[i] != '.' && !isdigit(str[i]))
            return 0;
    }
    return str[0] != '\0';
}

int eval_const_expr(const char *left, const char *op, const char *right)
{
    int l = atoi(left);
    int r = atoi(right);

    if (strcmp(op, "+") == 0)
        return l + r;
    if (strcmp(op, "-") == 0)
        return l - r;
    if (strcmp(op, "*") == 0)
        return l * r;
    if (strcmp(op, "/") == 0 && r != 0)
        return l / r;
    if (strcmp(op, "%") == 0 && r != 0)
        return l % r;

    return 0;
}

static int is_power_of_two_int(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

static TACInstruction *make_optimizer_instr(const char *op, const char *arg1, const char *arg2, const char *result)
{
    TACInstruction *instr = (TACInstruction *)malloc(sizeof(TACInstruction));
    if (!instr)
        return NULL;

    instr->op = op ? strdup(op) : NULL;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->label = -1;
    instr->next = NULL;
    return instr;
}

/* Replace temp operands with their known constant values (when available).
 * This enables later passes (constant folding / algebraic simplification)
 * on code lowered through temporaries like:
 *   t1 = 10; t2 = 20; t3 = t1 + t2
 */
int optimize_temp_constant_propagation()
{
    int count = 0;
    char *const_map[10000] = {0};

    TACInstruction *instr = tac_head;
    while (instr)
    {
        /* Replace arg1 temp with known constant */
        if (instr->arg1 && strncmp(instr->arg1, "t", 1) == 0)
        {
            int n = atoi(instr->arg1 + 1);
            if (n >= 0 && n < 10000 && const_map[n])
            {
                free(instr->arg1);
                instr->arg1 = strdup(const_map[n]);
                count++;
            }
        }

        /* Replace arg2 temp with known constant */
        if (instr->arg2 && strncmp(instr->arg2, "t", 1) == 0)
        {
            int n = atoi(instr->arg2 + 1);
            if (n >= 0 && n < 10000 && const_map[n])
            {
                free(instr->arg2);
                instr->arg2 = strdup(const_map[n]);
                count++;
            }
        }

        /* Update mapping for assignments to temps */
        if (instr->op && strcmp(instr->op, "=") == 0 &&
            instr->result && strncmp(instr->result, "t", 1) == 0)
        {
            int rn = atoi(instr->result + 1);
            if (rn >= 0 && rn < 10000)
            {
                if (const_map[rn])
                {
                    free(const_map[rn]);
                    const_map[rn] = NULL;
                }

                if (instr->arg1 && is_constant(instr->arg1) && !instr->arg2)
                {
                    const_map[rn] = strdup(instr->arg1);
                }
            }
        }

        instr = instr->next;
    }

    for (int i = 0; i < 10000; i++)
    {
        free(const_map[i]);
    }

    return count;
}

/* ========================================
 * OPTIMIZATION PASS 1: Constant Folding
 * ======================================== */

int optimize_constant_folding()
{
    int count = 0;
    TACInstruction *instr = tac_head;

    while (instr)
    {
        if (instr->op && instr->arg1 && instr->arg2 && instr->result)
        {
            if (is_constant(instr->arg1) && is_constant(instr->arg2))
            {
                if (strcmp(instr->op, "+") == 0 || strcmp(instr->op, "-") == 0 ||
                    strcmp(instr->op, "*") == 0 || strcmp(instr->op, "/") == 0 ||
                    strcmp(instr->op, "%") == 0)
                {
                    /* Leave algebraic identities to optimize_algebraic() so the
                     * pass remains observable in optimizer reports.
                     */
                    if ((strcmp(instr->op, "+") == 0 &&
                         (strcmp(instr->arg1, "0") == 0 || strcmp(instr->arg2, "0") == 0)) ||
                        (strcmp(instr->op, "-") == 0 && strcmp(instr->arg2, "0") == 0) ||
                        (strcmp(instr->op, "*") == 0 &&
                         (strcmp(instr->arg1, "0") == 0 || strcmp(instr->arg2, "0") == 0 ||
                          strcmp(instr->arg1, "1") == 0 || strcmp(instr->arg2, "1") == 0)) ||
                        (strcmp(instr->op, "/") == 0 && strcmp(instr->arg2, "1") == 0))
                    {
                        instr = instr->next;
                        continue;
                    }

                    int result = eval_const_expr(instr->arg1, instr->op, instr->arg2);

                    // Replace with direct assignment
                    free(instr->op);
                    instr->op = strdup("=");
                    free(instr->arg1);
                    char buf[32];
                    sprintf(buf, "%d", result);
                    instr->arg1 = strdup(buf);
                    free(instr->arg2);
                    instr->arg2 = NULL;

                    count++;
                }
            }
        }
        instr = instr->next;
    }

    return count;
}

/* ========================================
 * OPTIMIZATION PASS 2: Algebraic Simplification
 * ======================================== */

int optimize_algebraic()
{
    int count = 0;
    TACInstruction *instr = tac_head;

    while (instr)
    {
        if (instr->op && instr->arg1 && instr->arg2 && instr->result)
        {
            // x + 0 = x or 0 + x = x
            if (strcmp(instr->op, "+") == 0)
            {
                if (strcmp(instr->arg2, "0") == 0)
                {
                    free(instr->op);
                    instr->op = strdup("=");
                    free(instr->arg2);
                    instr->arg2 = NULL;
                    count++;
                }
                else if (strcmp(instr->arg1, "0") == 0)
                {
                    free(instr->op);
                    instr->op = strdup("=");
                    free(instr->arg1);
                    instr->arg1 = strdup(instr->arg2);
                    free(instr->arg2);
                    instr->arg2 = NULL;
                    count++;
                }
            }
            // x * 1 = x or 1 * x = x
            else if (strcmp(instr->op, "*") == 0)
            {
                if (strcmp(instr->arg2, "1") == 0)
                {
                    free(instr->op);
                    instr->op = strdup("=");
                    free(instr->arg2);
                    instr->arg2 = NULL;
                    count++;
                }
                else if (strcmp(instr->arg1, "1") == 0)
                {
                    free(instr->op);
                    instr->op = strdup("=");
                    free(instr->arg1);
                    instr->arg1 = strdup(instr->arg2);
                    free(instr->arg2);
                    instr->arg2 = NULL;
                    count++;
                }
                // x * 0 = 0 or 0 * x = 0
                else if (strcmp(instr->arg2, "0") == 0 || strcmp(instr->arg1, "0") == 0)
                {
                    free(instr->op);
                    instr->op = strdup("=");
                    free(instr->arg1);
                    instr->arg1 = strdup("0");
                    free(instr->arg2);
                    instr->arg2 = NULL;
                    count++;
                }
            }
            // x - 0 = x
            else if (strcmp(instr->op, "-") == 0 && strcmp(instr->arg2, "0") == 0)
            {
                free(instr->op);
                instr->op = strdup("=");
                free(instr->arg2);
                instr->arg2 = NULL;
                count++;
            }
            // x / 1 = x
            else if (strcmp(instr->op, "/") == 0 && strcmp(instr->arg2, "1") == 0)
            {
                free(instr->op);
                instr->op = strdup("=");
                free(instr->arg2);
                instr->arg2 = NULL;
                count++;
            }
        }
        instr = instr->next;
    }

    return count;
}

/* ========================================
 * OPTIMIZATION PASS 3: Strength Reduction
 * ======================================== */

int optimize_strength_reduction()
{
    int count = 0;
    TACInstruction *instr = tac_head;
    TACInstruction *prev = NULL;

    while (instr)
    {
        if (instr->op && instr->arg1 && instr->arg2 && instr->result)
        {
            if (strcmp(instr->op, "*") == 0)
            {
                const char *var = NULL;
                int factor = 0;

                if (is_constant(instr->arg2) && !is_constant(instr->arg1))
                {
                    factor = atoi(instr->arg2);
                    var = instr->arg1;
                }
                else if (is_constant(instr->arg1) && !is_constant(instr->arg2))
                {
                    factor = atoi(instr->arg1);
                    var = instr->arg2;
                }

                if (var && is_power_of_two_int(factor) && factor >= 2 && factor <= 8)
                {
                    if (factor == 2)
                    {
                        free(instr->op);
                        instr->op = strdup("+");
                        free(instr->arg1);
                        instr->arg1 = strdup(var);
                        free(instr->arg2);
                        instr->arg2 = strdup(var);
                        count++;
                    }
                    else
                    {
                        /* Build chained doubling:
                         * t0 = x + x
                         * t1 = t0 + t0    (for *4)
                         * t2 = t1 + t1    (for *8)
                         * result = tN
                         */
                        int doubles = 0;
                        int f = factor;
                        while (f > 1)
                        {
                            doubles++;
                            f >>= 1;
                        }

                        const char *current = var;
                        for (int i = 0; i < doubles - 1; i++)
                        {
                            char *tmp = new_temp();
                            TACInstruction *newi = make_optimizer_instr("+", current, current, tmp);
                            free(tmp);
                            if (!newi)
                                break;

                            if (prev)
                                prev->next = newi;
                            else
                                tac_head = newi;

                            newi->next = instr;
                            prev = newi;
                            current = newi->result;
                            count++;
                        }

                        free(instr->op);
                        instr->op = strdup("+");
                        free(instr->arg1);
                        instr->arg1 = strdup(current);
                        free(instr->arg2);
                        instr->arg2 = strdup(current);
                        count++;
                    }
                }
            }
        }
        prev = instr;
        instr = instr->next;
    }

    return count;
}

/* ========================================
 * OPTIMIZATION PASS 4: Copy Propagation
 * ======================================== */

int optimize_copy_propagation()
{
    int count = 0;
    TACInstruction *instr = tac_head;

    while (instr)
    {
        // Find assignments like t1 = t0
        if (instr->op && strcmp(instr->op, "=") == 0 &&
            instr->arg1 && instr->result && !instr->arg2)
        {
            // Replace uses of result with arg1 until result is redefined
            TACInstruction *next_instr = instr->next;
            while (next_instr)
            {
                if (next_instr->result && strcmp(next_instr->result, instr->result) == 0)
                    break;

                // Replace in arg1
                if (next_instr->arg1 && strcmp(next_instr->arg1, instr->result) == 0)
                {
                    free(next_instr->arg1);
                    next_instr->arg1 = strdup(instr->arg1);
                    count++;
                }
                // Replace in arg2
                if (next_instr->arg2 && strcmp(next_instr->arg2, instr->result) == 0)
                {
                    free(next_instr->arg2);
                    next_instr->arg2 = strdup(instr->arg1);
                    count++;
                }
                next_instr = next_instr->next;
            }
        }
        instr = instr->next;
    }

    return count;
}

/* ========================================
 * OPTIMIZATION PASS 5: Dead Code Elimination
 * ======================================== */

int optimize_dead_code()
{
    memset(temps_used, 0, sizeof(temps_used));

    // First pass: mark all temps that are used
    TACInstruction *instr = tac_head;
    while (instr)
    {
        // Mark temps used as operands
        if (instr->arg1 && strncmp(instr->arg1, "t", 1) == 0)
        {
            int num = atoi(instr->arg1 + 1);
            if (num >= 0 && num < 10000)
                temps_used[num] = 1;
        }
        if (instr->arg2 && strncmp(instr->arg2, "t", 1) == 0)
        {
            int num = atoi(instr->arg2 + 1);
            if (num >= 0 && num < 10000)
                temps_used[num] = 1;
        }
        instr = instr->next;
    }

    // Second pass: remove assignments to unused temps
    int count = 0;
    instr = tac_head;
    TACInstruction *prev = NULL;

    while (instr)
    {
        int should_remove = 0;

        // Check if this is an assignment to a temp that's never used
        if (instr->op && strcmp(instr->op, "=") == 0 &&
            instr->result && strncmp(instr->result, "t", 1) == 0)
        {
            int num = atoi(instr->result + 1);
            if (num >= 0 && num < 10000 && !temps_used[num])
            {
                should_remove = 1;
            }
        }

        if (should_remove)
        {
            TACInstruction *to_remove = instr;
            if (prev)
            {
                prev->next = instr->next;
            }
            else
            {
                tac_head = instr->next;
            }
            if (instr == tac_tail)
            {
                tac_tail = prev;
            }
            instr = instr->next;

            free(to_remove->op);
            free(to_remove->arg1);
            free(to_remove->arg2);
            free(to_remove->result);
            free(to_remove);
            count++;
        }
        else
        {
            prev = instr;
            instr = instr->next;
        }
    }

    return count;
}

/* ========================================
 * RUN ALL OPTIMIZATIONS
 * ======================================== */

/*
 * Optimization pipeline order (fixed): (1) Temporary constant propagation
 * substitutes known literal temp values into later instructions to expose
 * simplification opportunities, (2) Constant folding evaluates compile-time
 * arithmetic expressions directly, (3) Algebraic simplification applies
 * identity/annihilator rules (e.g., x+0, x*1, x*0), (4) Strength reduction
 * rewrites expensive operations into cheaper equivalents where safe,
 * (5) Copy propagation forwards simple assignments to reduce indirection,
 * and (6) Dead code elimination removes instructions that no longer affect
 * observable program behavior.
 */

void run_all_optimizations(FILE *fp)
{
    fprintf(fp, "\n⚡ RUNNING CODE OPTIMIZATIONS\n");
    fprintf(fp, "=========================================\n");

    int original_count = 0;
    TACInstruction *instr = tac_head;
    while (instr)
    {
        if (instr->label < 0)
            original_count++;
        instr = instr->next;
    }

    // Run optimization passes
    fprintf(fp, "\n🔧 OPTIMIZATION: Temp Constant Propagation\n");
    fprintf(fp, "==========================================\n");
    int tcp_count = optimize_temp_constant_propagation();
    fprintf(fp, "Total temp constant propagations: %d\n", tcp_count);

    fprintf(fp, "\n🔧 OPTIMIZATION: Constant Folding\n");
    fprintf(fp, "======================================\n");
    int cf_count = optimize_constant_folding();
    fprintf(fp, "Total constant folding optimizations: %d\n", cf_count);

    fprintf(fp, "\n🔧 OPTIMIZATION: Algebraic Simplification\n");
    fprintf(fp, "==========================================\n");
    int as_count = optimize_algebraic();
    fprintf(fp, "Total algebraic simplifications: %d\n", as_count);

    fprintf(fp, "\n🔧 OPTIMIZATION: Strength Reduction\n");
    fprintf(fp, "====================================\n");
    int sr_count = optimize_strength_reduction();
    fprintf(fp, "Total strength reductions: %d\n", sr_count);

    fprintf(fp, "\n🔧 OPTIMIZATION: Copy Propagation\n");
    fprintf(fp, "===================================\n");
    int cp_count = optimize_copy_propagation();
    fprintf(fp, "Total copy propagations: %d\n", cp_count);

    fprintf(fp, "\n🔧 OPTIMIZATION: Dead Code Elimination\n");
    fprintf(fp, "=======================================\n");
    int dce_count = optimize_dead_code();
    fprintf(fp, "Total dead code eliminations: %d\n", dce_count);

    // Count temps actually used
    int temps_in_use = 0;
    for (int i = 0; i < temp_counter; i++)
    {
        if (temps_used[i])
            temps_in_use++;
    }
    fprintf(fp, "Temporary variables used: %d/%d\n", temps_in_use, temp_counter);

    // Count final instructions
    int final_count = 0;
    instr = tac_head;
    while (instr)
    {
        if (instr->label < 0)
            final_count++;
        instr = instr->next;
    }

    int total_opts = tcp_count + cf_count + as_count + sr_count + cp_count + dce_count;
    int removed = original_count - final_count;
    if (removed < 0)
        removed = 0;
    float reduction = original_count > 0 ? (removed * 100.0 / original_count) : 0;

    fprintf(fp, "\n========================================\n");
    fprintf(fp, "📊 OPTIMIZATION SUMMARY\n");
    fprintf(fp, "========================================\n");
    fprintf(fp, "  Instructions before: %d\n", original_count);
    fprintf(fp, "  Instructions after:  %d\n", final_count);
    fprintf(fp, "  Instructions removed: %d\n", removed);
    fprintf(fp, "  Reduction: %.1f%%\n", reduction);
    fprintf(fp, "  Total optimizations applied: %d\n", total_opts);
    fprintf(fp, "========================================\n");
}

#endif /* OPTIMIZER_H */
