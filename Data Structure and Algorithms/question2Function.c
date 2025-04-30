//swali la 2:
#include <stdio.h>
struct node {
    struct node *left;
    struct node *right;
    int data;
};
struct node *root = NULL;
int find_height_and_diameter(struct node *root, int *diameter) {
    if (root == NULL) return 0;
    int left_height = find_height_and_diameter(root->left, diameter);
    int right_height = find_height_and_diameter(root->right, diameter);
    int height = 1 + (left_height > right_height ? left_height : right_height);
    int path_length = left_height + right_height;
    if (path_length > *diameter) {
        *diameter = path_length;
    }
    return height;
}


