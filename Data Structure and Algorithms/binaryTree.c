#include <stdio.h>
#include <stdlib.h>

// Define the structure of the node
struct node {
    struct node *left;
    struct node *right;
    int data;
};

// Function to insert a node into the binary search tree
struct node* insert(struct node *root, int info) {
    if (root == NULL) {
        struct node *newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = info;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (info < root->data) {
        root->left = insert(root->left, info);
    } else {
        root->right = insert(root->right, info);
    }
    return root;
}

// Function to search for a node in the tree
struct node* search(struct node *root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Function to find the minimum value in the tree
struct node* findMin(struct node *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to find the maximum value in the tree
struct node* findMax(struct node *root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Function to delete a node from the binary search tree
struct node* delete(struct node *root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = delete(root->left, key);
    } else if (key > root->data) {
        root->right = delete(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: get the in-order successor (smallest in the right subtree)
        struct node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Function for in-order traversal
void inorderTraversal(struct node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function for pre-order traversal
void preOrderTraversal(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Function for post-order traversal
void postOrderTraversal(struct node *root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Main function for testing
int main() {
    struct node *root = NULL;

    // Insert nodes into the BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preOrderTraversal(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postOrderTraversal(root);
    printf("\n");

    // Search for a key
    int key = 40;
    struct node *found = search(root, key);
    if (found != NULL) {
        printf("Key %d found in the tree.\n", key);
    } else {
        printf("Key %d not found in the tree.\n", key);
    }

    // Find the minimum and maximum values
    struct node *minNode = findMin(root);
    struct node *maxNode = findMax(root);
    printf("Minimum value in the tree: %d\n", minNode->data);
    printf("Maximum value in the tree: %d\n", maxNode->data);

    // Delete a node
    int delKey = 30;
    root = delete(root, delKey);
    printf("Tree after deleting %d (in-order): ", delKey);
    inorderTraversal(root);
    printf("\n");

    return 0;
}

