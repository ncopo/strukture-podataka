#define _CRT_SECURE_NO_WARNINGS
#define ALLOCATION_ERROR (-1)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef Node* Position;

struct Node {
    int element;
    Position left;
    Position right;
};

Position addNode(Position root, int newElement);
Position minNode(Position root);
void printInOrder(Position root);
void printPreOrder(Position root);
void printPostOrder(Position root);
void printLevelOrder(Position root);
Position deleteElement(Position root, int element);
Position findElement(Position root, int element);
void freeTree(Position root);

int main() {
    Position root = NULL;

    printf("Unesi  element za  root node: ");
    int rootElement = 0;
    scanf("%d", &rootElement);

    root = addNode(root, rootElement);
    if (root == NULL) {
        printf("Error allocating memory for root node.\n");
        return ALLOCATION_ERROR;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1 - unesi element u stablo\n");
        printf("2 - Printaj elemente stabla\n");
        printf("3 - izbrisi element\n");
        printf("4 - nadi element\n");
        printf("5 - Exit\n");

        int choice = 0;
        printf("izaberi: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int newElement = 0;
            printf("unesi element: ");
            scanf("%d", &newElement);
            root = addNode(root, newElement);
        } else if (choice == 2) {
            printf("\nPrintaj menu:\n");
            printf("1 - po redu\n");
            printf("2 - Prije reda\n");
            printf("3 - Poslije reda\n");
            printf("4 - Level reda\n");

            int printChoice = 0;
            printf("Izaberi vrstu printanja: ");
            scanf("%d", &printChoice);

            switch (printChoice) {
                case 1:
                    printInOrder(root);
                    break;
                case 2:
                    printPreOrder(root);
                    break;
                case 3:
                    printPostOrder(root);
                    break;
                case 4:
                    printLevelOrder(root);
                    break;
                default:
                    printf("krivi odabir\n");
            }
        } else if (choice == 3) {
            int element = 0;
            printf("Unesi element da izbrises: ");
            scanf("%d", &element);
            root = deleteElement(root, element);
        } else if (choice == 4) {
            int element = 0;
            printf("Unesi element da pronadjes: ");
            scanf("%d", &element);
            Position found = findElement(root, element);
            if (found != NULL) {
                printf("Element %d nadje u stablu.\n", found->element);
            } else {
                printf("Element nije pronadjen.\n");
            }
        } else if (choice == 5) {
            printf("\nIzlazi iz programa\n");
            break;
        } else {
            printf("krivi odabir.\n");
        }
    }

    freeTree(root);
    return 0;
}

Position addNode(Position root, int newElement) {
    if (root == NULL) {
        root = (Position)calloc(1, sizeof(Node));
        if (root == NULL) {
            printf("greska allocating memoriju\n");
            return NULL;
        }
        root->element = newElement;
    } else if (newElement > root->element) {
        root->right = addNode(root->right, newElement);
    } else if (newElement < root->element) {
        root->left = addNode(root->left, newElement);
    }

    return root;
}

void printInOrder(Position root) {
    if (root == NULL) return;
    printInOrder(root->left);
    printf("%d ", root->element);
    printInOrder(root->right);
}

void printPreOrder(Position root) {
    if (root == NULL) return;
    printf("%d ", root->element);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(Position root) {
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->element);
}

void printLevelOrder(Position root) {
    if (root == NULL) return;

    Position* queue = malloc(100 * sizeof(Position));
    if (queue == NULL) {
        printf("Memorija allocation nije uspio za red.\n");
        return;
    }

    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Position current = queue[front++];
        printf("%d ", current->element);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }

    free(queue);
}

Position deleteElement(Position root, int element) {
    if (root == NULL) {
        printf("Element nije pronadjen.\n");
        return NULL;
    }

    if (element < root->element) {
        root->left = deleteElement(root->left, element);
    } else if (element > root->element) {
        root->right = deleteElement(root->right, element);
    } else {
        if (root->left != NULL && root->right != NULL) {
            Position temp = minNode(root->right);
            root->element = temp->element;
            root->right = deleteElement(root->right, root->element);
        } else {
            Position toDelete = root;
            if (root->left == NULL) {
                root = root->right;
            } else {
                root = root->left;
            }
            free(toDelete);
        }
    }

    return root;
}

Position minNode(Position root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Position findElement(Position root, int element) {
    while (root != NULL) {
        if (element < root->element) {
            root = root->left;
        } else if (element > root->element) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

void freeTree(Position root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
