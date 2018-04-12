#ifndef THREADED_H
#define THREADED_H "Youre a good programmer <3"

#ifndef __cplusplus
/* Quick and dirty bool support */
#define bool int
#define true 1
#define false 0
#endif

typedef struct Tree {
    struct Tree* left;
    struct Tree* right;
    bool left_thread;
    bool right_thread;
    int data;
} Tree;

typedef void (*VisitFunc)(Tree*);

void threaded_traversal(Tree*, VisitFunc);
Tree* tree_successor(Tree*);

Tree* tree_insert(Tree*, int);
int tree_size(Tree*);
int tree_height(Tree*);
void tree_print(Tree*);
void tree_free(Tree*);


#endif
