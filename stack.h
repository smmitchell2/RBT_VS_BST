#include "dll.h"
#ifndef __Stack_INCLUDED__
#define __Stack_INCLUDED__

typedef struct Stack{
  dll *list;
}stack;

stack *newStack(void (*d)(FILE *d,void *));   //constructor
void push(stack *items,void *value);         //stores a generic value
void *pop(stack *items);                     //returns a generic value
void *peekStack(stack *items);               //returns a generic value
int sizeStack(stack *items);
void displayStack(FILE *fp,stack *items);

#endif
