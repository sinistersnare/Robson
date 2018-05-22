#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int main(int argc, char** argv) {
    Tree* t = NULL;
    int i;
    int c;

    VisitFunc pre_func = no_visit;
    VisitFunc in_func = no_visit;
    VisitFunc post_func = no_visit;

    /* Takes pRe, iN, or pOst order.
        I used the second character because post and pre both start with same character,
        and this seemed like the best comprompise, nobody wins! */
    while ((c = getopt(argc, argv, "rno")) != -1) {
        switch (c) {
        case 'r': /* Pre-order enabled */
            pre_func = pre_visit;
            break;
        case 'n': /* In-order enabled */
            in_func = in_visit;
            break;
        case 'o': /* Post-order enabled */
            post_func = post_visit;
            break;
        case '?':
            printf("Unknown option: -%c.\n", optopt);
            return 1;
        default:
            printf("hmm, how'd I get here? %c\n", c);
        }
    }

    for (i = optind; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    link_inversion(t, pre_func, in_func, post_func);
    tree_free(t);
    return 0;
}
