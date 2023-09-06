

#include <stddef.h> /*size_t*/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h> /* memcpy */
#include "heap.h"
#include "dynamic_vector.h"

/*****************************************************************************/
struct heap
{
    dynamic_vector_ty *vector;
    compare_ty heap_cmp;
};
/****************************** define and inner function ****************************/

#define RIGHT(a) ((2 * a) + 2)
#define LEFT(a) ((2 * a) + 1)
#define PARRENT(a) (((int)a - 1) / 2)

#define CAPACITY 20

static void SwapMem(void *data1, void *data2, int size)
{
    char *buffer = (char *)malloc((size_t)size);
    if (NULL == buffer)
    {
        return;
    }

    memcpy(buffer, data1, size);
    memcpy(data1, data2, size);
    memcpy(data2, buffer, size);

    free(buffer);
}
static void VectorSwap(dynamic_vector_ty *vector, size_t index1, size_t index2)
{

    void *data1 = VectorGetAccessToElement(vector, index1);
    void *data2 = VectorGetAccessToElement(vector, index2);

    size_t temp_data = 0;
    temp_data = *(size_t *)data1;
    *(size_t *)data1 = *(size_t *)data2;
    *(size_t *)data2 = temp_data;
}

static void HeapifyDown(heap_ty *heap, size_t index)
{

    dynamic_vector_ty *vector = heap->vector;
    size_t last_index = VectorSize(vector) - 1;
    compare_ty cmp = heap->heap_cmp;
    void *right = NULL;
    void *left = NULL;
    void *data_to_move = NULL;

    assert(NULL != heap);

    data_to_move = VectorGetAccessToElement(vector, index);
    right = VectorGetAccessToElement(vector, RIGHT(index));
    left = VectorGetAccessToElement(vector, LEFT(index));

    while ((-1 == cmp(data_to_move, right)) || (-1 == cmp(data_to_move, left)))
    {

        if (1 == cmp(left, right))
        {
            VectorSwap(vector, index, LEFT(index));
            PrintHeap(heap);
            index = LEFT(index);

        }
        else
        {
            printf("LEFT(index) = %d",LEFT(index));
            printf("RIGHT(index) = %d",RIGHT(index));
            printf("index = %d",index);

        }
    }

    /* while (RIGHT(index) <= last_index)
    {
        right = VectorGetAccessToElement(vector, RIGHT(index));
        left = VectorGetAccessToElement(vector, LEFT(index));

        if (0 == cmp(data_to_move, left) || 0 == cmp(data_to_move, right))
        {
            if (1 == cmp(right, left))
            {
                VectorSwap(vector, index, RIGHT(index));
                index = RIGHT(index);
            }
            else
            {
                VectorSwap(vector, index, LEFT(index));
                index = LEFT(index);
            }
        }
        else
        {
            return;
        }

        data_to_move = VectorGetAccessToElement(vector, index);
    } */
}

static void HeapifyUp(heap_ty *heap, void *data)
{

    dynamic_vector_ty *vector = heap->vector;

    size_t index = VectorSize(vector) - 1;
    compare_ty cmp = heap->heap_cmp;
    void *cmp_data = NULL;

    assert(NULL != heap);
    assert(NULL != data);

    cmp_data = VectorGetAccessToElement(vector, PARRENT(index));

    while (0 < cmp(data, cmp_data)) /*if to push > parent do swap*/
    {
        VectorSwap(vector, index, PARRENT(index));

        index = PARRENT(index);

        if (0 == index)
        {
            return;
        }

        cmp_data = VectorGetAccessToElement(vector, PARRENT(index));
    }
}

/****************************** Create ****************************/

heap_ty *HEAPCreate(compare_ty compare)
{
    heap_ty *heap = NULL;

    assert(NULL != compare);

    heap = (heap_ty *)malloc(sizeof(heap_ty));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->vector = VectorCreate(CAPACITY, sizeof(size_t));
    if (NULL == heap->vector)
    {
        free(heap);
        return NULL;
    }

    heap->heap_cmp = compare;

    return heap;
}

/****************************** Destroy ****************************/

void HEAPDestroy(heap_ty *heap)
{
    assert(NULL != heap);
    assert(NULL != heap->vector);

    VectorDestroy(heap->vector);
    heap->vector = NULL;
    heap->heap_cmp = NULL;

    free(heap);
}

/****************************** Push ********************************/

int HEAPPush(heap_ty *heap, void *to_push)
{
    assert(NULL != heap);
    assert(NULL != to_push);

    if (1 == VectorPushBack(heap->vector, to_push))
    {
        return 1;
    }
    if (1 == HEAPSize(heap))
    {
        return 0;
    }

    HeapifyUp(heap, to_push);
    return 0;
}

/****************************** Pop ********************************/

void HEAPPop(heap_ty *heap)
{
    size_t index = 0;

    assert(NULL != heap);

    index = VectorSize(heap->vector) - 1;

    VectorSwap(heap->vector, index, 0);

    VectorPopBack(heap->vector);

    printf("after popBack\n");

    PrintHeap(heap);

    HeapifyDown(heap, 0);

    printf("after HeapifyDown function\n");

    PrintHeap(heap);
}

/****************************** Peek ********************************/

void *HEAPPeek(heap_ty *heap)
{
    assert(NULL != heap);

    if (1 == HEAPIsEmpty(heap))
    {
        return (NULL);
    }

    return VectorGetAccessToElement(heap->vector, 0);
}
/****************************** Size ********************************/

size_t HEAPSize(const heap_ty *heap)
{
    assert(NULL != heap);

    return VectorSize(heap->vector);
}
/****************************** Is Empty ********************************/

int HEAPIsEmpty(const heap_ty *heap)
{
    assert(NULL != heap);

    return VectorIsEmpty(heap->vector);
}

/****************************** Remove ********************************/

void *HEAPRemove(heap_ty *heap, void *to_remove, int (*is_match)(const void *data, const void *to_remove))
{
    void *data = NULL;
    void *last_index = NULL;
    size_t index = 0;
    size_t size = 0;
    dynamic_vector_ty *vector = NULL;

    assert(NULL != heap);
    assert(NULL != is_match);

    vector = heap->vector;

    size = VectorSize(vector);

    last_index = (size_t *)VectorGetAccessToElement(vector, size - 1);

    while (index < size)
    {
        data = VectorGetAccessToElement(vector, index);

        if (1 == is_match(data, to_remove))
        {
            break;
        }
        ++index;
    }

    if (index == size)
    {
        return (NULL);
    }

    SwapMem(data, last_index, sizeof(size_t));

    VectorPopBack(vector);

    HeapifyDown(heap, index);

    return to_remove;
}

/****************************** Print Heap ********************************/

void PrintHeap(heap_ty *heap)
{
    size_t arr_size = HEAPSize(heap);
    size_t i = 0;
    void *data = NULL;

    assert(arr_size != 0);

    for (i = 0; i < arr_size; i++)
    {
        data = VectorGetAccessToElement(heap->vector, i);
        printf("index [%lu] = %d\n", i, *(int *)((size_t *)data));
    }
}

void PrintHeapTree(heap_ty *heap)
{
    size_t arr_size = HEAPSize(heap);
    size_t i, j = 0;
    void *data = NULL;
    size_t spase = arr_size;
    size_t count = arr_size - spase;

    for (i = 0; i < arr_size; i++)
    {
        data = VectorGetAccessToElement(heap->vector, i);

        for (j = 0; j < spase; j++)
        {
            printf(" ");
            spase /= 2;
        }
        printf("%d\n", *(int *)((size_t *)data));
    }
}
