#ifndef ROBSON_H
#define ROBSON_H "Wooh cool algorithms!!"

#ifndef __cplusplus
/* Quick and dirty bool support */
#define bool int
#define true 1
#define false 0
#endif

typedef struct Tree {
    struct Tree* left;
    struct Tree* right;
    int data;
} Tree;

typedef void (*VisitFunc)(Tree*);

void robson_traversal(Tree*, VisitFunc, VisitFunc, VisitFunc);


Tree* tree_insert(Tree*, int);
void tree_print(Tree*);
void tree_free(Tree*);


void no_visit(Tree*);
void pre_visit(Tree*);
void in_visit(Tree*);
void post_visit(Tree*);

#endif
