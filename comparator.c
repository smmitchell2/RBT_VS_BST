#include <stdlib.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "comparator.h"

int intComparator(void *v,void *w){
  return ((integer *) v)->value - ((integer *) w)->value;
}

int stringComparator(void *a, void *b){
  return strcmp((char*)a,(char*)b);
}

int realComparator(void *v, void *w){
  return ((real *) v)->value - ((real *) w)->value;
}
