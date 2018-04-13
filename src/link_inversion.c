#include <stdio.h>
#include <stdlib.h>

#include "link_inversion.h"


void link_inversion(Tree* cur, VisitFunc pre_order, VisitFunc in_order, VisitFunc post_order) {
    Tree* prev = NULL;
    Tree* old_prev;
    Tree* old_prev_left;
    Tree* old_cur;

    if (cur == NULL) return;

    for (;;) {
        /* Descend leftward as much as possible.*/
        while (cur != NULL) {
            pre_order(cur);
            cur->went_right = false;
            old_cur = cur;
            cur = old_cur->left;
            old_cur->left = prev;
            prev = old_cur;
        }

        /* ascend from right as much as we can.*/
        while (prev != NULL && prev->went_right == true) {
            old_prev = prev;
            prev = prev->right;
            old_prev->right = cur;
            cur = old_prev;
            post_order(cur);
        }

        /* If cur is null after coming back up from the right,
        // it means that we have finished traversal*/
        if (prev == NULL) return;

        /* Switch from the left side of prev to the right
        // Also, mark prev as went_right so we know to traverse upwards using right pointer.*/
        in_order(prev);
        old_prev_left = prev->left;
        prev->went_right = true;
        prev->left = cur;
        cur = prev->right;
        prev->right = old_prev_left;
    }
}



/************************** Tree Implementation **************************/



Tree* tree_insert(Tree* cur, int data) {
    if (cur == NULL) {
        Tree* new_node = (Tree*) malloc(sizeof(Tree));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->went_right = false;
        return new_node;
    }
    if (cur->data > data) {
        cur->left = tree_insert(cur->left, data);
    } else if (cur->data < data) {
        cur->right = tree_insert(cur->right, data);
    }
    return cur; /* Tree = Set, swallow duplicates.*/
}

void tree_print_aux(Tree* cur, int indentation) {
    if (cur == NULL) {
        printf("%*c- NULL\n", (indentation * 2), ' ');
        return;
    }
    printf("%*c- %d\n", (indentation * 2), ' ', cur->data);
    tree_print_aux(cur->left, indentation + 1);
    tree_print_aux(cur->right, indentation + 1);
}
void tree_print(Tree* cur) {
    tree_print_aux(cur, 0);
}

/* Post-order where traverse is free!! */
void tree_free(Tree* cur) {
    if (cur == NULL) return;
    tree_free(cur->left);
    tree_free(cur->right);
    free(cur); /* Boom */
}
