

#ifndef NEEDLEMAN_WUNSCH
#define NEEDLEMAN_WUNSCH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
   char*align_a;
   char*align_b;
}alignments;

int** initialize_matrix(int ref_seq_length, int align_seq_length);
void matrix_fill(int** scoring_matrix, const char*ref_seq, const char*align_seq);
alignments traceback(int**scoring_matrix, const char*ref_seq, const char*align_seq);
void append(char ref, char* a, char align, char* b);

#endif
