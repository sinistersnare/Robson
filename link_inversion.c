/*
    A standalone C program to demonstrate the link_inversion method for traversing binary trees.

    To run, simply call gcc on it:

    `$ gcc link_inversion.c -o inv.x`
    `$ ./inv.x 1 3 2 4 5
*/

#include <stdio.h>
#include <stdlib.h>


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
    bool follow_right;
} Tree;


void traverse(Tree*);

Tree* tree_insert(Tree* cur, int data) {
    if (cur == NULL) {
        Tree* new_node = malloc(sizeof(Tree));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->follow_right = 0;
        return new_node;
    }
    if (cur->data > data) {
        cur->left = tree_insert(cur->left, data);
    } else if (cur->data < data) {
        cur->right = tree_insert(cur->right, data);
    }
    return cur; // Tree = Set, swallow duplicates.
}

void visit(Tree* node) {
    printf("%d\n", node->data);
}


// TODO: implement ascendFromRight and ascendFromLeft
// seems it doesnt work when a tree just goes rightwards?
void traverse(Tree* cur) {
    if (cur == NULL) return;

    Tree* prev = NULL;

    while (!((cur->follow_right == 1) && (prev == NULL))) {

        // descend left as much as possible.
        while (cur != NULL) {
            visit(cur); // preorder
            cur->follow_right = 0;
            // descend to the left
            Tree* temp = prev;
            prev = prev->left;
            temp->left = cur;
            cur = temp;
        }

        while (prev != NULL && prev->follow_right == 1) {
            // ascend from the right.
            Tree* old_cur = cur;
            Tree* old_prev = prev;
            cur = prev;
            prev = prev->right;
            old_prev->right = old_cur;
            // visit(cur) // postorder
        }

        if (prev == NULL) {
            return;
        } else {
            // ascend from the left
            Tree* old_cur = cur;
            Tree* old_prev = prev;
            cur = prev;
            prev = prev->left;
            old_prev->left = old_cur;

            // visit(cur) // inorder
            cur->follow_right = 1;

            // descend to the right
            Tree* temp = prev;
            prev = prev->right;
            temp->right = cur;
            cur = temp;
        }
    }
}

int main(int argc, const char** argv) {
    Tree* t;
    int i;

    if (argc < 2) {
        printf("Link Inversion takes any amount of int arguments to add to tree in given order.");
        return 1;
    }

    t = NULL;

    for (i=1; i < argc; i++) {
        t = tree_insert(t, atoi(argv[i]));
    }

    traverse(t);
}


