﻿#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct _stack;
typedef struct _stack* Position;
typedef struct _stack {
    int El;
    Position Next;
} stack;


int Push(Position head, int element);
int Pop(Position head);
int Evaluate(Position head);
int Sum(Position head);
int Difference(Position head);
int Product(Position head);
int Quotient(Position head);

int main() {
    stack Head = { .El = 0, .Next = NULL }; 

    if (Evaluate(&Head) != 0) {
        printf("Evaluacija nije uspela!\n");
        return EXIT_FAILURE;
    }

    if (Head.Next != NULL) { 
        printf("Rezultat je: %d\n", Head.Next->El);
    } else {
        printf("Stek je prazan.\n");
    }

    return EXIT_SUCCESS;
}


int Evaluate(Position head) {
    FILE* fp = fopen("postfix.txt", "r");  
    char operation[15];

    if (fp == NULL) {
        printf("Otvaranje datoteke nije uspelo!\n");
        return 1;
    }

    while (fscanf(fp, "%s", operation) != EOF) {
        int num = 0;
        if (sscanf(operation, "%d", &num) == 1) { 
            if (Push(head, num) != 0) {
                fclose(fp);
                return 1;
            }
        } else { 
            if (strcmp(operation, "+") == 0) {
                Sum(head);
            } else if (strcmp(operation, "-") == 0) {
                Difference(head);
            } else if (strcmp(operation, "*") == 0) {
                Product(head);
            } else if (strcmp(operation, "/") == 0) {
                if (Quotient(head) != 0) {
                    fclose(fp);
                    return 1;
                }
            } else {
                printf("Nepoznata operacija: %s\n", operation);
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    return 0;
}


int Push(Position head, int element) {
    Position newElement = (Position)malloc(sizeof(stack));
    if (newElement == NULL) {
        printf("Alokacija memorije nije uspela!\n");
        return 1;
    }

    newElement->El = element;
    newElement->Next = head->Next;
    head->Next = newElement;

    return 0;
}


int Pop(Position head) {
    if (head->Next == NULL) {
        printf("Stek je prazan!\n");
        return -1;
    }

    Position temp = head->Next;
    int element = temp->El;

    head->Next = temp->Next;
    free(temp);

    return element;
}

int Sum(Position head) {
    int firstNum = Pop(head);
    int secondNum = Pop(head);

    if (firstNum == -1 || secondNum == -1) return 1;

    return Push(head, secondNum + firstNum);
}


int Difference(Position head) {
    int firstNum = Pop(head);
    int secondNum = Pop(head);

    if (firstNum == -1 || secondNum == -1) return 1;

    return Push(head, secondNum - firstNum);
}


int Product(Position head) {
    int firstNum = Pop(head);
    int secondNum = Pop(head);

    if (firstNum == -1 || secondNum == -1) return 1;

    return Push(head, secondNum * firstNum);
}


int Quotient(Position head) {
    int firstNum = Pop(head);
    int secondNum = Pop(head);

    if (firstNum == -1 || secondNum == -1) return 1;

    if (firstNum == 0) {
        printf("Deljenje nulom nije dozvoljeno!\n");
        return 1;
    }

    return Push(head, secondNum / firstNum);
}