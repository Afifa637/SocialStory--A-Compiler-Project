/* ============================================================
 * main.c  —  SocialStoryScript Compiler Driver
 *
 * This is the ONLY file that contains main().
 * All compiler logic lives in:
 *   socialstory.l           Lexer  (Flex)
 *   socialstory_parser.y    Grammar + AST (Bison)
 *   interpreter.h           Runtime execution engine
 *   tac_generator.h         Three-Address Code
 *   optimizer.h             Optimization passes
 *   symbol_table.h          Symbol table
 *   ast_functions.h         AST helpers
 *   statistics.h            Reporting
 *
 * Build (after flex + bison):
 *   gcc -o socialstory socialstory_parser.tab.c lex.yy.c main.c -lm
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

/* Cleanup functions from the compiler headers */
extern void free_ast(void *root);
extern void free_symbol_table(void);
extern void free_tac(void);
extern void *ast_root;

/* ---- Banner ---- */
static void print_banner(const char *infile, const char *outfile)
{
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║   🚀  SocialStoryScript Compiler  — v1.0            ║\n");
    printf("║   Pipeline: Lex → Parse → AST → TAC → Opt → Run    ║\n");
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  Input  : %-42s ║\n", infile);
    printf("║  Output : %-42s ║\n", outfile);
    printf("╚══════════════════════════════════════════════════════╝\n\n");
}

/* ---- Result box ---- */
static void print_result(int success, const char *outfile)
{
    if (success)
    {
        printf("\n╔══════════════════════════════════════════════╗\n");
        printf("║   ✅  COMPILATION + EXECUTION SUCCESSFUL      ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  Lexical errors  : %-25d ║\n", error_count);
        printf("║  Syntax errors   : 0                         ║\n");
        printf("║  Semantic errors : %-25d ║\n", semantic_errors);
        printf("║  TAC temps       : %-25d ║\n", temp_counter);
        printf("║  TAC labels      : %-25d ║\n", label_counter);
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  Report: %-35s ║\n", outfile);
        printf("╚══════════════════════════════════════════════╝\n\n");
    }
    else
    {
        printf("\n╔══════════════════════════════════════════════╗\n");
        printf("║   ❌  EXECUTION REPORTED ERRORS               ║\n");
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  Lexical errors  : %-25d ║\n", error_count);
        printf("║  Semantic errors : %-25d ║\n", semantic_errors);
        printf("╠══════════════════════════════════════════════╣\n");
        printf("║  Fix diagnostics and run again.              ║\n");
        printf("╚══════════════════════════════════════════════╝\n\n");
    }
}

/* ============================================================
 * main()
 * ============================================================ */
int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "\n❌  Usage: %s <input_file>\n", argv[0]);
        fprintf(stderr, "    Example: %s my_program.txt\n\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        fprintf(stderr, "\n❌  Cannot open: '%s'\n\n", argv[1]);
        return 1;
    }

    char output_filename[512];
    const char *base = argv[1];
    for (const char *p = argv[1]; *p; p++)
    {
        if (*p == '/' || *p == '\\')
            base = p + 1;
    }
    snprintf(output_filename, sizeof(output_filename), "output_%s", base);

    FILE *out = fopen(output_filename, "w");
    if (!out)
    {
        fprintf(stderr, "\n❌  Cannot create output file: '%s'\n\n", output_filename);
        fclose(input);
        return 1;
    }

    print_banner(argv[1], output_filename);

    int result = compiler_run(argv[1], output_filename, input, out);

    print_result(result == 0, output_filename);

    free_ast(ast_root);
    free_symbol_table();
    free_tac();
    fclose(input);
    fclose(out);

    return result;
}
