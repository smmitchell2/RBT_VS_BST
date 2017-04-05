#include "bst.h"
#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct rbtValue{
	void *value;
	int freq;
	int color;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
} rbtValue;

static rbtValue *newRBTValue(rbt *, void *);
static void rbtDisplay(FILE *, void *);

static int rbtComparator(void *x, void *y){
	if(x == NULL || y == NULL){
		return 1;
	}
	rbtValue *a = x;
	rbtValue *b = y;
	if(a->value == NULL || b->value == NULL){
		return 1;
	}
	return a->compare(a->value, b->value);
}

static int nodeComparator(void *x, void *y){
	if(x == NULL || y == NULL){
		return 1;
	}
	bstNode *temp1 = x;
	bstNode *temp2 = y;
	rbtValue *a = temp1->value;
	rbtValue *b = temp2->value;
	if(a->value == NULL || b->value == NULL){
		return 1;
	}
	return a->compare(a->value, b->value);
}

rbt *newRBT(void (*display)(FILE *, void *), int(*comparator)(void *, void *)){
	rbt *newRBT = malloc(sizeof(rbt));
	newRBT->tree = newBST(rbtDisplay, rbtComparator);
	newRBT->display = display;
	newRBT->compare = comparator;
	newRBT->size = 0;
	newRBT->words = 0;
	return newRBT;
}

static rbtValue *newRBTValue(rbt *r, void *value){
	rbtValue *newRBTValue = malloc(sizeof(rbtValue));
	newRBTValue->value = value;
	newRBTValue->freq = 1;
	newRBTValue->display = r->display;
	newRBTValue->compare = r->compare;
	newRBTValue->color = 0;
	return newRBTValue;
}

static void replaceNode(rbt *r, bstNode *oldNode, bstNode *newNode){
	if(nodeComparator(oldNode, r->tree->root) == 0){
		r->tree->root = newNode;
	}
	else{
		if(nodeComparator(oldNode, oldNode->parent->left) == 0){
			oldNode->parent->left = newNode;
		}
		else{
			oldNode->parent->right = newNode;
		}
	}
	if(newNode != NULL){
		newNode->parent = oldNode->parent;
	}
}

static void rightRotate(rbt *r, bstNode *node){
	bstNode *leftNode = node->left;
	replaceNode(r, node, leftNode);
	node->left = leftNode->right;
	if(leftNode->right != NULL){
		leftNode->right->parent = node;
	}
	leftNode->right = node;
	node->parent = leftNode;
}

static void leftRotate(rbt *r, bstNode *node){
	bstNode *rightNode = node->right;
	replaceNode(r, node, rightNode);
	node->right = rightNode->left;
	if(rightNode->left != NULL){
		rightNode->left->parent = node;
	}
	rightNode->left = node;
	node->parent = rightNode;
}

static int color(rbtValue *rv){
	if(rv == NULL){
		return 0;
	}
	else
	{
		return rv->color;
	}
}


static bstNode *uncle(rbt *r, bstNode *b){
	if(b->parent == NULL || b->parent->parent->left == NULL){
		return r->tree->root;
	}
	if(nodeComparator(b->parent, b->parent->parent->left) == 0){
		return b->parent->parent->right;
	}
	else{
		return b->parent->parent->left;
	}
	return r->tree->root;
}


static void insertionFixUp(rbt *r, bstNode *node){
	while(1){
		if(nodeComparator(node, node->parent) == 0){
			break;
		}
		if(color(node->parent->value) == 0){
			break;
		}
		bstNode *unc = uncle(r, node);
		int color1 = 0;
		if(unc == NULL){
			rbtValue *tempValue = newRBTValue(r, "the");
			tempValue->color = 0;
			color1 = 0;
		}
		else{
			color1 = color(unc->value);
		}
		if(color1 == 1){
			rbtValue *parentValue = node->parent->value;
			parentValue->color = 0;
			rbtValue *uncleValue = uncle(r, node)->value;
			uncleValue->color = 0;
			rbtValue *grandparentValue = node->parent->parent->value;
			grandparentValue->color = 1;
			node = node->parent->parent;
		}
		else{
			if((nodeComparator(node, node->parent->right) == 0) && (nodeComparator(node->parent, node->parent->parent->left) == 0)){
				bstNode *oldParent = node->parent;
				bstNode *oldNode = node;
				leftRotate(r, node->parent);
				node = oldParent;
				node->parent = oldNode;
			
			}
			if((nodeComparator(node, node->parent->left) == 0) && (nodeComparator(node->parent, node->parent->parent->right) == 0)){
				bstNode *oldParent = node->parent;
				bstNode *oldNode = node;
				rightRotate(r, node->parent);
				node = oldParent;
				node->parent = oldNode;
			}
			rbtValue *parentValue = node->parent->value;
			parentValue->color = 0;
			rbtValue *grandparentValue = node->parent->parent->value;
			grandparentValue->color = 1;
			if(nodeComparator(node->parent, node->parent->parent->right) == 0){
				leftRotate(r, node->parent->parent);
			}
			else if(nodeComparator(node->parent, node->parent->parent->left) == 0){
				rightRotate(r, node->parent->parent);
			}
			break;
		}
		
	}
	rbtValue *root = r->tree->root->value;
	r->tree->root->parent = r->tree->root;
	root->color = 0;
}




void insertRBT(rbt *r, void *value){
	rbtValue *newValue = newRBTValue(r, value);
	int theValue = findBST(r->tree, newValue);
	if(theValue == 0){
		(void)insertBST(r->tree, newValue);
		bstNode *temp = findBSTNode(r->tree, newValue);
		rbtValue *tempValue = temp->value;
		tempValue->color = 1;
		insertionFixUp(r, findBSTNode(r->tree, tempValue));
		r->size++;
		r->words++;
	}
	else{
		bstNode *temp = findBSTNode(r->tree, newValue);
		rbtValue *temporary = temp->value;
		temporary->freq += 1;
		r->size++;
	}
}

int findRBT(rbt *r, void *value){
	rbtValue *newValue = newRBTValue(r, value);
	bstNode *node = findBSTNode(r->tree, newValue);
	if(node == NULL){
		return 0;
	}
	rbtValue *val = node->value;
	return val->freq;
}

int sizeRBT(rbt *r){
	return r->size;
}

int wordsRBT(rbt *r){
	return r->words;
}

void deleteRBT(rbt *r, void *v){
	(void)r;
	(void)v;
}

void statisticsRBT(rbt *r, FILE *fp){
	fprintf(fp, "Words/Phrases: %d\n", sizeRBT(r));
	statisticsBST(r->tree, fp);
}

void rbtDisplay(FILE *fp, void *v){
	rbtValue *value = v;
	value->display(fp, value->value);
	int freq = value->freq;
	if(freq > 1){
		fprintf(fp, "-%d", freq);
	}
	if(value->color == 0){
		fprintf(fp, "-B");
	}
	if(value->color == 1){
		fprintf(fp, "-R");
	}
}

void displayRBT(FILE *fp, rbt *r){
	displayBST(fp, r->tree);
}

