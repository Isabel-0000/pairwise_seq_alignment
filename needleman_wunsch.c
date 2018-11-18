/*
 * Author: Isabel Jellen
 * Date: 11/1/2018
 * Title: needleman_wunsch.c
 * C implementation of the Needleman-Wunch algorithm
 */

#include "needleman_wunsch.h"

// Initialize and return scoring matrix with zeros given length of two sequences
int** initialize_matrix(int ref_seq_length, int align_seq_length){
   int **scoring_matrix = calloc(align_seq_length, sizeof(int*));
   for(int i =  0; i < align_seq_length; i++){
      scoring_matrix[i] = calloc(ref_seq_length, sizeof(int*));
      scoring_matrix[i][0] = 0;
   }

   for(int i = 0; i < ref_seq_length; i++){
      scoring_matrix[0][i] = 0;
   }
   return scoring_matrix;
}

// Fill matrix given two sequences
void matrix_fill(int** scoring_matrix, const char *ref_seq, const char*align_seq){
   for(int i = 1; i < strlen(align_seq) + 1; i++){
      for(int j = 1; j < strlen(ref_seq) + 1; j++){
         int diag_score = 0;
         if(ref_seq[j-1] == align_seq[i-1]){
            diag_score = scoring_matrix[i-1][j-1] + 2;
         }
         else{
            diag_score = scoring_matrix[i-1][j-1] - 1;
         }
         int left_score = scoring_matrix[i][j-1] - 2;
         int score_up = scoring_matrix[i-1][j] - 2;
         int max_score = 0;
         if(left_score > score_up)
            max_score = left_score;
         else
            max_score = score_up;
         if(max_score < diag_score)
            max_score = diag_score;

         scoring_matrix[i][j] = max_score;
      }
   }
}

// Determine and return pair of alignments resulting in max score
alignments traceback(int**scoring_matrix, const char *ref_seq, const char *align_seq){
   int m = strlen(align_seq);
   int n = strlen(ref_seq);
   char *alignment_a = calloc(m+n+1,sizeof(char));
   char *alignment_b = calloc(m+n+1, sizeof(char));

   while(m > 0 && n > 0){
      int diag_score = 0;
      if(align_seq[m-1] == ref_seq[n-1])
         diag_score = 2;
      else
         diag_score = -1;
      char ref = (char)(ref_seq[n-1]);
      char align = (char)(align_seq[m-1]);
      char space = '-';
      if(m > 0 && n > 0 && scoring_matrix[m][n] == scoring_matrix[m-1][n-1] + diag_score){
         append(ref, alignment_a, align, alignment_b);
         m--;
         n--;
      }
      else if(n > 0 && scoring_matrix[m][n] == scoring_matrix[m][n-1] - 2){
         append(ref, alignment_a, space, alignment_b);
         n--;
      }
      else if(m > 0){
         append(space, alignment_a, align, alignment_b);
         m--;
      }
   }
   alignments align;
   align.align_a = alignment_a;
   align.align_b = alignment_b;
   return align;

}

void append(char ref, char* a, char align, char* b){
   sprintf(a,"%c%s",ref,a);
   sprintf(b,"%c%s",align,b);
}
