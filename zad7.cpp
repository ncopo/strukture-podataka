#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DIR_LENGTH 256
#define MAX_COMMAND_LENGTH 256

typedef struct dir* Pos;

typedef struct dir {
    char name[MAX_DIR_LENGTH];
    Pos next;
    Pos child;
    Pos parent;
} Dir;

Dir Root = {
    .name = ":C",
    .next = NULL,
    .child = NULL,
    .parent = NULL
};

Pos current = &Root;

Pos CreateDirectory(char* name);
int Command();
int ConnectDirectory(char* name, Pos parent);
int ChangeDirectory(char* name);
int PrintDirectory(Pos current, int layer);
void PrintDirectoryElement(char* name);
int ReturnToPrev();

int main() {
    Command();
    return 0;
}

Pos CreateDirectory(char* name) {
    Pos NewDirectory = malloc(sizeof(Dir));
    if (!NewDirectory) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strncpy(NewDirectory->name, name, MAX_DIR_LENGTH);
    NewDirectory->parent = NULL;
    NewDirectory->child = NULL;
    NewDirectory->next = NULL;
    return NewDirectory;
}

int ConnectDirectory(char* name, Pos parent) {
    Pos New = CreateDirectory(name);
    if (!New) {
        printf("Failed to create new directory.\n");
        return EXIT_FAILURE;
    }

    Pos CurChild = parent->child;
    if (CurChild == NULL) {
        New->parent = parent;
        parent->child = New;
        return EXIT_SUCCESS;
    }

    while (CurChild->next) {
        CurChild = CurChild->next;
    }

    New->parent = parent;
    CurChild->next = New;
    return EXIT_SUCCESS;
}

int PrintDirectory(Pos current, int layer) {
    Pos temp = current->child;
    if (temp == NULL) {
        return EXIT_SUCCESS;
    }

    while (temp) {
        for (int i = 0; i < layer; i++)
            printf("\t");
        PrintDirectoryElement(temp->name);
        PrintDirectory(temp, layer + 1);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

void PrintDirectoryElement(char* name) {
    printf("[%s]\n", name);
}

int ChangeDirectory(char* name) {
    Pos temp = current->child;
    if (temp == NULL) {
        printf("No subdirectories found.\n");
        return EXIT_FAILURE;
    }

    while (temp) {
        if (strcmp(name, temp->name) == 0) {
            current = temp;
            return EXIT_SUCCESS;
        }
        temp = temp->next;
    }

    printf("Directory '%s' does not exist.\n", name);
    return EXIT_FAILURE;
}


int ReturnToPrev() {
    if (current->parent) {
        current = current->parent;
    } else {
        printf("You are already at the root directory.\n");
    }
    return EXIT_SUCCESS;
}


int Command() {
    int end = 0;
    char name[MAX_DIR_LENGTH] = { '\0' };
    char choice[MAX_COMMAND_LENGTH] = { '\0' };

    while (!end) {
        printf("\nChoose a command:\n");
        printf("1-md\n2-cd\n3-cd..\n4-dir\n5-exit\n");
        scanf("%s", choice);

        if (strcmp("md", choice) == 0) {
            printf("Enter name of new directory: ");
            scanf("%s", name);
            ConnectDirectory(name, current);
        } else if (strcmp("cd", choice) == 0) {
            printf("Enter name of directory to navigate to: ");
            PrintDirectory(current, 1);
            scanf("%s", name);
            ChangeDirectory(name);
        } else if (strcmp("cd..", choice) == 0) {
            ReturnToPrev();
        } else if (strcmp("dir", choice) == 0) {
            printf("\nCurrent Directory Tree:\n");
            PrintDirectory(current, 1);
        } else if (strcmp("exit", choice) == 0) {
            end = 1;
        } else {
            printf("Invalid command. Please try again.\n");
        }
    }
    return EXIT_SUCCESS;
}
