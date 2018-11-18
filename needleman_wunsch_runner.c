/*
 * Isabel Jellen
 * Date: 11/13/18
 * File: needleman_wunsch_runner.c
 * Runner for needleman wunsch
 */

#include "needleman_wunsch.h"

int main(int argc, char*argv[]){
   if(argc < 3)
      return 1;
   const char *ref_seq = argv[1];
   const char *align_seq = argv[2];
   int ** scoring_matrix = initialize_matrix(strlen(ref_seq) + 1, strlen(align_seq) + 1);
   matrix_fill(scoring_matrix, ref_seq, align_seq);
   alignments align = traceback(scoring_matrix, ref_seq, align_seq);
   printf("%s\n", align.align_a+1);
   printf("%s\n", align.align_b+1);

   // Cleanup
   for(int i = 0; i<strlen(align_seq); i++)
      free(scoring_matrix[i]);
   free(scoring_matrix);
   return 0;
}

