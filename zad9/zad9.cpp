﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node* position;
typedef struct Node {
    int value;
    position left;
    position right;
} Node;

position create_element(int value) {
    position new = (position)malloc(sizeof(Node));
    if (new == NULL) {
        printf("Greška pri alokaciji memorije.\n");
        return NULL;
    }

    new->value = value;
    new->left = NULL;
    new->right = NULL;

    return new;
}


position insert_element(position root, int value) {
    if (root == NULL) {
        return create_element(value);
    }

    if (value >= root->value) {
        root->left = insert_element(root->left, value);
    } else {
        root->right = insert_element(root->right, value);
    }

    return root;
}


void inorder_stablo(position root) {
    if (root != NULL) {
        inorder_stablo(root->left);
        printf("%d ", root->value);
        inorder_stablo(root->right);
    }
}


int replace(position current) {
    if (current == NULL) {
        return 0;
    }

    int old_value = current->value;

    current->value = replace(current->left) + replace(current->right);

    return old_value + current->value;
}

int main() {
    position root = NULL;

    root = insert_element(root, 2);
    root = insert_element(root, 5);
    root = insert_element(root, 7);
    root = insert_element(root, 8);
    root = insert_element(root, 11);
    root = insert_element(root, 1);
    root = insert_element(root, 4);
    root = insert_element(root, 2);
    root = insert_element(root, 3);
    root = insert_element(root, 7);

   
    printf("Stablo prije zamjene:\n");
    inorder_stablo(root);

    
    replace(root);

    
    printf("\nStablo nakon zamjene:\n");
    inorder_stablo(root);

    printf("\n");

    return 0;
}