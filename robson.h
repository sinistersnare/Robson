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

Tree* tree_insert(Tree* cur, int data) {
    if (cur == NULL) {
        Tree* new_node = (Tree*) malloc(sizeof(Tree));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (cur->data > data) {
        cur->left = tree_insert(cur->left, data);
    } else if (cur->data < data) {
        cur->right = tree_insert(cur->right, data);
    }
    return cur; /* Tree = Set, swallow duplicates. */
}

void _tree_print_aux(Tree* cur, int indentation) {
    if (cur == NULL) {
        printf("%*c- NULL\n", (indentation * 2), ' ');
        return;
    }
    printf("%*c- %d\n", (indentation * 2), ' ', cur->data);
    _tree_print_aux(cur->left, indentation + 1);
    _tree_print_aux(cur->right, indentation + 1);
}
void tree_print(Tree* cur) {
    _tree_print_aux(cur, 0);
}

#endif
