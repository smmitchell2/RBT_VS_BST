#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "bst.h"

#define min(a,b)	(((a) < (b)) ? (a) : (b))

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
    tree->display = d;
    tree->compare = c;
    return tree;
}

static int maximum(bstNode *n){
  if(n == NULL){
    return 0;
  }
  else{
	int l = maximum(n->left);
	int r = maximum(n->right);
	if(l > r){
	  return (l+1);
	}
	else{
	  return (r + 1);
	}
  }
}

static int minimum(bstNode *n){
  if(n == NULL){
    return 0;
  }
  if(n->left == NULL && n->right == NULL){
    return 1;
  }
  return min(minimum(n->left), minimum(n->right))+1;
}

bstNode *maxValue(bstNode *n){
  bstNode *current = n;
  while(current->right != NULL){
    current = current->right;
  }
  return current;
}

bstNode *minValue(bstNode *n){
  bstNode *current = n;
  while(current->left != NULL){
    current = current->left;
  }
  return current;
}

bstNode *predecessor(bstNode *n){
  if(n->left != NULL){
    return maxValue(n->left);
  }
  bstNode *p = n->parent;
  while(p != NULL && n == p->left){
    n = p;
	p = p->parent;
  }
  return p;
}

bstNode *successor(bstNode *n){
  if(n->right != NULL){
    return minValue(n->right);
  }
  bstNode *p = n->parent;
  while(p != NULL && n == p->right){
	n = p;
	p = p->parent;
  }
  return p;
}

bstNode *insertHelper(bst *tree, bstNode *root, bstNode *prev, void *valToInsert){
  bstNode *temp = valToInsert;
  if(!root){
    root = temp;
	if(prev != NULL){
	  root->parent = prev;
	}
	else{
	  root->parent = root;
	}
	return root;	
  }
  else if(tree->compare(root, temp) > 0){
    root->left = insertHelper(tree, root->left, root, valToInsert);
  }
  else if(tree->compare(root, temp) <= 0){
	root->right = insertHelper(tree, root->right, root, valToInsert);
  }
  return root;
}

bstNode *insertBST(bst *tree, void *data){
  bstNode *n = newBSTNode(data);
  tree->root = insertHelper(tree, tree->root, NULL, n);
  return tree->root;
  return n;
}

static int findHelper(bst *tree, bstNode *root, void *value){
  bstNode *tempNode = value;
  if(!root){
    return 0;
  }
  if(tree->compare(root, tempNode) > 0){
    return findHelper(tree, root->left, tempNode);
  }
  else if(tree->compare(root, tempNode) < 0){
	return findHelper(tree, root->right, tempNode);
  }
  else if(tree->compare(root, tempNode) == 0){
    return 1;
  }
  return 0;
}

int findBST(bst *tree, void *data){
    bstNode *newNode = newBSTNode(data);
	return findHelper(tree, tree->root, newNode);
}

static bstNode *findBSTHelper(bst *tree, bstNode *root, void *value){
  bstNode *tempNode = value;
  if(!root){
    return 0;
  }
  if(tree->compare(root, tempNode) > 0){
    root = findBSTHelper(tree, root->left, value);
  }
  else if(tree->compare(root, tempNode) < 0){
    root = findBSTHelper(tree, root->right, value);
  }
  return root;
}


bstNode *findBSTNode(bst *tree, void *data){
  bstNode *newNode = newBSTNode(data);
  return findBSTHelper(tree, tree->root, newNode);
}

bstNode *swapToLeafBSTNode(bstNode *n){
  if(n->left == NULL && n->right == NULL){
	return n;
  }
  bstNode *np = NULL;
  if(n->left != NULL){
	np = predecessor(n);
  }
  else{
	np = successor(n);
  }
  void *temp = n->value;
  n->value = np->value;
  np->value = temp;
  return swapToLeafBSTNode(np);
}

void pruneBSTNode(bst *tree,bstNode *n){
  if(n->parent->left != NULL){
    if(tree->compare(n->parent->left, n) == 0){
	  n->parent->left = NULL;
	  n = NULL;
	  return;
    }
  }
  if(n->parent->right != NULL){
	if(tree->compare(n->parent->right, n) == 0){
	  n->parent->right = NULL;
	  n = NULL;
	  return;
	}
  }
}

static int sizeHelper(bstNode *node){
  if(node == NULL){
    return 0;
  }
  else{
    return(sizeHelper(node->left) + 1 + sizeHelper(node->right));
  }
}

int sizeBST(bst *tree){
  return sizeHelper(tree->root);
}

void statisticsBST(bst *tree,FILE *fp){
  fprintf(fp, "Nodes: %d\n", sizeBST(tree));
  fprintf(fp, "Minimum depth: %d\n", minimum(tree->root));
  fprintf(fp, "Maximum depth: %d\n", maximum(tree->root));
}

static void recursiveHelper(bst *t, bstNode *root, FILE *fp){
  queue *q = newQueue(t->display);
  int levelNodes = 0;
  int level = 0;
  if(root == NULL){
    return;
  }
  enqueue(q, root);
  while(sizeQueue(q) != 0){
    fprintf(fp, "%d:", level);
	levelNodes = sizeQueue(q);
	while(levelNodes > 0){
	  fprintf(fp, " ");
	  bstNode *n = dequeue(q);
	  if(n->left == NULL && n->right == NULL){
	    fprintf(fp, "=");
	  }
	  t->display(fp, n->value);
	  fprintf(fp, "(");
	  if(n->parent == NULL || n->parent == 0){
		t->display(fp, n->value);
	  }
	  else{
		t->display(fp, n->parent->value);
	  }
	  fprintf(fp, ")");
	  if(n->left != NULL){
		enqueue(q, n->left);
	  }
	  if(n->right != NULL){
		enqueue(q, n->right);
	  }
	  if(n->parent->left != NULL){
	    if(t->compare(n, n->parent->left) == 0){
		  fprintf(fp, "-l");
		}
      }
	  if(n->parent->right != NULL){
	    if(t->compare(n, n->parent->right) == 0){
		  fprintf(fp, "-r");
	    }
	  }
	  if(t->compare(n, n->parent) == 0){
	    fprintf(fp, "-");
	  }
	  levelNodes--;
	}
	fprintf(fp, "\n");
	level++;
  }
}

void displayBST(FILE *fp,bst *tree){
  recursiveHelper(tree, tree->root, fp);
}
