#ifndef LINK_INVERSION_H
#define LINK_INVERSION_H "You're awesome!"

#ifndef __cplusplus
/* Quick and dirty bool support */
#define bool int
#define true 1
#define false 0
#endif



typedef struct Tree {
    int data;
    struct Tree* left;
    struct Tree* right;
    bool went_right;
} Tree;

typedef void (*VisitFunc)(Tree*);

void link_inversion(Tree*, VisitFunc, VisitFunc, VisitFunc);


/** Tree Related functions **/
Tree* tree_insert(Tree*, int);
void tree_print(Tree*);
void tree_free(Tree*);



#endif
