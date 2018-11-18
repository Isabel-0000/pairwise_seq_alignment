#ifndef HIRSCHBERG_H
#define HIRSCHBERG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   char *ptr;
   int length;
}str;

int lcs_length(str align_seq, str ref_seq);
str lcs_string(str align_seq, str ref_seq);
#endif
