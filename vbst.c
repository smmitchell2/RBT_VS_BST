#include "vbst.h"

typedef struct vbstValue {
    void *vVal;
    int freq;
    void (*display)(FILE*fp,void*);
    int (*compare)(void*,void*);
} vbstValue;

static vbstValue *newVBSTValue(void (*)(FILE *,void *),int (*)(void *,void *));
static void displayVBSTValue(FILE *, void *);
static int vbstComparator(void *,void *);

vbst *newVBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    vbst *v = malloc(sizeof(vbst));
    if (v == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    v->tree = newBST(displayVBSTValue,vbstComparator);
    v->display = d;
    v->compare = c;
    v->size = 0;
    v->words = 0;
    return v;
}

void insertVBST(vbst *v,void *val) {
    //get the value in the tree if it exist
    vbstValue *vbstV = newVBSTValue(v->display,v->compare);
    vbstV->vVal = val;
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

int findVBST(vbst *v, void *val) {
    vbstValue *vbstV = newVBSTValue(v->display,v->compare);
    vbstV->vVal = val;
    //look in the bst for that value
    bstNode *n = findBSTNode(v->tree,vbstV);
    //if it wasn't found return 0
    if (n == 0)
        return 0;
    //return the freq
    else
        return ((vbstValue *)(n->value))->freq;
}

void deleteVBST(vbst *v, void *val) {
    vbstValue *vbstV = newVBSTValue(v->display,v->compare);
    vbstV->vVal = val;
    bstNode *n = findBSTNode(v->tree,vbstV);
    //if the value doesn't exist print error message
    if (n == 0) {
        fprintf(stderr, "Value ");
        vbstV->display(stderr, vbstV->vVal);
        fprintf(stderr, " not found\n");
    }
    //it exist so remove it or decrease the freq
    else {
        if (((vbstValue *)(n->value))->freq == 1) {
            n = swapToLeafBSTNode(n);
            pruneBSTNode(v->tree, n);
        }
        else
            ((vbstValue *)(n->value))->freq--;
        //fix the word/size
        v->words--;
        v->size--;
    }
}

int sizeVBST(vbst *v) {
    return v->size;
}

int wordsVBST(vbst *v) {
    return v->words;
}

void statisticsVBST(vbst *v, FILE *fp) {
    fprintf(fp, "Words/Phrases: %d\n", wordsVBST(v));
    statisticsBST(v->tree,fp);
}

void displayVBST(FILE *fp,vbst *v) {
    displayBST(fp,v->tree);
}


/****************************** Private Functions ******************************/

static vbstValue *newVBSTValue(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    vbstValue *vbstV = malloc(sizeof(vbstValue));
    if (vbstV == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    vbstV->display = d;
    vbstV->compare = c;
    vbstV->vVal = 0;
    vbstV->freq = 1;
    return vbstV;
}

static void displayVBSTValue(FILE *fp, void *val) {
    vbstValue *v = (vbstValue*)val;
    v->display(fp,v->vVal);
    if (v->freq > 1)
        fprintf(fp, "-%d",v->freq);
}

static int vbstComparator(void *a,void *b) {
    vbstValue *x = (vbstValue*)a;
    vbstValue *y = (vbstValue*)b;
    return x->compare(x->vVal,y->vVal);
}