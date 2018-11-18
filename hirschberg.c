/*
 * Isabel Jellen
 * Date: 11/13/18
 * hirschberg.c
 * Hirschberg recursive optimization
 * Sources: http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/DynProg/Herschberg2.html
 */

#include "hirschberg.h"

// Length of least common substring
int lcs_length(str align_seq, str ref_seq){
   int m = align_seq.length;
   int n = ref_seq.length;
   int **matrix = calloc(2, sizeof(int*));
   for(int i = 0; i < 2; i++)
      matrix[i] = calloc(n + 1, sizeof(int));

   for(int i = 0; i < m + 1; i++){
      for(int j = 0; j < n + 1; j++)
         matrix[0][j] = matrix[1][j];
      
      matrix[1][0] = 0;

      for(int j = 1; j < n + 1; j++){
         if(align_seq.ptr[i-1] == ref_seq.ptr[j-1])
            matrix[1][j] = matrix[0][j-1] + 1;
         else{
            int max = matrix[0][j];
            if (matrix[1][j-1] > max)
               max = matrix[1][j-1];
            matrix[1][j] = max;
         }
      }
   }
   return matrix[1][n]; 
}

// assume ref_seq is longer than align_seq
str lcs_string(str align_seq, str ref_seq){
   int m = align_seq.length;
   int n = ref_seq.length;
   // Base case 1: x=""
   if(m == 0){
      str retstr;
      retstr.ptr = NULL;
      retstr.length = 0;
      return retstr;
   }

   // Base case 2: x has a single character
   
   if(m == 1){
      for(int i = 0; i < n; i++){
         if(ref_seq.ptr[i] == align_seq.ptr[0]){
            str retstr;
            retstr.ptr = calloc(1, sizeof(char));
            retstr.ptr[0] = align_seq.ptr[0];
            retstr.length = 1;
            return retstr;
         }
      }
      str retstr;
      retstr.ptr = NULL;
      retstr.length = 0;
      return retstr;
   }
  
   // General Case: align_seq has 2+ characters
   int total_length = lcs_length(align_seq, ref_seq);
   str x1, x2, y1, y2;
   x1.ptr = calloc((int)(m/2), sizeof(char));
   x2.ptr = calloc((int)(m/2), sizeof(char));
   y1.ptr = calloc(n, sizeof(char)); //full size of string to be careful
   y2.ptr = calloc(n, sizeof(char));
   x1.length = m/2;
   x2.length = m - m/2; // may not be the same as m/2 because rounding
   // Divide first string in half
   memcpy(x1.ptr, align_seq.ptr, m/2);
   memcpy(x2.ptr, align_seq.ptr + m/2, m - m/2);
   // Divide second string in half
   for(int i = 0; i <= n; i++){
      memcpy(y1.ptr, ref_seq.ptr, i/2);
      memcpy(y2.ptr, ref_seq.ptr + i/2, i - i/2);
      y1.length = i/2;
      y2.length = i - i/2;
      if(lcs_length(x1, y1) + lcs_length(x2, y2) == total_length){
         break; // correct split of ref seq
      }
   }
   str str1 = lcs_string(x1, y1);
   str str2 = lcs_string(x2, y2);
   
   str sum_str;
   sum_str.ptr = calloc(total_length, sizeof(char));
   sum_str.length = total_length;
   if(str1.ptr != NULL && str2.ptr != NULL){
      memcpy(sum_str.ptr, str1.ptr, str1.length);
      memcpy(sum_str.ptr+str1.length, str2.ptr, str2.length);
      free(str1.ptr);
      free(str2.ptr);
   }
   else if(str1.ptr != NULL){
      memcpy(sum_str.ptr, str1.ptr, str1.length);
      free(str1.ptr);
   }
   else if(str2.ptr != NULL){
      memcpy(sum_str.ptr+str1.length, str2.ptr, str2.length);
      free(str2.ptr);
   }
   return sum_str;
}
