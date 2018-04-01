/*
    A standalone C program to demonstrate the link_inversion method for traversing binary trees.

    To run, simply call gcc on it:

    `$ gcc link_inversion.c -o inv.x`
    `$ ./inv.x 1 3 2 4 5
*/

#include <stdio.h>
#include <stdlib.h>

#include "link_inversion.h"



void pre_visit(Tree* node) {
    printf("pre:%d\n", node->data);
}

void in_visit(Tree* node) {
    printf("in:%d\n", node->data);

}

void post_visit(Tree* node) {
    printf("post:%d\n", node->data);
}

void no_visit(Tree* node) {}


void link_inversion(Tree* cur, VisitFunc pre_order, VisitFunc in_order, VisitFunc post_order) {
    if (cur == NULL) return;

    Tree* prev = NULL;
    for (;;) {
        // Descend leftward as much as possible.
        while (cur != NULL) {
            pre_order(cur);
            cur->went_right = false;
            Tree* old_cur = cur;
            cur = old_cur->left;
            old_cur->left = prev;
            prev = old_cur;
        }

        // ascend from right as much as we can.
        while (prev != NULL && prev->went_right == true) {
            Tree* old_prev = prev;
            prev = prev->right;
            old_prev->right = cur;
            cur = old_prev;
            post_order(cur);
        }

        // If cur is null after coming back up from the right,
        // it means that we have finished traversal
        if (prev == NULL) return;

        // Switch from the left side of prev to the right
        // Also, mark prev as went_right so we know to traverse upwards using right pointer.
        in_order(prev);
        Tree* old_prev_left = prev->left;
        prev->went_right = true;
        prev->left = cur;
        cur = prev->right;
        prev->right = old_prev_left;
    }
}

int main(int argc, const char** argv) {
    Tree* t;
    int i;

    if (argc < 2) {
        printf("Link Inversion takes more than 0 int arguments to add to tree in given order.");
        return 1;
    }

    t = NULL;

    for (i=1; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    // tree_print(t);
    link_inversion(t, no_visit, in_visit, no_visit);
}


