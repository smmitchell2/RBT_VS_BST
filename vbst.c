#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "vbst.h"

typedef struct vbstValue{
  void *value;
  int freq;
  void (*display)(FILE *, void *);
  int (*compare)(void *, void *);
} vbstValue;

static void vbstDisplay(FILE *, void *);

static int vbstComparator(void *x, void *y){
  vbstValue *a = x;
  vbstValue *b = y;
  return a->compare(a->value, b->value);
}

vbst *newVBST(void (*display)(FILE *, void *), int(*comparator)(void *, void *)){
  vbst *newVBST = malloc(sizeof(vbst));
  newVBST->tree = newBST(vbstDisplay, vbstComparator);
  newVBST->display = display;
  newVBST->compare = comparator;
  newVBST->size = 0;
  newVBST->words = 0;
  return newVBST;
}

static vbstValue *newVBSTValue(vbst *v, void *value){
  vbstValue *newVBSTValue = malloc(sizeof(vbstValue));
  newVBSTValue->value = value;
  newVBSTValue->freq = 1;
  newVBSTValue->display = v->display;
  newVBSTValue->compare = v->compare;
  return newVBSTValue;
}


void insertVBST(vbst *v, void *val){
  //get the value in the tree if it exist
    vbstValue *vbstV = newVBSTValue(v,val);
    vbstV->value = val;
    bstNode *n = findBSTNode(v->tree,vbstV);
    //if that node doesn't exist
    if (n==0) {
        v->size++;
        (void)insertBST(v->tree,vbstV);
    }
    //if it did update it's freq
    else
        ((vbstValue *)(n->value))->freq++;
    v->words++;
}

int findVBST(vbst *v, void *value){
	vbstValue *newValue = newVBSTValue(v, value);
	bstNode *n = findBSTNode(v->tree, newValue);
	if(n == NULL){
	  return 0;
	}
	vbstValue *val = n->value;
	return val->freq;
}

void deleteVBST(vbst *v, void *value){
	vbstValue *newValue = newVBSTValue(v, value);
	int temp = findVBST(v, value);
	if(temp > 1){
	  bstNode *temp = findBSTNode(v->tree, newVBSTValue(v, value));
	  vbstValue *t = temp->value;
	  t->freq -= 1;
	  v->size--;
	}
	else if(temp == 1){
	  bstNode *temp = findBSTNode(v->tree, newValue);
	  temp = swapToLeafBSTNode(temp);
	  pruneBSTNode(v->tree, temp);
	  v->size--;
	  v->words--;
	  vbstValue *t = temp->value;
	  t->freq -= 1;
	  return;
	}
	else{
	  fprintf(stderr, "Value \"%s\" not found.\n", (char*)value);
    }
}

int sizeVBST(vbst *v){
  return v->size;
}

int wordsVBST(vbst *v){
  return v->words;
}

void statisticsVBST(vbst *v, FILE *fp){
  fprintf(fp, "Words/Phrases: %d\n", wordsVBST(v));
  statisticsBST(v->tree, fp);
}

void vbstDisplay(FILE *fp, void *v){
  vbstValue *value = v;
  value->display(fp, value->value);
  int freq = value->freq;
  if(freq > 1){
	fprintf(fp, "-%d", freq);
  }
}

void displayVBST(FILE *fp, vbst *v){
  displayBST(fp, v->tree);
}

