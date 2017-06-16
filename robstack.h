/* Struct and function defintions for objects used in a Robson Traversal */

/* node+tree code included because I couldnt get headers to work correctly at 3am... */

#ifndef ROB_STACK_H
#define ROB_STACK_H

#ifndef __cplusplus
/* Quick and dirty bool support */
#define bool int
#define true 1
#define false 0
#endif




typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

typedef struct tree {
    struct node* root;
} tree;

typedef struct inner_stack {
    node* top;
    node* cur;
} inner_stack;


typedef struct leaf_stack {
    node* avail;
    node* top;
} leaf_stack;


void node_make(node**, int);
node* node_insert(node*, int);
void node_free(node*);
void print_node(node*);
void tree_make(tree**);
void tree_insert(tree*, int);
void tree_free(tree**);
void tree_print(tree*);

/************** Inner Stack Functions **************/

void is_make(inner_stack**, node*);
void is_push(inner_stack*,node*);
node* is_top(inner_stack*);
void is_pop(inner_stack*);
node* is_exchange(inner_stack*, node*);
bool is_empty(inner_stack*);


/************** Leaf Stack Functions **************/

void ls_make(leaf_stack**);
void ls_push(leaf_stack*, node*);
node* ls_top(leaf_stack*);
void ls_pop(leaf_stack*);
bool ls_empty(leaf_stack*);
void ls_set_avail(leaf_stack*, node*);


#endif
