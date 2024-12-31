//swali la 6:
#include <stdio.h>
struct node {
    struct node *left;
    struct node *right;
    int data;
};
struct node *root = NULL;

struct node* delete_node_with_rotation(struct node *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = delete_node_with_rotation(root->left, key); 
    } else if (key > root->data) {
        root->right = delete_node_with_rotation(root->right, key); 
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        } else {
            struct node *temp = findMin(root->right);

            root->data = temp->data;

            root->right = delete_node_with_rotation(root->right, temp->data);

            if (root->left && root->left->data > root->data) {
                root = rightRotate(root);
            } else if (root->right && root->right->data < root->data) {
                root = leftRotate(root);
            }
        }
    }
    return root;
}
