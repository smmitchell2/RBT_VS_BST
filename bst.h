#include <stdio.h>
#include <stdlib.h>

#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

typedef struct bstNode {
    struct bstNode *left;
    struct bstNode *right;
    struct bstNode *parent;
    void *value;
} bstNode;

typedef struct bst {
    bstNode *root;
    int size;
    void (*display)(FILE *,void *);
    int (*compare)(void *,void *);
} bst;

extern bst *newBST(void (*)(FILE *,void *),int (*)(void *,void *));
extern bstNode *insertBST(bst *,void *);
extern int findBST(bst *,void *);
extern bstNode *findBSTNode(bst *,void *);
extern bstNode *swapToLeafBSTNode(bstNode *);
extern void pruneBSTNode(bst *,bstNode *);
extern int sizeBST(bst *);
extern void statisticsBST(bst *,FILE *);
extern void displayBST(FILE *,bst *);
#endif