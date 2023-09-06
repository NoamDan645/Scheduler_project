
#include <stddef.h> /*size_t*/
#include <stdio.h>
#include <assert.h>
#include "heap.h"

#define SIZE 12

int IntCmpFuncTest(const void *data1, const void *data2)
{
    int x = 0;

    assert(data1);
    assert(data2);
 
    x =  *(int *)data1 - *(int *)data2; 

    if (x > 0) 
    {
        return 1;
    }
    else if (x < 0)
    {
        return -1;
    }
    return x;
}

int IntIsMatch(const void *data, const void *param)
{
    assert(data);
    assert(param);

    return (*(int *)data == *(int *)param);
}

/************************TEST*******************/
void Test1();
void Test2()
{
    int x1 = 10;
    int x2 = 10;

    heap_ty *heap = HEAPCreate(IntCmpFuncTest);
    HEAPPush(heap, &x1);
    HEAPPush(heap, &x2);
}

int main()
{
    Test1();
    Test2();

    return 0;
}

void Test1()
{
    int arr[SIZE + 1] = {10, 6, 20, 65, 80, 5, 3, 100, 300, 201, 12, 2, 7};
    int arr1[3] = {1, 10, 20};

    int peek, pop, i = 0;
    int is_heap_empty = 0;
    void *remove = 0;

    heap_ty *heap = HEAPCreate(IntCmpFuncTest);

    HEAPIsEmpty(heap) ? printf("heap is empty\n") : printf("heap is not empty\n");

    for (i = 0; i < SIZE; i++)
    {
        HEAPPush(heap, &arr[i]);
    }

    PrintHeap(heap);

    for (i = 0; i < SIZE; i++)
    {
        HEAPPop(heap);
        printf("------------------------------------------\n");
    }

    HEAPDestroy(heap);
}
