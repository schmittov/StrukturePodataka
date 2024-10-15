/*
	1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
	zapisanih u datoteci. 
	Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
	studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
	prezime, apsolutni i relativni broj bodova.
	Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
	relatvan_br_bodova = br_bodova/max_br_bodova*100
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024

typedef struct {
    char ime[10];
    char prezime[10];
    int bodovi;
} student;

int rowCounter(char* fileName);
void studentReader(student* studenti, int brojStudenata, char* fileName, int* maxBodovi);
void printStudents(student* studenti, int brojStudenata, int maxBodovi);

int main()
{
    int maxBodovi = 0;
    char* fileName = "rezultati.txt";

    int brojStudenata = rowCounter(fileName);

    student* studenti = malloc(brojStudenata * sizeof(student));
    if (studenti == NULL) {
        printf("Error allocating memory!\n");
        return ERROR_OPENING_FILE;
    }

    studentReader(studenti, brojStudenata, fileName, &maxBodovi);
    printStudents(studenti, brojStudenata, maxBodovi);

    free(studenti);

    return 0;
}

int rowCounter(char* fileName)
{
    int counter = 0;
    char buffer[BUFFER_SIZE];
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return ERROR_OPENING_FILE;
    }

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        counter++;
    }

    fclose(fp);
    return counter;
}

void studentReader(student* studenti, int brojStudenata, char* fileName, int* maxBodovi)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < brojStudenata; i++) {
        fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        if (studenti[i].bodovi > *maxBodovi) {
            *maxBodovi = studenti[i].bodovi;
        }
    }
    fclose(fp);
}

void printStudents(student* studenti, int brojStudenata, int maxBodovi)
{
    printf("Ime\tPrezime\t\tApsolutni bodovi\tRelativni bodovi\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < brojStudenata; i++) {
        float relativniBodovi = ((float)studenti[i].bodovi / maxBodovi) * 100;
        printf("%s\t%s\t\t%d\t\t\t%.2f%%\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativniBodovi);
    }
}