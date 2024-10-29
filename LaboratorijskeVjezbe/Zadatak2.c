#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct osoba* position;
struct osoba {
    char ime[10];
    char prezime[10];
    int godinaRodenja;
    position next;
};
int addNewElement(position p);
int printList(position p);                          //A
int addNewElementOnStart(position p);               //B
int addNewElementOnEnd(position p);                 //C
int findElement(position p);                        //D
int deleteElement(position p);                      //E
int addElementsFromFile(position p, char* fileName); //F
int main()
{
    struct osoba Head;
    Head.next = NULL;

    char choice;


    while (1)
    {

        printf("Odaberi radnju\n");
        printf(" A- ispiši listu\n B- dodaj element na poèetak liste\n C- dodaj element na kraj liste\n D-pronaði element\n E-izbriši element\n F-upiši podatke iz datoteke\n X-izaði\n");

        scanf(" %c", &choice);
        choice = toupper(choice);
        switch (choice)
        {
        case 'A':
            printList(Head.next);
            break;
        case 'B':
            addNewElementOnStart(&Head);
            break;
        case 'C':
            addNewElementOnEnd(&Head);
            break;
        case 'D':
            findElement(&Head);
            break;
        case 'E':
            deleteElement(&Head);
            break;
        case 'F':
            addElementsFromFile(&Head, "osobe.txt");
            break;
        case 'X':
            return 0;
            break;
        }
        while (getchar() != '\n');
        getchar();
        system("clear");
    }

    return 0;
}


int printList(position p)
{
    while (p != NULL)
    {
        printf("%s %s %d \n", p->ime, p->prezime, p->godinaRodenja);
        p = p->next;
    }
    return 0;
}
int addNewElementOnStart(position p)
{
    addNewElement(p);
    return 0;
}

int addNewElementOnEnd(position p)
{
    while (p->next != NULL)
    {
        p = p->next;
    }
    addNewElement(p);

    return 0;
}

int findElement(position p)
{
    char tempPrezime[30];
    printf("Unesi prezime: ");
    scanf("%s", tempPrezime);

    while (p != NULL && strcmp(tempPrezime, p->prezime) != 0)
    {
        p = p->next;
    }

    printf("%s %s %d \n", p->ime, p->prezime, p->godinaRodenja);
}
int deleteElement(position p)
{
    position q = NULL;
    char tempPrezime[30];
    printf("Unesi prezime osobe:");
    scanf("%s", tempPrezime);

    while (p->next != NULL && strcmp(tempPrezime, p->prezime) != 0)
    {
        q = p;
        p = p->next;
    }
    if (q != NULL && strcmp(tempPrezime, p->prezime) == 0)
    {
        p = q->next;
        q->next = p->next;
        free(p);
    }
    return 0;
}
int addElementsFromFile(position p, char* fileName) {

    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error with opening file\n");
        return -1;
    }

    while (1)
    {
        while (p->next != NULL)
        {
            p = p->next;
        }

        position q = NULL;
        q = (position)malloc(sizeof(struct osoba));
        if (q == NULL) {
            printf("Error with malloc\n");
            fclose(fp);
            return -1;
        }

        if (fscanf(fp, "%s %s %d", q->ime, q->prezime, &q->godinaRodenja) != 3)
        {
            free(q);
            break;
        }

        q->next = p->next;
        p->next = q;
    }
    fclose(fp);
    return 0;
}
int addNewElement(position p)
{
    position q = NULL;
    q = (position)malloc(sizeof(struct osoba));
    if (q == NULL)
    {
        printf("Error with malloc\n");
        return -1;
    }
    printf("Unesi ime: ");
    scanf("%s", q->ime);
    printf("Unesi prezime: ");
    scanf("%s", q->prezime);
    printf("Unesi godinu roðenja: ");
    scanf("%d", &q->godinaRodenja);

    q->next = p->next;
    p->next = q;

    return 0;
}