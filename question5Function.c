//swali la 5:
#include <stdio.h>
struct node {
    struct node *left;
    struct node *right;
    int data;
};
struct node *root = NULL;
void post_order_iterative_with_deletion_count(struct node *root, int *delete_count) {
    *delete_count = 0;

    if (root == NULL) {
        return; //
    }

    struct node *stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 >= 0) {
        struct node *current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL) {
            stack1[++top1] = current->left;
        }
        if (current->right != NULL) {
            stack1[++top1] = current->right;
        }
    }

    while (top2 >= 0) {
        struct node *current = stack2[top2--];
        if (current->left == NULL && current->right == NULL) {
            (*delete_count)++;
        }
        free(current);
    }
}
