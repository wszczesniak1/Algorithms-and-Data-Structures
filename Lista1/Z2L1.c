#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node *next;
};

typedef struct {
    struct node *start;
    struct node *end;
} list;

void add(int,list*);
void display(list*);
void search(int, list*);
void merge(list*, list*);


int main() {
    srand(time(NULL));
    list lista1;
    list lista2;
    list lista3;
    (&lista1)->start = NULL;
    (&lista2)->start = NULL;
    (&lista3)->start = NULL;

    for(int i = 0; i < 10000; i++) {
        int random = rand() % 1000;
        add(random, &lista1);
    }

    printf("\nSprawdzam średnie czasy\n");

    double average0 = 0;
    clock_t t0;
    for(int i = 0; i < 10000; i++) {
        t0 = clock();
        search(5000, &lista1);
        t0 = clock() - t0;
        
        average0 = average0 + t0;
    }
    average0 = (average0/10000.0)/CLOCKS_PER_SEC;
    printf("%f  dla połowy listy\n", average0);

    double average = 0;
    clock_t t;
    for(int i = 0; i < 10000; i++) {
        t = clock();
        search(2000, &lista1);
        t = clock() - t;
        
        average = average + t;
    }
    average = (average/10000.0)/CLOCKS_PER_SEC;
    printf("%f  dla 2000\n", average);

    double average3 = 0;
    clock_t t3;
    for(int i = 0; i < 10000; i++) {
        t3 = clock();
        search(9990, &lista1);
        t3 = clock() - t3;
        
        average3 = average3 + t3;
    }

    average3 = (average3/10000.0)/CLOCKS_PER_SEC;
    printf("%f  dla 9990\n", average3);

    int rand1 = rand() % 10000;

    double average2 = 0;
    clock_t t2;
    for(int i = 0; i < 10000; i++) {
        t2 = clock();
        search(rand1, &lista1);
        t2 = clock() - t2;
        
        average2 = average2 + t2;
    }
    average2 = (average2/10000.0)/CLOCKS_PER_SEC;
    printf("%f  dla losowej wartosci: ", average2);
    printf("%d ", rand1);


    //Merge
    for(int i = 0; i < 10; i++) {
        int random = rand() % 1000;
        add(random, &lista2);
    }
    for(int i = 0; i < 10; i++) {
        int random = rand() % 1000;
        add(random, &lista3);
    }
    printf("\nMerge list \n");
    display(&lista2);
    printf("\n");
    display(&lista3);
    printf("\n");
    merge(&lista2, &lista3);
    printf("\n");
    display(&lista2);
    printf("\n");

}


void add(int item, list* lista) {
    struct node *nptr = malloc(sizeof(struct node));
    nptr->data = item;
    nptr->next = NULL;
    if (lista->start == NULL) {
        lista->start = nptr;
        lista->end = nptr;
    } 
    else {
        struct node *temp;
        temp = lista->start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        } 
        temp->next = nptr;
        lista->end = nptr;
    }
}


void display(list* lista) {
    struct node *temp;
    temp = lista->start;
    if (temp == NULL)
    {
        printf("link list is empty");
    } 
    while (temp != NULL)
    {
        printf("%d, ", temp->data);
        temp = temp->next;
    }
}

void search(int i, list* lista) {
    struct node *temp;
    temp = lista->start;

    for(int a = 0; a<i; a++) {
        temp = temp->next;
    }
    // printf("%d, ", temp->data);

}

void merge(list* lista1, list* lista2) {

    if (lista2->start == NULL) {
        printf("lista druga jest pusta");
    } 
    else {
        lista1->end->next = lista2->start;
    }

}
