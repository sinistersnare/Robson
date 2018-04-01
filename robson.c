#include <stdio.h>
#include <stdlib.h>

#include "bintree.h"
#include "robstack.h"


/* At this point in execution, we have reached a leaf, and we must
// pop back up the inner_stack of inverted links so that we can
// find find a new subtree to traverse.
// We know when we have reached an appropriate subtree when
// the leaf_stack's top is the current node. We then return
// the current node, so it traverse its tree. */
node* next_subtree(node* m, inner_stack* inner, leaf_stack* leaf) {
    node* p;
    bool found;
    ls_set_avail(leaf, m);
    p = m;
    found = false;
    while (!found && !is_empty(inner)) {
        if (ls_top(leaf) == is_top(inner)) {
            /* We have just popped up from a right-subtree
            // and can keep poppin' right on up! */
            ls_pop(leaf);
            p = is_top(inner);
            is_pop(inner);
        } else {
            if (((is_top(inner))->left) == NULL) {
                /* popped up from right, but its not special,
                // as there just was never a left child to traverse.
                // keep poppin' */
                p = is_top(inner);
                is_pop(inner);
            } else {
                if ((is_top(inner))->right) {
                    /* Its popping up the tree, and it has found a
                    // right subtree to traverse!!!
                    // exchange sets the current pointer to the right
                    // subtree. In the example we are going up the 3 subtree.
                    // the ls_push call marks that fact that we
                    // are going down the right subtree of top(inner).
                    //
                    //    p=3           p=7
                    //     5      ->     5
                    //    3 7           3 7
                    // */
                    ls_push(leaf, is_top(inner));
                    p = is_exchange(inner, p);
                    found = true;
                } else {
                    /* popped up from left, keep on going til you hit something good. */
                    p = is_top(inner);
                    is_pop(inner);
                }
            }
        }
    }
    if (is_empty(inner)) {
        return NULL;
    } else {
        return p;
    }
}

void robson_traversal(node* root, void (*process)(node *)) {
    inner_stack* ins;
    leaf_stack* lfs;
    node* cur;

    is_make(&ins, root);
    ls_make(&lfs);
    cur = root;
    /* this loop simply pushes down the tree repeatedly.
    // If it doesnt have a left child to push, but has a right
    // it will push to the right, and link it that way.
    // Once a leaf is found, we must start popping, to find a new subtree
    // to find a new subtree, when we are propagating up,
    // if we find that the next node to visit has a right child,
    // we traverse it, UNLESS our leaf_stack has that element at its top.
    // if that is the case, then we just came from that spot, and we should
    // therefore keep going up. */
    while (cur) {
        process(cur);
        if (cur->left) {
            is_push(ins, cur);
            cur = cur->left;
        } else if (cur->right) {
            is_push(ins, cur);
            cur = cur->right;
        } else {
            cur = next_subtree(cur, ins, lfs);
        }
    }
}

void process(node* n) {
    printf("%d\n", n->data);
}

int main(int argc, const char** argv) {

    tree* t = tree_new();
    /*tree_make(&t);*/

    if (argc > 1) {
        int i;
        for (i=1; i < argc; i++) {
            const char* arg = argv[i];
            int val = atoi(arg);
            printf("inserted %d\n", val);
            tree_insert(t, val);
        }
    } else {
        /* 1 2 5 4 7 1 3 8 10 1 11*/
        tree_insert(t, 1);
        tree_insert(t, 3);
        tree_insert(t, 2);
        tree_insert(t, 4);
        tree_insert(t, 5);
    }
    tree_print(t);
    robson_traversal(t->root, process);

    return 0;
}
