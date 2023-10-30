#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

int COMPARISONS = 0;
bool VERBOSE = true;

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 127

typedef struct __node_t__ {
	int value;
	int degree;
	struct __node_t__ *child;
	struct __node_t__ *parent;
	struct __node_t__ *brother;
} node_t;

typedef struct __heap_t__ {
	node_t *head;
} heap_t;

node_t *node_init( int value )
{
	node_t *node = malloc( sizeof ( node_t ) );
	node->value = value;
	node->degree = 0;
	return node;
}

heap_t *heap_init()
{
	heap_t *heap = malloc( sizeof ( heap_t ) );
	heap->head = NULL;
	return heap;
}

int compareInts(
    int i1,
    int i2
) {
    COMPARISONS++;

    if (i1 > i2) {
        return 1;
    } else if (i1 == i2) {
        return 0;
    } else {
        return -1;
    }
}

node_t *heap_merge( heap_t *heap1, heap_t *heap2 )
{
	if( heap1->head == NULL ) return heap2->head;
	if( heap2->head == NULL ) return heap1->head;

	node_t *head;
	node_t *h1It = heap1->head;
	node_t *h2It = heap2->head;
	node_t *tail;

	if( heap1->head->degree <= heap2->head->degree )
	{
		head = heap1->head;
		h1It = h1It->brother;
	}
	else
	{
		head = heap2->head;
		h2It = h2It->brother;
	}
	tail = head;
	while( h1It != NULL && h2It != NULL )
	{
		if( h1It->degree <= h2It->degree )
		{
			tail->brother = h1It;
			h1It = h1It->brother;
		}
		else
		{
			tail->brother = h2It;
			h2It = h2It->brother;
		}

		tail = tail->brother;
	}

	tail->brother = ( h1It != NULL ) ? h1It : h2It;

	return head;
}

node_t *heap_union( heap_t *original, heap_t *uni )
{
	node_t *new_head = heap_merge( original, uni );

	original->head = NULL;
	uni->head = NULL;

	if( new_head == NULL )
		return NULL;

	node_t *prev = NULL;
	node_t *aux = new_head;
	node_t *next = new_head->brother;

	while( next != NULL )
	{
		if( aux->degree != next->degree || ( next->brother != NULL && next->brother->degree == aux->degree ) )
		{
			prev = aux;
			aux = next;
		}
		else
		{
			if(compareInts(aux -> value, next -> value) < 0)
			{
				aux->brother = next->brother;
				next->parent = aux;
				next->brother = aux->child;
				aux->child = next;
				aux->degree++;
			}
			else
			{
				if( prev == NULL )
					new_head = next;
				else
					prev->brother = next;

				aux->parent = next;
				aux->brother = next->child;
				next->child = aux;
				next->degree++;

				aux = next;
			}
		}

		next = aux->brother;
	}

	return new_head;
}

node_t *heap_union_comps(heap_t *original, heap_t *uni) {
    COMPARISONS = 0;
    node_t* result = heap_union(original, uni);
    printf("COMPARISONS: %d\n", COMPARISONS);
    return result;
}

void heap_insert( heap_t *heap, int value )
{
    COMPARISONS = 0;
	node_t *node = node_init( value );
	heap_t *temp = heap_init();
	temp->head = node;
	heap->head = heap_union( heap, temp );
	free( temp );
    printf("COMPARISONS: %d\n", COMPARISONS);
}


void heap_remove( heap_t *heap, node_t *head, node_t *bef )
{
	if( head == heap->head )
		heap->head = head->brother;
	else
		bef->brother = head->brother;

	node_t *new_head = NULL;
	node_t *child = head->child;

	while( child != NULL )
	{
		node_t *next = child->brother;
		child->brother = new_head;
		child->parent = NULL;
		new_head = child;
		child = next;
	}

	heap_t *temp = heap_init();
	temp->head = new_head;
	heap->head = heap_union( heap, temp );
	free( temp );
}


node_t *heap_min( heap_t *heap )
{
    COMPARISONS = 0;
	if( heap->head == NULL ) {
        return NULL;
    }

	node_t *min = heap->head;
	node_t *min_prev = NULL;
	node_t *next = min->brother;
	node_t *next_prev = min;

	while( next != NULL )
	{
		if(compareInts(next -> value, min -> value) < 0)
		{
			min = next;
			min_prev = next_prev;
		}

		next_prev = next;
		next = next->brother;
	}

	heap_remove( heap, min, min_prev );

    printf("COMPARISONS: %d\n", COMPARISONS);

	return min;
}

void heap_free( heap_t *h )
{
	while( heap_min( h ) );
	free( h );
}

int main(int argc, char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./binheap n\n");
        return -1;
    }

    int n;
    bool verbose;

    n = atoi(argv[1]);

    if (n > 50) {
        VERBOSE = false;
    }

    assert(n > 0);
    
    heap_t *heap1 = heap_init();
    heap_t *heap2 = heap_init();

    srand(time(NULL));

    int elem;

    for (int i = 0; i < n; i++) {
        elem = rand() % (2 * n);
        heap_insert(heap1, elem);
        if (VERBOSE) {
            printf("INSERT HEAP 1: %d\n", elem);
        }
        elem = rand() % (2 * n);
        
        heap_insert(heap2, elem);
        if (VERBOSE) {
            printf("INSERT HEAP 2: %d\n", elem);
            printf("\n");
        }
    }

    heap_t *heap = heap_init();
    heap -> head = heap_union_comps(heap1, heap2);
    if (VERBOSE) {
        printf("UNION\n");
        printf("\n");
    }
    
    for (int i = 0; i < 2 * n; i++) {
        node_t* min = heap_min(heap);
        if (VERBOSE) {
            printf("REMOVE HEAP UNION: %d\n", min -> value);
            printf("\n");
        }
    }

    if (VERBOSE) {
        printf("EMPTY: ");
        if (heap -> head == NULL) {
            printf("TRUE\n");
        } else {
            printf("FALSE\n");
        }
    }
    

    heap_free(heap);

    return 0;
}
