#include <stdio.h>
#include <stdlib.h>

#include "robson.h"

void no_visit(Tree* unused) {(void) unused;}
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
    Tree* t = NULL;
    int i;

    if (argc < 2) {
        printf("Robson Traversal takes more than 0 int arguments to add to tree in given order.");
        return 1;
    }

    for (i=1; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    /*tree_print(t);*/
    robson_traversal(t, pre_visit, in_visit, post_visit);
    tree_free(t);
    return 0;
}
