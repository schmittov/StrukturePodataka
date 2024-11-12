#include <stdio.h>
#include<stdlib.h>

typedef struct polynomial* position;
struct polynomial {
    int coefficient;
    int exponent;
    position next;
};

int input(position head, char* fileName);
int deleteZeroNode(position head);
int sumOfPolynomials(position headList, position headSum);
int productOfPolynomials(position headListFirst, position headListSecond, position headProduct);
int printList(position head);
int main()
{
    struct polynomial HeadFirst;
    struct polynomial HeadSecond;
    struct polynomial HeadSum;
    struct polynomial HeadProduct;

    input(&HeadFirst, "polynomialFirst.txt");
    input(&HeadSecond, "polynomialSecond.txt");

    printList(&HeadFirst);
    printList(&HeadSecond);

    sumOfPolynomials(&HeadFirst, &HeadSum);
    sumOfPolynomials(&HeadSecond, &HeadSum);
    printList(&HeadSum);

    productOfPolynomials(&HeadFirst, &HeadSecond, &HeadProduct);
    printList(&HeadProduct);

    return 0;
}

int input(position head, char* fileName)
{
    FILE* fp = NULL;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Greška kod otvaranja datoteke!\n");
        return 1;
    }

    int coefficient, exponent;
    while (fscanf(fp, "%d %d", &coefficient, &exponent) == 2)
    {
        position tempPrevious = head;
        position temp = head;

        while (temp->next != NULL && temp->next->exponent >= exponent)
        {
            temp = temp->next;
        }

        if (temp->exponent == exponent)
        {
            temp->coefficient += coefficient;

            if (temp->coefficient == 0)
            {
                deleteZeroNode(head);
            }
        }

        else
        {
            position newNode = (position)malloc(sizeof(struct polynomial));
            newNode->coefficient = coefficient;
            newNode->exponent = exponent;
            newNode->next = NULL;

            newNode->next = temp->next;
            temp->next = newNode;
        }

    }


    return 0;
}
int deleteZeroNode(position head)
{
    position temp = head;

    while (temp != NULL && temp->next != 0)
    {

        if (temp->next->coefficient == 0)
        {
            position toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
        }
        else
        {
            temp = temp->next;
        }

    }
}

int sumOfPolynomials(position headList, position headSum)
{
    position tempSum = headSum, tempList = headList;

    while (tempList->next != NULL)
    {
        while (tempSum->next != NULL && tempSum->next->exponent >= tempList->next->exponent)
        {
            tempSum = tempSum->next;
        }

        if (tempSum->exponent == tempList->next->exponent)
        {

            tempSum->coefficient += tempList->next->coefficient;
            if (tempSum->coefficient == 0)
            {
                deleteZeroNode(headSum);
            }
        }
        else
        {
            position newNode = (position)malloc(sizeof(struct polynomial));
            newNode->coefficient = tempList->next->coefficient;
            newNode->exponent = tempList->next->exponent;

            newNode->next = tempSum->next;
            tempSum->next = newNode;
        }



        tempList = tempList->next;
        tempSum = headSum;
    }

}
int productOfPolynomials(position headListFirst, position headListSecond, position headProduct)
{
    position tempFirst = headListFirst->next;
    position tempSecond = headListSecond;
    position tempProduct = headProduct;

    int exponent, coefficient;

    while (tempFirst->next != NULL)
    {
        tempSecond = headListSecond->next;
        while (tempSecond->next != NULL)
        {
            coefficient = (tempFirst->coefficient) * (tempSecond->coefficient);
            exponent = (tempFirst->exponent) + (tempSecond->exponent);


            position newNode = (position)malloc(sizeof(struct polynomial));
            newNode->coefficient = coefficient;
            newNode->exponent = exponent;
            newNode->next = NULL;

            newNode->next = tempProduct->next;
            tempProduct->next = newNode;


            tempSecond = tempSecond->next;
        }
        tempFirst = tempFirst->next;
    }
}
int printList(position head) {
    position temp = head->next;

    if (temp == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (temp != NULL) {
        if (temp->coefficient != 0)
        {
            printf("%dx^%d", temp->coefficient, temp->exponent);



            if (temp->next != NULL) {
                printf(" + ");
            }
        }
        temp = temp->next;
    }
    printf("\n");
}