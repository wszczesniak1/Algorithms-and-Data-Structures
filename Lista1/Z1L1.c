#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct nodeTwo
{
    int dataTwo;
    struct nodeTwo *next;
};

struct node *front = NULL;
struct node *rear = NULL;
struct nodeTwo *top = NULL;


void display();
void enqueue(int);
void displayStack();
void push(int);

int main() {
    printf("Dodaję elementy do kolejki FIFO \n");

    for(int i = 0; i < 100; i++) {
        enqueue(i);
        printf("%d", i);
        printf( " ");
    }
    printf("\nPobieram elementy z kolejki FIFO\n");
    display();
    printf(" \n");

    printf("Dodaję elementy do kolejki LIFO \n");

    for(int i = 0; i < 100; i++) {
        push(i);
        printf("%d", i);
        printf( " ");
    }
    printf("\nPobieram elementy z kolejki LIFO\n");
    displayStack();
    printf(" \n");


}

void enqueue(int item) {
    struct node *nptr = malloc(sizeof(struct node));
    nptr->data = item;
    nptr->next = NULL;
    if (rear == NULL)
    {
        front = nptr;
        rear = nptr;
    }
    else
    {
        rear->next = nptr;
        rear = rear->next;
    }
}

void display() {
    struct node *temp;
    temp = front;
    printf(" ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

void displayStack() {

    struct nodeTwo *temp;
    temp = top;
    printf(" ");
    while (temp != NULL)
    {
        printf("%d ", temp->dataTwo);
        temp = temp->next;
    }
}

void push(int item) {
    struct nodeTwo *nptr = malloc(sizeof(struct nodeTwo));
    nptr->dataTwo = item;
    nptr->next = top;
    top = nptr;
}
