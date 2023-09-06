#include <stdio.h>  /*printf */
#include <stdlib.h> /*malloc*/
#include <assert.h> /* assert */
#include "heap.h"   /*heap */
#include "pqueue.h" /**/

struct pqueue
{
    heap_ty *heap;
};

/*****************************************************************************/

pqueue_ty *PQCreate(compare_ty cmp)
{
    pqueue_ty *pq = NULL;

    assert(NULL != cmp);

    pq = (pqueue_ty *)malloc(sizeof(pqueue_ty));
    if (NULL == pq)
    {
        return NULL;
    }
    pq->heap = HEAPCreate(cmp);
    if (NULL == pq->heap)
    {
        free(pq);
        return NULL;
    }

    return pq;
}

/*****************************************************************************/

void PQDestroy(pqueue_ty *pq)
{
    assert(pq != NULL);

    HEAPDestroy(pq->heap);

    free(pq);
}

/*****************************************************************************/

void *PQDeQueue(pqueue_ty *pq)
{
    void *data = NULL;
    heap_ty *heap;

    assert(NULL != pq);

    heap = pq->heap;
    data = HEAPPeek(heap);
    HEAPPop(heap);

    return data;
}

/*****************************************************************************/

int PQEnQueue(pqueue_ty *pq, void *data)
{
    assert(NULL != pq);
    assert(NULL != data);

    return HEAPPush(pq->heap, data);
}

/*****************************************************************************/

const void *PQPeek(const pqueue_ty *pq)
{
    heap_ty *heap = NULL;
    
    assert(NULL != pq);
    
    heap = pq->heap;
    
    if (1 == HEAPIsEmpty(heap))
    {
        return NULL;
    }
    
    return HEAPPeek(heap);
}
/*****************************************************************************/

int PQIsEmpty(const pqueue_ty *pq)
{
    assert(pq);

    return HEAPIsEmpty(pq->heap);
}
/*****************************************************************************/

size_t PQSize(const pqueue_ty *pq)
{
    assert(NULL != pq);

    return HEAPSize(pq->heap);
}
/*****************************************************************************/

void *PQErase(pqueue_ty *pq, int (*is_match)(const void *data, const void *param), void *param)
{
    assert(pq);

    return HEAPRemove(pq->heap, param, is_match);
}
