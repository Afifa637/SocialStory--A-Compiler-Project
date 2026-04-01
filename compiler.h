#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>

int compiler_run(const char* input_filename,
                 const char* output_filename,
                 FILE* input_file,
                 FILE* out_file);


extern int   error_count;
extern int   semantic_errors;
extern int   temp_counter;
extern int   label_counter;
extern FILE* output_file;
extern FILE* yyin;

#endif 
