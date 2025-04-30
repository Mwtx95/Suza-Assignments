//swali la 4:
#include <stdio.h>
struct node {
    struct node *left;
    struct node *right;
    int data;
};
struct node *root = NULL;
int in_order_iterative_with_balance_check(struct node *root) {
    struct stack *s = create_stack();
    struct stack *height_stack = create_stack();
    int left_height, right_height;
    while (!is_empty(s) || root != NULL) {
        while (root != NULL) {
            push(s, root);
            root = root->left;
        }
        root = pop(s);
        left_height = root->left ? root->left->data : 0;
        right_height = root->right ? root->right->data : 0;
        if (abs(left_height - right_height) > 1) return 0;
        root = root->right;
    }
    return 1;
}
