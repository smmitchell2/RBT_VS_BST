#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "bst.h"

bstNode *newBSTNode(void *data){
    bstNode *n = malloc(sizeof(bstNode));
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->value = data;
    return n;
}

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *)){
    bst *tree = malloc(sizeof(bst));
    tree->root = NULL;
    tree->size = 0;
    tree->display = d;
    tree->compare = c;
    return tree;

}

bstNode *insertBST(bst *tree, void *data){
    bstNode *n = newBSTNode(data);
    if(tree->root == NULL) {tree->root = n;}
    else if((tree->compare(tree->root->value,data)) < 0){ }
    else if((tree->compare(tree->root->value,data)) > 0){ }
    else if((tree->compare(tree->root->value,data)) == 0){ }
    return n;

}

int findBST(bst *tree, void *data){

}

bstNode *findBSTNode(bst *tree, void *data){

}

bstNode *swapToLeafBSTNode(bstNode *n){

}

void pruneBSTNode(bst *tree,bstNode *n){

}

int sizeBST(bst *tree){
    return tree->size;
}

void statisticsBST(bst *tree,FILE *FP){

}

void displayBST(FILE *FP,bst *tree){

}

void checkBST(bst *tree){

}