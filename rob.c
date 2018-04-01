#include <stdio.h>
#include <stdlib.h>

#include "rob.h"

void no_visit(Tree* _) {}

void robson_traversal(Tree* tree, VisitFunc previsit, VisitFunc invisit, VisitFunc postvisit) {

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

    /* tree_print(t);*/
    robson_traversal(t, no_visit, no_visit, no_visit);
}


