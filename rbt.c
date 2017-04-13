#include "rbt.h"

typedef struct rbtValue {
    void *rVal;
    int freq;
    int color;
    void (*display)(FILE*fp,void*);
    int (*compare)(void*,void*);
}rbtValue;

static rbtValue *newRBTValue(void (*)(FILE *,void *),int (*)(void *,void *));
static void insertionFixUp(bst*, bstNode*);
static bstNode *findUncle(bstNode *n);
static int findColor(bstNode *);
static int checkLinear(bstNode *, bstNode *);
static void rotate(bst *, bstNode*);
static void displayRBTValue(FILE *, void *);
static int rbtComparator(void *, void *);

rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    rbt *r = malloc(sizeof(rbt));
    if (r == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    r->tree = newBST(displayRBTValue,rbtComparator);
    r->display = d;
    r->compare = c;
    r->size = 0;
    r->words = 0;
    return r;
}

void insertRBT(rbt *r,void *val) {
    rbtValue *rbtV = newRBTValue(r->display,r->compare);
    rbtV->rVal = val;
    //if it's the root incriment size/words, color is already Black and insert it
    if (sizeRBT(r) == 0) {
        r->size++;
        r->words++;
        insertBST(r->tree, rbtV);
        return;
    }
    bstNode *n = findBSTNode(r->tree,rbtV);
    //if it doens't exist
    if (n == 0) {
        r->size++;
        //set node red
        rbtV->color = 1;
        n = insertBST(r->tree, rbtV);
        insertionFixUp(r->tree,n);
    }
    else
        ((rbtValue *)(n->value))->freq++;
    r->words++;
}

int findRBT(rbt *r,void *val) {
    rbtValue *rbtV = newRBTValue(r->display,r->compare);
    rbtV->rVal = val;
    //look in the bst for that value
    bstNode *n = findBSTNode(r->tree,rbtV);
    //if it wasn't found return 0
    if (n == 0)
        return 0;
    //return the freq
    else
        return ((rbtValue *)(n->value))->freq;
}

void deleteRBT(rbt *r, void *val) {
	r = NULL;
	val = NULL;
}

int sizeRBT(rbt *r) {
    return r->size;
}

int wordsRBT(rbt *r) {
    return r->words;
}

void statisticsRBT(rbt *r,FILE *fp) {
    fprintf(fp, "Words/Phrases: %d\n", wordsRBT(r));
    statisticsBST(r->tree,fp);
}

void displayRBT(FILE *fp,rbt *r) {
    displayBST(fp,r->tree);
}

/****************************** private functions ******************************/

static rbtValue *newRBTValue(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    rbtValue *rbtV = malloc(sizeof(rbtValue));
    if (rbtV == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    rbtV->display = d;
    rbtV->compare = c;
    rbtV->rVal = 0;
    //0 is black 1 is red
    rbtV->color = 0;
    rbtV->freq = 1;
    return rbtV;
}

static void insertionFixUp(bst *b, bstNode *n) {
    bstNode *uncle = NULL, *p = NULL, *gP = NULL, *oldP, *oldN;
    while(1) {
        //if root exit
        if (n == b->root)
            break;
        p = n->parent;
        //if parent is black
        if (!findColor(p))
            break;
        uncle = findUncle(n);
        gP = n->parent->parent;
        //if uncle exist and is red, color parent, uncle, gp, black set n to grandparent
        if (findColor(uncle)) {
            ((rbtValue*)p->value)->color = 0;
            ((rbtValue*)uncle->value)->color = 0;
            ((rbtValue *) gP->value)->color = 1;
            n = gP;
        }
        //uncle must be black or non existant
        else {
            //seeing if they are linear
            if (!checkLinear(n->parent,n)) {
                oldP = p;
                oldN = n;
                //rotate x to parent
                rotate(b,n);
                n = oldP;
                p = oldN;
            }
            //color parent black, gp red, rotate p to gP
            ((rbtValue*)p->value)->color = 0;
            ((rbtValue*)gP->value)->color = 1;
            //rotate parent to grandparent
            rotate(b,p);
            break;
        }
    }
    ((rbtValue*)b->root->value)->color = 0;
}

static int findColor(bstNode *n) {
    if (n == NULL)
        return 0;
    else
        return ((rbtValue*)n->value)->color;
}

bstNode *findUncle(bstNode *n) {
    //if isLeftChild(parent(n)) aka. if the parent is a left child
    if (n->parent->parent->left == n->parent) {
        //return rightChild(grandparent(n))
        return n->parent->parent->right;
    }
    else
        return n->parent->parent->left;
}

static int checkLinear(bstNode *p, bstNode *n) {
    //if parent is a left child
    if (p->parent->left == p) {
        //n must be a left child to be linear
        if (n->parent->left == n)
            return 1;
        else
            return 0;
    }
    //parent must be a right child
    else {
        //n must be a right child to be linear
        if (n->parent->right == n)
            return 1;
        else
            return 0;
    }
}

static void rotate(bst *b, bstNode *n) {
    bstNode *p = n->parent;
    bstNode *gP = n->parent->parent;
    bstNode *nL = n->left;
    bstNode *nR = n->right;
    //gonna rotate left
    if (p->right == n) {
        n->left = p;
        p->parent = n;
        p->right = nL;
        if (nL != NULL)
            nL->parent = p;
        if (p == b->root) {
            n->parent = n;
            b->root = n;
        }
        else {
            if (gP->left == p)
                gP->left = n;
            else
                gP->right = n;
            n->parent = gP;
        }
    }
    //gonna rotate right
    else {
        n->right = p;
        p->parent = n;
        p->left = nR;
        if (nR != NULL)
            nR->parent = p;
        if (p == b->root) {
            n->parent = n;
            b->root = n;
        }
        else{
            //if p was a right child
            if (gP->right == p)
                gP->right = n;
            else
                gP->left = n;
            n->parent = gP;
        }
    }
}

static void displayRBTValue(FILE *fp, void *val) {
    rbtValue *r = (rbtValue*)val;
    r->display(fp,r->rVal);
    if (r->freq > 1)
        fprintf(fp, "-%d",r->freq);
    if (r->color == 0)
        fprintf(fp,"-B");
    else
        fprintf(fp,"-R");
}

static int rbtComparator (void *a, void *b) {
    rbtValue *x = (rbtValue*)a;
    rbtValue *y = (rbtValue*)b;
    return x->compare(x->rVal,y->rVal);
}
