﻿#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Greška: Nema dovoljno memorije!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

void inorderToFile(Node* root, FILE* file) {
    if (root != NULL) {
        inorderToFile(root->left, file);
        fprintf(file, "%d ", root->value);
        inorderToFile(root->right, file);
    }
}

void writeToFile(Node* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Greška pri otvaranju datoteke %s\n", filename);
        return;
    }
    inorderToFile(root, file);
    fclose(file);
}

int replace(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftSum = replace(root->left);
    int rightSum = replace(root->right);

    int currentValue = root->value;

    root->value = leftSum + rightSum;

    return currentValue + root->value;
}

int main() {
    Node* root = NULL;
    srand((unsigned)time(0));  

    for (int i = 0; i < 10; i++) {
        int num = rand() % 81 + 10;  
        root = insert(root, num);
    }

    printf("Inorder prolazak originalnog stabla:\n");
    inorder(root);
    printf("\n");

    writeToFile(root, "original_tree.txt");

    replace(root);

    printf("Inorder prolazak modificiranog stabla:\n");
    inorder(root);
    printf("\n");

    writeToFile(root, "modified_tree.txt");

    printf("Originalno i modificirano stablo su upisani u datoteke 'original_tree.txt' i 'modified_tree.txt'.\n");

    return 0;
}
