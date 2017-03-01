#include <stdlib.h>
#include <stdio.h>
#include "dll.h"
#include "stack.h"

//lifo
stack *newStack(void (*d)(FILE *,void *)){
  stack *s = malloc(sizeof(stack));
  s->list = newDLL(d);
  return s;
}

void push(stack *items,void *value){
  insertDLL(items->list,0,value);
}

void *pop(stack *items){
  void *r = removeDLL(items->list,0);
  return r;
}

void *peekStack(stack *items){
  return items->list->head->value;
}

int sizeStack(stack *items){
  return items->list->size;
}

void displayStack(FILE *fp,stack *items){
  dllnode *temp = items->list->head;
  fprintf(fp, "[" );
  while(temp != NULL){
    items->list->display(fp,temp->value);
    if(temp->next != NULL){fprintf(fp,",");}
    temp = temp->next;
  }
  fprintf(fp, "]");
}
