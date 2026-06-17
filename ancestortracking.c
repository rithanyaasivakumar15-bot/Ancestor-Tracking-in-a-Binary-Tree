#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} NODE;

// Function to safely read an integer
int getInteger() {
    int num;
    char ch;

    while (1) {
        if (scanf("%d", &num) == 1) {
            return num;   // Valid integer
        }

        printf("Invalid input! Please enter a number: ");

        // Clear invalid input from buffer
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

// Create new node
NODE* createNode(int data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Find a node by value
NODE* findNode(NODE* root, int data) {
    if (root == NULL)
        return NULL;

    if (root->data == data)
        return root;

    NODE* left = findNode(root->left, data);

    if (left != NULL)
        return left;

    return findNode(root->right, data);
}

// Insert child under parent
void insertNode(NODE* root, int parentData, int childData, char side) {
    NODE* parent = findNode(root, parentData);

    if (parent == NULL) {
        printf("Parent not found!\n");
        return;
    }

    if (side == 'L' || side == 'l') {
        if (parent->left == NULL) {
            parent->left = createNode(childData);
            printf("Node inserted successfully!\n");
        } else {
            printf("Left child already exists!\n");
        }
    }
    else if (side == 'R' || side == 'r') {
        if (parent->right == NULL) {
            parent->right = createNode(childData);
            printf("Node inserted successfully!\n");
        } else {
            printf("Right child already exists!\n");
        }
    }
    else {
        printf("Invalid side! Enter L or R.\n");
    }
}

// Inorder traversal
void inorder(NODE* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Print ancestors
int printAncestors(NODE* root, int target) {
    if (root == NULL)
        return 0;

    if (root->data == target)
        return 1;

    if (printAncestors(root->left, target) ||
        printAncestors(root->right, target)) {
        printf("%d ", root->data);
        return 1;
    }

    return 0;
}

// Free memory
void freeTree(NODE* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Main menu
int main() {
    NODE* root = NULL;
    int choice, data, parent, child, target;
    char side;

    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Create root node\n");
        printf("2. Insert node under parent\n");
        printf("3. Print inorder traversal\n");
        printf("4. Print ancestors of a node\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        choice = getInteger();

        switch (choice) {

            case 1:
                if (root != NULL) {
                    printf("Root already exists!\n");
                } else {
                    printf("Enter root data: ");
                    data = getInteger();

                    root = createNode(data);
                    printf("Root created successfully!\n");
                }
                break;

            case 2:
                if (root == NULL) {
                    printf("Create root first!\n");
                    break;
                }

                printf("Enter parent data: ");
                parent = getInteger();

                printf("Enter child data: ");
                child = getInteger();

                printf("Enter side (L/R): ");
                scanf(" %c", &side);

                insertNode(root, parent, child, side);
                break;

            case 3:
                if (root == NULL) {
                    printf("Tree is empty. Create root first!\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty. Create root first!\n");
                    break;
                }

                printf("Enter node to find ancestors: ");
                target = getInteger();

                if (target == root->data) {
                    printf("Root node has no ancestors!\n");
                    break;
                }

                printf("Ancestors: ");
                if (!printAncestors(root, target))
                    printf("Node not found!");

                printf("\n");
                break;

            case 5:
                freeTree(root);
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}