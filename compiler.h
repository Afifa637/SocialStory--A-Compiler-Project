/* ============================================================
 * compiler.h
 * Shared declarations between main.c and the parser.
 * Declares the compiler_run() entry point called by main().
 * ============================================================ */

#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>

/* Called by main() — implemented in socialstory_parser.tab.c */
int compiler_run(const char* input_filename,
                 const char* output_filename,
                 FILE* input_file,
                 FILE* out_file);

/* Globals exposed by the Bison/Flex generated code */
extern int   error_count;
extern int   semantic_errors;
extern int   temp_counter;
extern int   label_counter;
extern FILE* output_file;
extern FILE* yyin;

#endif /* COMPILER_H */
