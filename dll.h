#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

typedef struct dllnode{
  void *value;
  struct dllnode *next;
  struct dllnode *prev;
} dllnode;

typedef struct dll{
  dllnode *head;
  dllnode *tail;
  int size;
  void (*display)(FILE *,void *);
} dll;

extern dllnode *newDLLNode(void *v);
extern dll *newDLL(void (*d)(FILE *,void *));            //constructor
extern void insertDLL(dll *items,int index,void *value); //stores a generic value
extern void *removeDLL(dll *items,int index);            //returns a generic value
extern void unionDLL(dll *recipient,dll *donor);
extern void *getDLL(dll *items,int index);
extern int sizeDLL(dll *items);
extern void displayDLL(FILE *fp,dll *items);

#endif
