#include <stdio.h>
#include <stdlib.h>

#include "threaded.h"

void visit(Tree* node) {
    printf("%d\n", node->data);
}

/**
    Runs an in-order traversal on the tree.
*/
void threaded_traversal(Tree* root, VisitFunc visitor) {
    Tree* cur;
    if (root == NULL) return;

    cur = root;
    /* Go all the way down to the smallest number in the tree.*/
    while (!cur->left_thread) {
        cur = cur->left;
    }

    /* Now all we have to do is go rightwards until the end!*/
    while (cur != NULL) {
        visitor(cur);
        cur = tree_successor(cur);
    }
}

int main(int argc, const char** argv) {
    Tree* t;
    int i;

    if (argc < 2) {
        printf("Threaded Traverasl takes more than 0 int arguments to add to tree in given order.");
        return 1;
    }

    t = NULL;

    for (i=1; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    /* tree_print(t);*/
    threaded_traversal(t, visit);
    return 0;
}

