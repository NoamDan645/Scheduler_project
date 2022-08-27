/*************************************************************
* OL124 Queue project
* Queue.h
* Queue.c
* Queue_test.c
* *
*
******************************************************************/
#include <stddef.h>

#ifndef Q_H
#define Q_H




/*
struct queue
{
    slist_ty *list;
};
*/

typedef struct queue queue_ty;
/*Creates Queue - return pointer to Que */
queue_ty *QCreate(void); 
/*Delete Que */
void QDestroy(queue_ty *queue);
/*Get node from front of the queue - return  data from node (pop front)*/
void *QDeQueue(queue_ty *queue);
/* Add node to the end of queue Success = 0, Fail = 1 (push back) */
int QEnQueue(queue_ty *queue, void *data);
/*get data of first element in queue first node */
const void *QPeek(const queue_ty *queue);
/*Queue is empty- status 1 for empty, 0 not empty*/
int QIsEmpty(const queue_ty *queue);
/*Size of Queue from tail to head*/
size_t QSize(const queue_ty *queue);
/*append source queue to end of the line of dest queue (push back) */
void QAppend(queue_ty *_dest_queue, queue_ty *_src_queue);

#endif /*Q_H */