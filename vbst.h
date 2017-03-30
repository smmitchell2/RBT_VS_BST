#include <stdio.h>
#include "bst.h"

#ifndef __VBST_INCLUDED__
#define __VBST_INCLUDED__

typedef struct vbst{
	bst *tree;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
    int size;
    int words;
} vbst;

vbst *newVBST(void (*display)(FILE *, void *), int(*comparator)(void *, void *));
void insertVBST(vbst *v, void *value);
int findVBST(vbst *v, void *value);
void deleteVBST(vbst *v, void *value);
int sizeVBST(vbst *v);
void statisticsVBST(vbst *v, FILE *fp);
void displayVBST(FILE *fp, vbst *v);

#endif