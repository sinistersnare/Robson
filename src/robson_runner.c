#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

    /*tree_print(t);*/
    robson_traversal(t, pre_func, in_func, post_func);
    fflush(stdout);
    tree_free(t);
    return 0;
}
