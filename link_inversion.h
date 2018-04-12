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

Tree* tree_insert(Tree* cur, int data) {
    if (cur == NULL) {
        Tree* new_node = (Tree*) malloc(sizeof(Tree));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->went_right = false;
        return new_node;
    }
    if (cur->data > data) {
        cur->left = tree_insert(cur->left, data);
    } else if (cur->data < data) {
        cur->right = tree_insert(cur->right, data);
    }
    return cur; /* Tree = Set, swallow duplicates.*/
}

void tree_print_aux(Tree* cur, int indentation) {
    if (cur == NULL) {
        printf("%*c- NULL\n", (indentation * 2), ' ');
        return;
    }
    printf("%*c- %d\n", (indentation * 2), ' ', cur->data);
    tree_print_aux(cur->left, indentation + 1);
    tree_print_aux(cur->right, indentation + 1);
}
void tree_print(Tree* cur) {
    tree_print_aux(cur, 0);
}

/* Post-order where traverse is free!! */
void free_tree(Tree* cur) {
    if (cur == NULL) return;
    free_tree(cur->left);
    free_tree(cur->right);
    free(cur); /* Boom */
}

#endif
