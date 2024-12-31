//swali la kwanza 1:
#include <stdio.h>
struct node {
    struct node *left;
    struct node *right;
    int data;
};
struct node *root = NULL;
int search_bst(struct node *root, int key, int *count) {
    *count = 0;
    while (root != NULL) {
        printf("%d ", root->data);
        (*count)++;
        if (key == root->data) {
            return 1;
        } else if (key < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return 0;
}


