#ifndef BINTREE_H
#define BINTREE_H

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

typedef struct tree {
    struct node* root;
} tree;

void node_make(node**, int);
node* node_insert(node*, int);
void node_free(node*);
void node_print(node*);
void tree_make(tree**);
tree* tree_new();
void tree_insert(tree*, int);
void tree_free(tree**);
void tree_print(tree*);

#endif
