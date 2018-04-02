#include <stdio.h>
#include <stdlib.h>

#include "robson.h"

/* the memory address 1 will never be valid, so it makes a good sentinel.*/
#define ROOT_PARENT_SENTINEL ((Tree*) 1)

/* Insightful comments are sporadically placed in anticipation of upcoming blog-post, sorry! */

/*
// When going up, going up from right means we can keep going up,
// The algorithm never goes from right to left, only left to right.
// So when we go up from left, we need to check if there is a right
// subtree, as then we need to traverse the right.
// And when we do find that right-subtree, we mark the root of it
// (the top of the little triangle from left-top-right created)
// using the `top` leaf-node's right pointer
// (its left is pointing to the next in the leaf-node stack)

// We know we are coming up from the right when the parent == top->right
// or when parent->left == NULL. Once we find the top->right condition,
// We set top = top->left for the next time we are going up.
*/
void robson_traversal(Tree* cur, VisitFunc pre_visit, VisitFunc in_visit, VisitFunc post_visit) {
    /* Currently only pre_visit is supported, in_visit and post_visit coming soon <3*/
    Tree* top = NULL;
    Tree* available = NULL;
     /* Using a sentinel pointer value here instead of NULL
     because if the roots parent was NULL, on the way up the tree
     when the root is the parent, the parent->left == NULL,
     and the algorithm would think that we are in a right branch.*/
    Tree* parent = ROOT_PARENT_SENTINEL;

    for (;;) {
        pre_visit(cur);

        /* Push down the tree until we find a leaf and use the information
            we gained on the way down to find the next subtree to traverse
            after the leaf. Pushing down the tree means adding inverted pointers
            to the inner_stack so we can get back up the tree.

            When we reach the leaf, we add it to the leaf_stack
            */
        if (cur->left != NULL) {
            Tree* old_left = cur->left;
            cur->left = parent;
            parent = cur;
            cur = old_left;
        } else if (cur->right != NULL) {
            Tree* old_right = cur->right;
            cur->right = parent;
            parent = cur;
            cur = old_right;
        } else {
            bool exchanged = false;
            available = cur;
            while (parent != ROOT_PARENT_SENTINEL) {
                if (top != NULL && parent == top->right) {
                    /* If the parent node is an exchange point (when we switched from left to right subtree)
                        then we are *ascending from the right subtree*. What we must do is keep going up
                        as we have not yet found another subtree to traverse.
                        To do that, we pop off of the leaf-stack (top/avail)
                        Remember that top->right is an exchange point,
                        and top->left is the next leaf in the stack. */
                    /* In this case, the parents left pointer points to its parent,
                        and its right pointer points to its left child.*/
                    Tree* new_parent = parent->left;
                    parent->left = parent->right;
                    parent->right = cur;
                    cur = parent;
                    parent = new_parent;
                    /* pop the leaf stack, the top's left pointer is the next leaf in the stack,
                        and there will always be one, but I dont feel like formally proving it.
                        Exercise to the reader <3*/
                    top = top->left;
                } else if (parent->left == NULL) {
                    /* We are still ascending from the right here, but only because there was no left
                        child to traverse, so the leaf-stack is to be left unaltered.*/
                    /* In this case, parent->left == NULL and parent->right is parent's parent.*/
                    Tree* new_parent = parent->right;
                    parent->right = cur;
                    cur = parent;
                    parent = new_parent;
                } else if (parent->right == NULL) {
                    /* We are ascending from the left here, but there is no right tree to exchange with.
                        so just keep going on up.*/
                    /* Here, parent->left is parent's parent, and parent->right == NULL */
                    Tree* new_parent = parent->left;
                    parent->left = cur;
                    cur = parent;
                    parent = new_parent;
                } else {
                    Tree* new_cur;
                    /* After saving the most interesting case for last, here we are!
                        We are ascending from the left, and there is a right tree
                        that we have not traversed!*/
                    if (available == NULL) {
                        printf("Error, available should never be NULL here!");
                        return;
                    }
                    /* Available becomes the new top of the leaf stack,
                        and parent is the exchange point.*/
                    new_cur = parent->right;
                    available->left = top;
                    available->right = parent;
                    top = available;
                    available = NULL; /* For cleanliness purposes.*/
                    /* A right link going leftwards, which seems confusing,
                        but its so we know which way we are going on the way back up*/
                    parent->right = cur;
                    cur = new_cur;
                    /* parent need not change!*/
                    exchanged = true;
                    break; /* Get out of this loop so we can go down again.*/
                }
            }
            /* If we make it here and we have not exchanged, then we are at the root
                after traversing the right tree, so we are done!*/
            if (!exchanged) return;
        }
    }
}


void no_visit(Tree* _) {}
void pre_visit(Tree* n) {
    printf("pre:%d\n", n->data);
}
void in_visit(Tree* n) {
    printf("in:%d\n", n->data);
}
void post_visit(Tree* n) {
    printf("post:%d\n", n->data);
}

int main(int argc, const char** argv) {
    Tree* t;
    int i;

    if (argc < 2) {
        printf("Robson Traversal takes more than 0 int arguments to add to tree in given order.");
        return 1;
    }

    t = NULL;

    for (i=1; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    /*tree_print(t);*/
    /* 1 2 5 4 7 1 3 8 10 1 11 */
    robson_traversal(t, pre_visit, no_visit, no_visit);
    return 0;
}


