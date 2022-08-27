/*************************************************************
* Priority Queue project
* pqueue.h
* pqueue.c
* pqueue_test.c
******************************************************************/

#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <stddef.h> /* size_t */

/*
struct pqueue
{
    sorted_list_ty *list;

};

*/

typedef struct pqueue pqueue_ty;

typedef int (*pq_is_match_ty)( void *data,  void *param);

/*Creates Queue - return pointer to Que */
pqueue_ty *PQCreate(int (*cmp)(const void *, const void *));

/*Delete Que */
void PQDestroy(pqueue_ty *pqueue);

/*Get node from front of the queue - return  data from node */
void *PQDeQueue(pqueue_ty *pqueue);

/* Add node to the end of queue Success = 0, Fail = 1 */
int PQEnQueue(pqueue_ty *pqueue, void *data);

/*get data of first element in queue first node */
const void *PQPeek(const pqueue_ty *pqueue);

/*Queue is empty- status 1 for empty, 0 not empty*/
int PQIsEmpty(const pqueue_ty *pqueue);

/*Size of Queue from tail to head*/
size_t PQSize(const pqueue_ty *pqueue);

/*Delete node by is_match and return pointer to data */
void *PQErase(pqueue_ty *pq, int (*is_match)(const void *data, const void *params), void *params);

#endif /*PriorityQueue_H */

