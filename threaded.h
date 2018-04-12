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

int tree_size(Tree* cur) {
    if (cur == NULL) return 0;
    return 1 + tree_size(cur->left) + tree_size(cur->right);
}

int _tree_height_aux(Tree* cur, int level) {
    int lh, rh;
    if (t == NULL) return level;
    lh = _tree_height_aux(t->left) + 1;
    rh = _tree_height_aux(t->right) + 1;
    return lh > rh ? lh : rh;
}
int tree_height(Tree* t) {
    if (t == NULL) {
        return 0;
    }
    _tree_height_aux(t, -1);
}

void _tree_print_aux(Tree* cur, int indentation) {
    if (cur == NULL) {
        return;
    }
    printf("%*c- %d\n", (indentation * 2), ' ', cur->data);
    if (!cur->left_thread) {
        _tree_print_aux(cur->left, indentation + 1);
    }
    if (!cur->right_thread) {
        _tree_print_aux(cur->right, indentation + 1);
    }
}
void tree_print(Tree* cur) {
    _tree_print_aux(cur, 0);
}

/* Post-order where traverse is free!! */
void free_tree(Tree* cur) {
    if (cur == NULL) return;
    free_tree(cur->left);
    free_tree(cur->right);
    free(cur); /* Boom */
}

#endif
