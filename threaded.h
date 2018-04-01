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

/** Shamelessly lifted from:
    https://www.geeksforgeeks.org/threaded-binary-tree-insertion/
    because I didnt feel like hand-porting my Java OOPy version...
    Thanks G4G!!
*/
Tree* tree_insert(Tree* root, int data) {
    Tree* cur = root;
    Tree* parent = NULL;
    Tree* new_node;
    while (cur != NULL) {
        if (data == cur->data) {
            /* duplicate, so just dont do anything.*/
            return root;
        }
        parent = cur;

        if (cur->data > data) {
            if (!cur->left_thread) cur = cur->left;
            else break;
        } else {
            if (!cur->right_thread) cur = cur->right;
            else break;
        }
    }
    new_node = (Tree*) malloc(sizeof(Tree));
    new_node->data = data;
    new_node->left_thread = true;
    new_node->right_thread = true;

    if (parent == NULL) {
        new_node->left = NULL;
        new_node->right = NULL;
        root = new_node;
    } else if (parent->data > data) {
        new_node->left_thread = parent->left_thread;
        new_node->left = parent->left;
        new_node->right = parent;
        parent->left_thread = false;
        parent->left = new_node;
    } else {
        new_node->right_thread = parent->right_thread;
        new_node->left = parent;
        new_node->right = parent->right;
        parent->right_thread = false;
        parent->right = new_node;
    }
    return root;
}


Tree* tree_successor(Tree* node) {
    Tree* cur;

    /* fast path!*/
    if (node->right_thread) return node->right;

    /* else return leftmost child of right subtree!*/
    cur = node->right;
    while (!cur->left_thread) {
        cur = cur->left;
    }
    return cur;
}


void tree_print_aux(Tree* cur, int indentation) {
    if (cur == NULL) {
        return;
    }
    printf("%*c- %d\n", (indentation * 2), ' ', cur->data);
    if (!cur->left_thread) {
        tree_print_aux(cur->left, indentation + 1);
    }
    if (!cur->right_thread) {
        tree_print_aux(cur->right, indentation + 1);
    }
}
void tree_print(Tree* cur) {
    tree_print_aux(cur, 0);
}

#endif
