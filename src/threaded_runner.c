#include <stdio.h>
#include <stdlib.h>

#include "threaded.h"

void visit(Tree* node) {
    printf("%d\n", node->data);
}

int main(int argc, const char** argv) {
    Tree* t = NULL;
    int i;

    if (argc < 2) {
        printf("Threaded Traverasl takes more than 0 int arguments to add to tree in given order.");
        return 1;
    }

    for (i=1; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    threaded_traversal(t, visit);
    tree_free(t);
    return 0;
}
