//swali la 3:
#include <stdio.h>
struct node {
    struct node *left;
    struct node *right;
    int data;
};
struct node *root = NULL;
void pre_order_iterative_with_sum(struct node *root, int *sum) {
    *sum = 0;
    if (root == NULL) return;
    struct node *current;
    struct stack *s = create_stack();
    push(s, root);
    while (!is_empty(s)) {
        current = pop(s);
        printf("%d ", current->data);
        *sum += current->data;
        if (current->right) push(s, current->right);
        if (current->left) push(s, current->left);
    }
}
