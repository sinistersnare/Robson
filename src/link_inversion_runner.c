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

void no_visit(Tree* unused) { (void) unused;}


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

    /* tree_print(t); */
    link_inversion(t, pre_visit, in_visit, post_visit);
    tree_free(t);
    return 0;
}
