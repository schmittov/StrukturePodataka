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

int printList(position p);                              //A
int addNewElementOnStart(position p);                   //B
int addNewElementOnEnd(position p);                     //C
int addNewElementAfterOther(position p);                //D
int addNewElementBeforeOther(position p);               //E

int findElement(position p);                            //F
int deleteElement(position p);                          //G

int addElementsFromFile(position p, char* fileName);    //H
int addElementsIntoFile(position p, char* fileName);    //I

int sortListByLastName(position p);                     //J

int main()
{
    struct osoba Head;
    Head.next = NULL;

    char choice;


    while (1)
    {

        printf("Odaberi radnju\n");
        printf(" A -ispiši listu\n");
        printf(" B -dodaj element na poèetak liste\n");
        printf(" C -dodaj element na kraj liste\n");
        printf(" D -dodaj element u listu nakon odreðenog\n");
        printf(" E -dodaj element u listu prije odreðenog\n");
        printf(" F -naði element liste\n");
        printf(" G -izbriši element liste\n");
        printf(" H -dodaj elemente u listu iz datoteke\n");
        printf(" I -dodaj elemente liste u datoteku\n");
        printf(" J -sortiraj listu\n");

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
            addNewElementAfterOther(&Head);
            break;
        case 'E':
            addNewElementBeforeOther(&Head);
            break;
        case 'F':
            findElement(&Head);
            break;
        case 'G':
            deleteElement(&Head);
            break;
        case 'H':
            addElementsFromFile(&Head, "osobe.txt");
            break;
        case 'I':
            addElementsIntoFile(Head.next, "osobeUpis.txt");
            break;
        case 'J':
            sortListByLastName(&Head);
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
int addNewElementAfterOther(position p)
{
    char prezimeFind[30];
    printf("Unesi prezime");
    scanf("%s", prezimeFind);

    while (p != NULL && strcmp(p->prezime, prezimeFind) != 0)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("Element s prezimenom '%s' nije pronaðen.\n", prezimeFind);
        return -1;
    }

    position newElement = (position)malloc(sizeof(struct osoba));
    if (newElement == NULL) {
        printf("Greška pri alokaciji memorije\n");
        return -1;
    }

    printf("Unesi ime: ");
    scanf("%s", newElement->ime);
    printf("Unesi prezime: ");
    scanf("%s", newElement->prezime);
    printf("Unesi godinu roðenja: ");
    scanf("%d", &newElement->godinaRodenja);

    newElement->next = p->next;
    p->next = newElement;

    return 0;
}
int addNewElementBeforeOther(position p)
{
    char prezimeFind[30];
    printf("Unesi prezime");
    scanf("%s", prezimeFind);

    while (p != NULL && strcmp(p->next->prezime, prezimeFind) != 0)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        printf("Element s prezimenom '%s' nije pronaðen.\n", prezimeFind);
        return -1;
    }

    position newElement = (position)malloc(sizeof(struct osoba));
    if (newElement == NULL) {
        printf("Greška pri alokaciji memorije\n");
        return -1;
    }

    printf("Unesi ime: ");
    scanf("%s", newElement->ime);
    printf("Unesi prezime: ");
    scanf("%s", newElement->prezime);
    printf("Unesi godinu roðenja: ");
    scanf("%d", &newElement->godinaRodenja);

    newElement->next = p->next;
    p->next = newElement;

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
int addElementsIntoFile(position p, char* fileName)
{
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("Error with opening file\n");
        return -1;
    }

    while (p != NULL)
    {
        fprintf(fp, "%s\t%s\t%d\n", p->ime, p->prezime, p->godinaRodenja);
        p = p->next;
    }
    return 0;
    fclose(fp);

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
    printf("Unesi godinu ro?enja: ");
    scanf("%d", &q->godinaRodenja);

    q->next = p->next;
    p->next = q;

    return 0;
}

int sortListByLastName(position p)
{
    position j, prev_j, temp, end;
    end = NULL;

    while (p->next != end)
    {
        prev_j = p;
        j = p->next;

        while (j->next != end)
        {
            if (strcmp(j->prezime, j->next->prezime) > 0)
            {
                temp = j->next;
                prev_j->next = temp;
                j->next = temp->next;
                temp->next = j;

                j = temp;
            }

            prev_j = j;
            j = j->next;
        }
        end = j;

    }
}