
#include <stddef.h> /*size_t*/
#include <stdio.h>
#include <assert.h>
#include "heap.h"

#define SIZE 12

int IntCmpFuncTest(const void *data1, const void *data2)
{

    assert(data1);
    assert(data2);

    return (*(int *)data1) - (*(int *)data2) > 0 ? 1 : 0;
}

int IntIsMatch(const void *data, const void *param)
{
    assert(data);
    assert(param);
    return (*(int *)data == *(int *)param);
}

int main()
{
    int arr[SIZE] = {300, 10, 6, 20, 65, 80, 5, 3, 100, 201, 12, 2};
    int peek, pop, i = 0;
    int is_heap_empty = 0;
    void *remove = 0;

    heap_ty *heap = HEAPCreate(IntCmpFuncTest);

    printf("create heap : ");
    HEAPIsEmpty(heap) ? printf("י File\n") : printf("heap is not empty\n");

    for (i = 0; i < SIZE; i++)
    {
        HEAPPush(heap, &arr[i]);
    }
    printf("after push : ");

    HEAPIsEmpty(heap) ? printf("heap is empty\n") : printf("heap is not empty\n");
    PrintHeap(heap);

    HEAPRemove(heap, &arr[4], IntIsMatch);
    PrintHeap(heap);

    printf("size of heap = %lu\n", HEAPSize(heap));
    peek = *(int *)HEAPPeek(heap);
    printf("peek = %d\n", peek);

    HEAPPop(heap);

    PrintHeap(heap);

    for (i = 0; i < SIZE; i++)
    {
        printf("remove %d from heap \n", arr[i]);
        HEAPRemove(heap, &arr[i], IntIsMatch);
        PrintHeap(heap);
    } 
    printf("size of heap after remove = %lu\n", HEAPSize(heap));
    HEAPIsEmpty(heap) ? printf("heap is empty\n") : printf("heap is not empty\n");

    HEAPDestroy(heap);

    return 0;
}
