/***************************
 * HEAP TREE project
 * heap.h
 * heap.c
 * heap_test.c
 *
 ***************************/


#ifndef __HEAP_TREE_H__
#define __HEAP_TREE_H__

#include <stddef.h> /*size_t*/

/* The root is the element with the highest priority. */
typedef struct heap heap_ty;

/*
  Return a positive integer if data1 should come before data2,
  a negative integer if data2 should come first, and 0 if equal.
*/
typedef int(*compare_ty)(const void *data1,const void *data2);

/***********************************************************
 * --- HEAPCreate ---
 * Function creates a new binary tree heap data structure.
 *	return NULL if malloc fails
 ***********************************************************/
heap_ty *HEAPCreate(compare_ty compare);

/***********************************************************
 * --- HEAPDestroy ---
 * Frees the heap. The stored user data is not freed.
 ***********************************************************/
void HEAPDestroy(heap_ty* heap);

/***********************************************************
 * --- HEAPPush ---
 * push new element to the tree. return 0 if succeed, 1 if fail
 ***********************************************************/
int HEAPPush(heap_ty* heap, void *to_push);

/***********************************************************
 * --- HEAPPop ---
 * remove the root 
 ***********************************************************/
void HEAPPop(heap_ty* heap);

/***********************************************************
 * --- HEAPPeek ---
 * return the data of the root
 ***********************************************************/
void *HEAPPeek(heap_ty* heap);

/***********************************************************
 * --- HEAPSize ---
 * Function returns the number of items stored in HEAP
 ***********************************************************/
size_t HEAPSize(const heap_ty *heap);

/***********************************************************
 * --- HEAPIsEmpty ---
 * Function returns 1 - if Empty, 0 - not Empty
 ***********************************************************/
int HEAPIsEmpty(const heap_ty *heap);

/***********************************************************
 * --- HEAPRemove ---
 * Removes the first element for which is_match(data, to_remove) is
 * true and returns it, or NULL if there is no match.
 ***********************************************************/
void* HEAPRemove(heap_ty *heap, void *to_remove, int (*is_match)(const void *data, const void *to_remove));



#endif /* __HEAP_TREE_H__ */
