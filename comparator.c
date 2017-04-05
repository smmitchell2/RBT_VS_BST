#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comparator.h"

int stringComparator(void *a, void *b){
  return strcmp((char*)a,(char*)b);
}

