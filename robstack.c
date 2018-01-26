/* Implementations of the leaf_stack and inner_stack as found in rob_stack.h */

#include <stdlib.h>

#include "bintree.h"
#include "robstack.h"


/******** inner_stack code ********/

void is_make(inner_stack** is, node* t) {
    *is = (inner_stack*) malloc(sizeof(inner_stack));
    (*is)->top = t;
    (*is)->cur = NULL;
}

/**  performs a link-inversion with the current node and p **/
void is_push(inner_stack* is, node* p) {
    if (p->left) {
        is->cur = p->left;
        p->left = is->top;
        is->top = p;
    } else {
        is->cur = p->right;
        p->right = is->top;
        is->top = p;
    }
}

node* is_top(inner_stack* is) {
    return is->top;
}

/* un-inverts the links, going back up the tree. */
void is_pop(inner_stack* is) {
    node *pred;
    node* temp;
    if (is->top->left == NULL) {
        pred = is->top->right;
        is->top->right = is->cur;
        temp = is->top;
        is->top = pred;
        is->cur = temp;
    } else if (is->top->right == NULL) {
        pred = is->top->left;
        is->top->left = is->cur;
        temp = is->top;
        is->top = pred;
        is->cur = temp;
    } else {
        if (is->top->left == is->top) {
            pred = NULL;
        } else {
            pred = is->top->left;
        }
        is->top->left = is->top->right;
        is->top->right = is->cur;
        temp = is->top;
        is->top = pred;
        is->cur = temp;
    }
}

/* exchange is used when `p` has a right child, and we are looking for a next subtree
// it sets the current pointer `cur` to that right pointer
// */
node* is_exchange(inner_stack* is, node* p) {
    node* temp = is->top->right;
    is->top->right = p;
    is->cur = temp;
    return temp;
}

/* the inner_stack is empty at the root, and when we have
// nothing left to traverse.
// */
bool is_empty(inner_stack* is) {
    return is->top == NULL;
}


/******** leaf_stack code ********/

void ls_make(leaf_stack** ls) {
    *ls = (leaf_stack*) malloc(sizeof(leaf_stack));
    (*ls)->avail = NULL;
    (*ls)->top = NULL;
}

/** Moves the top of the leaf_stack to the next available spot,
    Having it point at `p` **/
void ls_push(leaf_stack* ls, node* p) {
    ls->avail->left = ls->top;
    ls->avail->right = p;
    ls->top = ls->avail;
}

/* peeks the top of the leaf stack.
// if the top of `ls` is seen, then
// we can start stop popping up the tree.
// */
node* ls_top(leaf_stack* ls) {
    if (ls->top) {
        return ls->top->right;
    } else {
        return NULL;
    }
}

/** The left pointer of the leaf_stack is to the next item on the stack.
    The right pointer on the leaf stack is to the inner node
    the top node itself is a leaf, so after we pop, we must reset its links to NULL. **/
void ls_pop(leaf_stack* ls) {
    node* held = ls->top;
    ls->top = ls->top->left;
    held->left = NULL;
    held->right = NULL;
}

/* the leaf_stack is empty once we have nothing left to traverse.
// */
bool ls_empty(leaf_stack* ls) {
    return ls->top == NULL;
}
/* set_avail is a holding variable
// and will soon enough be put on top of `ls` by a push call.
// */
void ls_set_avail(leaf_stack* ls, node* p) {
    ls->avail = p;
}
