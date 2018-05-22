#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "robson.h"

/* the memory address 1 will never be valid, so it makes a good sentinel. */
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
    Tree* top = NULL;
    Tree* available = NULL;
     /* Using a sentinel pointer value here instead of NULL
     because if the roots parent was NULL, on the way up the tree
     when the root is the parent, the parent->left == NULL,
     and the algorithm would think that we are in a right branch. */
    Tree* parent = ROOT_PARENT_SENTINEL;

    if (cur == NULL) return;

    while (1) {
        pre_visit(cur);

        /* Push down the tree until we find a leaf and use the information
            we gained on the way down to find the next subtree to traverse
            after the leaf. Pushing down the tree means adding inverted pointers
            to the inner_stack so we can get back up the tree.

            When we reach the leaf, we mark it as available to the leaf stack. */
        if (cur->left != NULL) {
            /* If there is a left to traverse, we must traverse it. */
            Tree* old_left = cur->left;
            cur->left = parent;
            parent = cur;
            cur = old_left;
        } else if (cur->right != NULL) {
            /* If there is no left but a right to traverse, we must traverse it. */
            Tree* old_right = cur->right;
            in_visit(cur);
            cur->right = parent;
            parent = cur;
            cur = old_right;
        } else {
            /* No children, at a leaf. */
            bool exchanged = false;
            available = cur;
            in_visit(cur);
            while (!exchanged && parent != ROOT_PARENT_SENTINEL) {
                Tree* old_cur = cur;
                if (parent->right == NULL) {
                    /* We are ascending from the left here, but there is no right tree to exchange with.
                        so just keep going on up. */
                    /* Here, parent->left is parent's parent, and parent->right == NULL */
                    Tree* new_parent = parent->left;
                    in_visit(parent);
                    parent->left = cur;
                    cur = parent;
                    parent = new_parent;
                } else if (parent->left == NULL) {
                    /* We are ascending from the right here, but only because there was no left
                        child to traverse, so the leaf-stack is to be left unaltered. */
                    /* In this case, parent->left == NULL and parent->right is parent's parent. */
                    Tree* new_parent = parent->right;
                    parent->right = cur;
                    cur = parent;
                    parent = new_parent;
                } else if (top != NULL && parent == top->right) {
                    /* If the parent node is an exchange point (when we switched from left to right subtree)
                        then we are *ascending from the right subtree*. What we must do is keep going up
                        as we have not yet found another subtree to traverse.
                        To do that, we pop off of the leaf-stack (top/avail)
                        Remember that top->right is an exchange point,
                        and top->left is the next leaf in the stack. */
                    /* In this case, the parents left pointer points to its parent,
                        and its right pointer points to its left child. */
                    Tree* old_top = top;
                    Tree* new_parent = parent->left;
                    parent->left = parent->right;
                    parent->right = cur;
                    cur = parent;
                    parent = new_parent;
                    /* pop the leaf stack, the top's left pointer is the next leaf in the stack,
                        and there will always be one, but I dont feel like formally proving it.
                        Exercise to the reader <3 */
                    top = top->left;
                    old_top->left = NULL;
                    old_top->right = NULL;
                } else  {
                    /* After saving the most interesting case for last, here we are!
                        We are ascending from the left, and there is a right tree
                        that we have not traversed! */
                    Tree* new_cur;
                    assert(available != NULL);
                    /* Available becomes the new top of the leaf stack,
                        and parent is the exchange point. */
                    new_cur = parent->right;
                    available->left = top;
                    available->right = parent;
                    top = available;
                    available = NULL; /* For cleanliness purposes. */
                    /* A right link going leftwards, which seems confusing,
                        but its so we know which way we are going on the way back up */
                    parent->right = cur;
                    cur = new_cur;
                    /* parent need not change! */
                    exchanged = true;
                }
                post_visit(old_cur);
            }
            /* If we make it here and we have not exchanged, there are no more suitable subtrees.
                we are at the root, and so we are done! */
            if (!exchanged) {
                post_visit(cur);
                return;
            }
        }
    }
}



/************************** Tree Implementation **************************/


Tree* tree_insert(Tree* cur, int data) {
    if (cur == NULL) {
        Tree* new_node = (Tree*) malloc(sizeof(Tree));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (cur->data > data) {
        cur->left = tree_insert(cur->left, data);
    } else if (cur->data < data) {
        cur->right = tree_insert(cur->right, data);
    }
    return cur; /* Tree = Set, swallow duplicates. */
}

void _tree_print_aux(Tree* cur, int indentation, int max_depth) {
    if (indentation >= max_depth) {
        return;
    }
    if (cur == NULL) {
        printf("%*c- NULL\n", (indentation * 2), ' ');
        return;
    }
    printf("%*c- %d\n", (indentation * 2), ' ', cur->data);
    _tree_print_aux(cur->left, indentation + 1, max_depth);
    _tree_print_aux(cur->right, indentation + 1, max_depth);
}
void tree_print(Tree* cur) {
    _tree_print_aux(cur, 0, INT_MAX);
}

void tree_print_depth(Tree* cur, int max_depth) {
    _tree_print_aux(cur, 0, max_depth);
}

void none_visit(Tree* unused) {(void) unused;}
void free_visit(Tree* cur) { free(cur); }
void tree_free(Tree* cur) {
    if (cur == NULL) return;
    tree_free(cur->left);
    tree_free(cur->right);
    free(cur);
}
