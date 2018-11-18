/*
 * Isabel Jellen
 * Date: 11/13/18
 * File: hirschberg_runner.c
 * Runner for Hirschberg C
 */

#include "hirschberg.h"
#include "needleman_wunsch.h"

int main(int argc, char* argv[]){
   if(argc < 3)
      return 1;
   str x, y;
   x.ptr = argv[1];
   y.ptr = argv[2];
   x.length = strlen(argv[1]);
   y.length = strlen(argv[2]);
   str lcs=lcs_string(x, y);
   printf("Length of LCS: %d\n",lcs.length);
   for(int i = 0; i < lcs.length; i++){
      printf("%c", lcs.ptr[i]);
   }
   printf("\n");
}
