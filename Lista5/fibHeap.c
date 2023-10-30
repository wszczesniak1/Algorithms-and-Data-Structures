#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>

bool VERBOSE = true;
int COMPARISONS = 0;

// Struktura wezla Fibonacci Heap
typedef struct FibonacciHeapNode
{
    int key;                          // Klucz węzła
    int degree;                       // Stopień węzła
    bool marked;                      // Czy węzeł jest oznaczony
    struct FibonacciHeapNode *parent; // Wskaźnik na rodzica
    struct FibonacciHeapNode *child;  // Wskaźnik na dowolne dziecko
    struct FibonacciHeapNode *left;   // Wskaźnik na lewe rodzeństwo
    struct FibonacciHeapNode *right;  // Wskaźnik na prawe rodzeństwo
} FibonacciHeapNode;

// Struktura Fibonacci Heap
typedef struct FibonacciHeap
{
    FibonacciHeapNode *min; // Wskaźnik na węzeł z najmniejszym kluczem
    int count;              // Liczba węzłów w kopcu
} FibonacciHeap;

FibonacciHeap *make_heap();
void heap_insert(FibonacciHeap *heap, int key);
FibonacciHeap *heap_union(FibonacciHeap *heap1, FibonacciHeap *heap2);
void heap_link(FibonacciHeapNode *node1, FibonacciHeapNode *node2);
void merge_with_child_list(FibonacciHeapNode *parent, FibonacciHeapNode *node);
void consolidate(FibonacciHeap *heap);
FibonacciHeapNode *extract_min(FibonacciHeap *heap);
void display_heap(FibonacciHeapNode *node, int level);

int compareInts(int i1, int i2)
{
    COMPARISONS++;

    if (i1 > i2)
    {
        return 1;
    }
    else if (i1 == i2)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

// Tworzenie pustego kopca
FibonacciHeap *make_heap()
{
    printf("Heap created\n");
    FibonacciHeap *heap = (FibonacciHeap *)malloc(sizeof(FibonacciHeap));
    heap->min = NULL;
    heap->count = 0;
    return heap;
}

// Wstawianie wezla do kopca
void heap_insert(FibonacciHeap *heap, int key)
{
    printf("inserted key = %d into the heap\n", key);
    COMPARISONS = 0;

    FibonacciHeapNode *node = (FibonacciHeapNode *)malloc(sizeof(FibonacciHeapNode));
    node->key = key;
    node->degree = 0;
    node->marked = false;
    node->parent = NULL;
    node->child = NULL;

    if (heap->min == NULL)
    {
        node->left = node;
        node->right = node;
        heap->min = node;
    }
    else
    {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
        if (compareInts(heap->min->key, key) > 0)
        {
            heap->min = node;
        }
    }

    heap->count++;
}

// Laczenie dwoch kopcow
FibonacciHeap* heap_union(FibonacciHeap* heap1, FibonacciHeap* heap2) {
    FibonacciHeap* newHeap = make_heap();
    newHeap->min = heap1->min;

    if (heap1->min == NULL) {
        newHeap->min = heap2->min;
    } else if (heap2->min != NULL) {
        FibonacciHeapNode* temp1 = heap1->min->right;
        FibonacciHeapNode* temp2 = heap2->min->left;
        heap1->min->right = heap2->min;
        heap2->min->left = heap1->min;
        temp1->left = temp2;
        temp2->right = temp1;

        if (compareInts(heap2->min->key,heap1->min->key) < 0) {
            newHeap->min = heap2->min;
        }
    }

    newHeap->count = heap1->count + heap2->count;
    free(heap1);
    free(heap2);
    return newHeap;
}

// Laczenie dwoch list wezlow
void heap_link(FibonacciHeapNode *node1, FibonacciHeapNode *node2)
{
    // Usun z root-listy wezel node1
    node1->left->right = node1->right;
    node1->right->left = node1->left;

    node1->left = node1;
    node1->right = node1;

    merge_with_child_list(node2, node1);

    node2->degree++;
    node1->parent = node2;
    node1->marked = false;
}

void merge_with_child_list(FibonacciHeapNode *parent, FibonacciHeapNode *node)
{
    if (parent->child == NULL)
    {
        parent->child = node;
    }
    else
    {
        node->right = parent->child->right;
        node->left = parent->child;
        parent->child->right->left = node;
        parent->child->right = node;
    }
}

FibonacciHeapNode *extract_min(FibonacciHeap *heap)
{
    printf("Extract Min %d from Heap\n", heap->min->key);
    COMPARISONS = 0;

    // Sprawdź, czy kopiec jest pusty
    if (heap->min == NULL)
    {
        printf("Heap is empty.\n");
        return NULL;
    }

    // Znajdz minimalny wezel
    FibonacciHeapNode *minNode = heap->min;

    // Przywroc dzieci minimalnego wezla do listy korzeni
    if (minNode->child != NULL)
    {
        FibonacciHeapNode *child = minNode->child;
        do
        {
            FibonacciHeapNode *nextChild = child->right;
            child->left = heap->min;
            child->right = heap->min->right;
            heap->min->right = child;
            child->right->left = child;
            child->parent = NULL;
            child = nextChild;
        } while (child != minNode->child);
    }

    // Usun minimalny wezel z listy korzeni
    if (minNode->right == minNode)
    {
        heap->min = NULL;
        heap->count = 0;
    }
    else
    {
        minNode->left->right = minNode->right;
        minNode->right->left = minNode->left;
        heap->min = minNode->right;

        // Polacz korzenie o tym samym stopniu
        consolidate(heap);
    }
    heap->count--;

    // Zwroc usuniety minimalny wezel
    return minNode;
}

// Konsolidacja kopcow
void consolidate(FibonacciHeap *heap)
{
    int maxDegree = (int)(log(heap->count) * 2);
    FibonacciHeapNode **array = (FibonacciHeapNode **)malloc(maxDegree * sizeof(FibonacciHeapNode *));
    int i;

    for (int i = 0; i < maxDegree; i++)
    {
        array[i] = NULL;
    }

    FibonacciHeapNode *current = heap->min;
    int numRoots = 0;

    if (current != NULL)
    {
        numRoots++;
        current = current->right;

        while (current != heap->min)
        {
            numRoots++;
            current = current->right;
        }
    }

    for (int i = 0; i < numRoots; i++)
    {
        int degree = current->degree;
        FibonacciHeapNode *next = current->right;

        while (array[degree] != NULL)
        {
            FibonacciHeapNode *other = array[degree];

            if (compareInts(current->key, other->key) > 0)
            {
                FibonacciHeapNode *temp = current;
                current = other;
                other = temp;
            }
            heap_link(other, current);
            array[degree] = NULL;
            degree++;
        }
        array[degree] = current;
        current = next;
    }

    for (int i = 0; i < maxDegree; i++)
    {
        if (array[i] != NULL)
        {
            if (compareInts(array[i]->key,heap->min->key) <= 0)
            {
                heap->min = array[i];
            }
        }
    }

    free(array);
}

// Funkcja do printowania Fibonacci Heap
void display_heap(FibonacciHeapNode *node, int level)
{
    if (node == NULL)
    {
        return;
    }

    FibonacciHeapNode *current = node;
    do
    {
        if (current->child != NULL)
        {
            printf("%*s%d\\_\n", level * 3, "", current->key);
            display_heap(current->child, level + 1);
        }
        else
        {
            printf("%*s%d\n", level * 3, "", current->key);
        }

        current = current->right;
    } while (current != node);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./fibHeap n\n");
        return -1;
    }

    int n;
    bool verbose;

    n = atoi(argv[1]);

    if (n > 50)
    {
        VERBOSE = false;
    }

    assert(n > 0);

    FibonacciHeap *heap, *heap1, *heap2;

    heap1 = make_heap();
    heap2 = make_heap();

    srand(time(NULL));

    int elem;

    for (int i = 0; i < n; i++) {
        elem = rand() % (2 * n);
        heap_insert(heap1, elem);
        
        if (VERBOSE) {
          display_heap(heap1 -> min,1);
            printf("\n");

        }

        elem = rand() % (2 * n);
        heap_insert(heap2, elem);
        
        if (VERBOSE) {
            display_heap(heap2 -> min,1);
            printf("\n");
        }
    }

    heap = heap_union(heap1, heap2);

    if (VERBOSE) {
        display_heap(heap -> min,1);
        printf("\n");
    }

    for (int i = 0; i < 2*n; i++) {
        FibonacciHeapNode *min = extract_min(heap);
        if (VERBOSE) {
            display_heap(heap -> min, 1);
            printf("\n");
        }
    }

    if (VERBOSE) {
        printf("EMPTY: ");

        if (heap -> min == NULL) {
            printf("TRUE\n");
        } 
        else {
            printf("FALSE\n");
        }
    }

    return 0;
}
