#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Directory {
    char name[100];
    struct Directory* parent;
    struct Directory* subdirectories;
    struct Directory* next;
} Directory;

Directory* createDirectory(char* name, Directory* parent) {
    Directory* newDir = (Directory*)malloc(sizeof(Directory));
    strcpy(newDir->name, name);
    newDir->parent = parent;
    newDir->subdirectories = NULL;
    newDir->next = NULL;
    return newDir;
}

void makeDirectory(Directory* current, char* name) {
    Directory* newDir = createDirectory(name, current);
    if (!current->subdirectories) {
        current->subdirectories = newDir;
    }
    else {
        Directory* temp = current->subdirectories;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newDir;
    }
}

Directory* changeDirectory(Directory* current, char* name) {
    if (strcmp(name, "..") == 0) {
        return current->parent ? current->parent : current;
    }

    Directory* temp = current->subdirectories;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    printf("Direktorij '%s' ne postoji!\n", name);
    return current;
}

void listDirectory(Directory* current) {
    printf("Sadržaj direktorija '%s':\n", current->name);
    Directory* temp = current->subdirectories;
    if (!temp) {
        printf("(prazno)\n");
    }
    else {
        while (temp) {
            printf("%s\n", temp->name);
            temp = temp->next;
        }
    }
}

int main() {
    char name[100];
    int command;
    Directory* root = createDirectory("root", NULL);
    Directory* current = root;



    do
    {
        system("clear");
        printf("Trenutni direktorij: %s\n", current->name);
        printf("Odaberi opciju.\n");
        printf("1- md\n");
        printf("2- cd dir\n");
        printf("3- cd..\n");
        printf("4- dir\n");
        printf("5- izlaz\n");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            printf("Unesi ime direktorija.\n");
            scanf("%s", name);
            makeDirectory(current, name);
            break;
        case 2:
            printf("Unesi ime direktorija.\n");
            scanf("%s", name);
            current = changeDirectory(current, name);
            break;
        case 3:
            current = changeDirectory(current, "..");
            break;
        case 4:
            listDirectory(current);
            printf("Pritisni bilo koju tipku za nastaviti.");

            while (getchar() != '\n');
            getchar();

            break;

        case 5:
            break;

        default:
            printf("Nepostojeæa naredba!");
            break;
        }


    } while (command != 5);

    return 0;
}