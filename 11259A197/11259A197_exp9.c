 
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int value) {
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to insert a node into BST
struct Node *insert(struct Node *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Duplicate value %d ignored.\n", value);
    }

    return root;
}

// In-order traversal: Left, Root, Right
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Pre-order traversal: Root, Left, Right
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Post-order traversal: Left, Right, Root
void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to search for a value in BST
struct Node *search(struct Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }

    return search(root->right, value);
}

// Function to find the smallest node
struct Node *findMin(struct Node *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

// Function to find the largest node
struct Node *findMax(struct Node *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {
        root = root->right;
    }

    return root;
}

// Function to count total nodes
int countNodes(struct Node *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

// Function to calculate the height of the tree
int height(struct Node *root) {
    int leftHeight, rightHeight;

    if (root == NULL) {
        return 0;
    }

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }

    return rightHeight + 1;
}

// Function to display the tree traversals
void displayTraversals(struct Node *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    printf("\nIn-order Traversal: ");
    inorder(root);

    printf("\nPre-order Traversal: ");
    preorder(root);

    printf("\nPost-order Traversal: ");
    postorder(root);

    printf("\n");
}

// Function to free allocated memory
void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node *root = NULL;
    struct Node *result;
    struct Node *temp;

    int n, i, value, choice;

    printf("Enter number of nodes: ");

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter %d values:\n", n);

    for (i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input.\n");
            freeTree(root);
            return 1;
        }

        root = insert(root, value);
    }

    do {
        printf("\n===== BINARY SEARCH TREE MENU =====\n");
        printf("1. Insert a node\n");
        printf("2. In-order traversal\n");
        printf("3. Pre-order traversal\n");
        printf("4. Post-order traversal\n");
        printf("5. Display all traversals\n");
        printf("6. Search an element\n");
        printf("7. Find minimum element\n");
        printf("8. Find maximum element\n");
        printf("9. Count total nodes\n");
        printf("10. Find height of tree\n");
        printf("11. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");

                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    freeTree(root);
                    return 1;
                }

                result = search(root, value);

                if (result != NULL) {
                    printf("Duplicate value. Node not inserted.\n");
                } else {
                    root = insert(root, value);
                    printf("Node inserted successfully.\n");
                }
                break;

            case 2:
                printf("In-order Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                printf("Pre-order Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 4:
                printf("Post-order Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 5:
                displayTraversals(root);
                break;

            case 6:
                printf("Enter value to search: ");

                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    freeTree(root);
                    return 1;
                }

                result = search(root, value);

                if (result != NULL) {
                    printf("%d found in the BST.\n", value);
                } else {
                    printf("%d not found in the BST.\n", value);
                }
                break;

            case 7:
                temp = findMin(root);

                if (temp == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Minimum element: %d\n", temp->data);
                }
                break;

            case 8:
                temp = findMax(root);

                if (temp == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Maximum element: %d\n", temp->data);
                }
                break;

            case 9:
                printf("Total nodes: %d\n", countNodes(root));
                break;

            case 10:
                printf("Height of tree: %d\n", height(root));
                break;

            case 11:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 11);

    freeTree(root);

    return 0;
}
