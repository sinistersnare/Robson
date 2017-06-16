/* Implementations of the node and tree as found in rob_stack.h */
#include <stdlib.h>
#include <stdio.h>
#include "robstack.h"

/**********    Node Code    **********/
/*************************************/

void node_make(node** n, int elem) {
    *n = (node*) malloc(sizeof(node));
    (*n)->data = elem;
    (*n)->left = NULL;
    (*n)->right = NULL;
}

node* node_insert(node* cur, int elem) {
    if (cur == NULL) {
        node* new_node;
        node_make(&new_node, elem);
        return new_node;
    }
    if (cur->data > elem) {
        cur->left = node_insert(cur->left, elem);
    } else if (cur->data < elem) {
        cur->right = node_insert(cur->right, elem);
    }
    return cur;
}

void node_free(node* cur) {
    if (cur == NULL) return;
    node_free(cur->left);
    cur->left = NULL;
    node_free(cur->right);
    cur->right = NULL;
    free(cur);
}

void print_node(node* n) {
    if (n == NULL) return;
    print_node(n->left);
    printf(" %d ", n->data);
    print_node(n->right);
}


/**********    Tree Code    **********/
/*************************************/

/** allocates space for a tree */
void tree_make(tree** t) {
    *t = (tree*) malloc(sizeof(tree));
    (*t)->root = NULL;
}


void tree_insert(tree* t, int elem) {
    t->root = node_insert(t->root, elem);
}

/* Frees all node in the tree, along with the tree itself, NULLifying it */
void tree_free(tree** t) {
    node_free((*t)->root);
    free(*t);
    (*t) = NULL;
}

/* Prints a tree in-order */
void tree_print(tree* t) {
    if (t == NULL) {
        puts("[]");
        return;
    }
    printf("[ ");
    print_node(t->root);
    printf(" ]\n");
}
