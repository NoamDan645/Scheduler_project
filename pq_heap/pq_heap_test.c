#include <stdlib.h>/*malloc*/
#include <stdio.h> /*printf */
#include "pqueue.h"

#define RESET "\033[0m"  /* Reset colour */
#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */
#define WHITE "\033[37m" /*  White */

#define MSG_SUCCESS(func) printf(GREEN #func "--> Test PASSED \n" RESET)
#define MSG_FAILURE(func) puts(RED #func "--> Test FAILED \n" RESET)
#define TEST_MSG(func, func_res, exp_res) \
    if (func_res == exp_res)              \
    {                                     \
        MSG_SUCCESS(func);                \
    }                                     \
    else                                  \
    {                                     \
        MSG_FAILURE(func);                \
    }

typedef struct data
{
    char priority;
    int ID;
    char *Name;
} data_ty;

int compare(const void *data, const void *param);
int compare1(const void *data, const void *param);

int compare2(const data_ty *data1, const data_ty *data2);
/*
int SortLInsert_test(sortlist_ty *list, int x);
int SortLPopBack_test(sortlist_ty *list);
int SortLPopFront_test(sortlist_ty *list);
int SortLForEach_test(sortlist_ty *list);
int SortLFind_test(sortlist_ty *list);
int SortLFindIf_test(sortlist_ty *list);
int SortLMerge_test(sortlist_ty *list1, sortlist_ty *list2);
void Print_list(sortlist_ty  *list);
*/
int addnum(void *data, void *param);
int match(const void *data, const void *param);

int arr[] = {11, 3, 15, 7, 17, 56, 2, 22, 66};
int arr1[] = {25, 28, 21, 27, 25, 45, 5, 36, 11};
size_t len_arr = sizeof(arr) / sizeof(arr[0]);
size_t len_arr1 = sizeof(arr1) / sizeof(arr1[0]);
size_t stud_num = 10;

data_ty students[10];

int main(void)
{
    char str[] = "12345";
    int i = 0, x = 15, y = 1;
    int *ptr = &x;
    size_t j = 0;
    void *param = &y, *v = NULL;
    pqueue_ty *pque1 = PQCreate(compare);
    pqueue_ty *pque2 = PQCreate(compare);
    pqueue_ty *pque3 = PQCreate(compare1);
    (void)pque3;
    (void)param;
    (void)ptr;
    (void)i;
    (void)str;
    printf("PQUE1 Is Empty %d\n", PQIsEmpty(pque1));
    printf("PQUE2 Is Empty %d\n", PQIsEmpty(pque2));

    for (j = 0; j < len_arr; j++)
    {
        PQEnQueue(pque1, arr + j);
        PQEnQueue(pque2, arr1 + j);
        printf("PQueue1 Size: %lu  PQueue2 Size: %lu \n", PQSize(pque1), PQSize(pque2));
    }

    printf("PPQUE1 Size %lu\n", PQSize(pque1));

    TEST_MSG(PQSize(), PQSize(pque1), len_arr);
    TEST_MSG(PQSize(), PQSize(pque2), len_arr1);
    printf("PPQUE1 Is Empty %d\n", PQIsEmpty(pque1));
    printf("PPQUE2 Is Empty %d\n", PQIsEmpty(pque2));

    printf("Peek PPQUE1 %d\n", *(int *)PQPeek(pque1));
    printf("Peek PPQUE1 %d\n", *(int *)PQPeek(pque2));
    for (j = 0; j < len_arr; j++)
    {
        printf("Depque PQUE1 %d, ", *(int *)PQDeQueue(pque1));
        printf("PQueue1 Size %lu\n", PQSize(pque1));
        printf("Depque PQUE2 %d, ", *(int *)PQDeQueue(pque2));
        printf("PQueue2 Size %lu\n", PQSize(pque2));
    }

    printf("PQUE1 Is Empty %d\n", PQIsEmpty(pque1));
    printf("PQUE2 Is Empty %d\n", PQIsEmpty(pque2));

    /*****************************************************/
    
    for (j = 0; j < len_arr; j++)
    {
        PQEnQueue(pque1, arr + j);
        PQEnQueue(pque2, arr1 + j);
    }
    printf("PQUE1 Size %lu\n", PQSize(pque1));
    printf("PQUE2 Size %lu\n", PQSize(pque2));

    v = PQErase(pque1, &match, &arr[0]);
    printf("Erase =  %d\n", *(int *)v);
    v = PQErase(pque1, &match, &arr[0]);
    TEST_MSG(PQErase(), v, NULL);
    /*printf("Erase =  %d\n", *(int*)v);*/

    while (!PQIsEmpty(pque1))
    {
        printf("Depque PQUE1 %d ,", *(int *)PQDeQueue(pque1));
        printf("PQueue1 Size %lu\n", PQSize(pque1));
        /*printf("Depque PQUE2 %d\n", *(int*)PQDePQueue(pque2));
          printf("PQueue2 Size %lu\n", PQSize(pque2));*/
    }

    PQDestroy(pque1);
    PQDestroy(pque2);

    return 0;
}

int addnum(void *data, void *param)
{
    *(int *)data = *(int *)data + *(int *)param;
    return 1;
}

/*return 1 if param==data and 0 otherwise*/
int match(const void *data, const void *param)
{
    return *(int *)data == *(int *)param;
    /*
       return 0;
       return 1;
     */
}

int compare(const void *data, const void *param)
{
    return (*(int *)data - *(int *)param);
}

int compare1(const void *data, const void *param)
{
    return (*(int *)param - *(int *)data);
}

int compare2(const data_ty *data1, const data_ty *data2)
{
    return (data1->priority - data2->priority);
}
