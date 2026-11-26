/*************************************************************
 * Binary heap
 *
 * Author: Noam Hadad
 *
 * Stores pointers to user data in a dynamic vector. The element with
 * the highest priority (compare(a, b) > 0 means a before b) is at the
 * root.
 ******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "dynamic_vector.h"
#include "heap.h"

#define LEFT(i) ((2 * (i)) + 1)
#define RIGHT(i) ((2 * (i)) + 2)
#define PARENT(i) (((i) - 1) / 2)

#define INITIAL_CAPACITY 16

struct heap
{
	dynamic_vector_ty *vector;
	compare_ty compare;
};

/****************************** helpers ******************************/

static void *GetData(const heap_ty *heap, size_t index)
{
	return *(void **)VectorGetAccessToElement(heap->vector, index);
}

static void Swap(heap_ty *heap, size_t i, size_t j)
{
	void **a = (void **)VectorGetAccessToElement(heap->vector, i);
	void **b = (void **)VectorGetAccessToElement(heap->vector, j);
	void *tmp = *a;

	*a = *b;
	*b = tmp;
}

/* a has higher priority than b */
static int IsBefore(const heap_ty *heap, size_t a, size_t b)
{
	return 0 < heap->compare(GetData(heap, a), GetData(heap, b));
}

static void HeapifyUp(heap_ty *heap, size_t index)
{
	while (0 < index && IsBefore(heap, index, PARENT(index)))
	{
		Swap(heap, index, PARENT(index));
		index = PARENT(index);
	}
}

static void HeapifyDown(heap_ty *heap, size_t index)
{
	size_t size = VectorSize(heap->vector);

	for (;;)
	{
		size_t best = index;

		if (LEFT(index) < size && IsBefore(heap, LEFT(index), best))
		{
			best = LEFT(index);
		}
		if (RIGHT(index) < size && IsBefore(heap, RIGHT(index), best))
		{
			best = RIGHT(index);
		}
		if (best == index)
		{
			return;
		}

		Swap(heap, index, best);
		index = best;
	}
}

/* move the last element into index, drop the last slot and restore order */
static void RemoveAt(heap_ty *heap, size_t index)
{
	size_t last = VectorSize(heap->vector) - 1;

	if (index != last)
	{
		Swap(heap, index, last);
	}
	VectorPopBack(heap->vector);

	if (index < last)
	{
		HeapifyDown(heap, index);
		HeapifyUp(heap, index);
	}
}

/****************************** API ******************************/

heap_ty *HEAPCreate(compare_ty compare)
{
	heap_ty *heap = NULL;

	assert(NULL != compare);

	heap = (heap_ty *)malloc(sizeof(heap_ty));
	if (NULL == heap)
	{
		return NULL;
	}

	heap->vector = VectorCreate(INITIAL_CAPACITY, sizeof(void *));
	if (NULL == heap->vector)
	{
		free(heap);
		return NULL;
	}

	heap->compare = compare;

	return heap;
}

void HEAPDestroy(heap_ty *heap)
{
	if (NULL == heap)
	{
		return;
	}

	VectorDestroy(heap->vector);
	free(heap);
}

int HEAPPush(heap_ty *heap, void *to_push)
{
	assert(NULL != heap);

	if (0 != VectorPushBack(heap->vector, &to_push))
	{
		return 1;
	}

	HeapifyUp(heap, VectorSize(heap->vector) - 1);

	return 0;
}

void HEAPPop(heap_ty *heap)
{
	assert(NULL != heap);

	if (HEAPIsEmpty(heap))
	{
		return;
	}

	RemoveAt(heap, 0);
}

void *HEAPPeek(heap_ty *heap)
{
	assert(NULL != heap);

	if (HEAPIsEmpty(heap))
	{
		return NULL;
	}

	return GetData(heap, 0);
}

size_t HEAPSize(const heap_ty *heap)
{
	assert(NULL != heap);

	return VectorSize(heap->vector);
}

int HEAPIsEmpty(const heap_ty *heap)
{
	assert(NULL != heap);

	return VectorIsEmpty(heap->vector);
}

void *HEAPRemove(heap_ty *heap, void *to_remove,
				 int (*is_match)(const void *data, const void *to_remove))
{
	size_t size = 0;
	size_t i = 0;

	assert(NULL != heap);
	assert(NULL != is_match);

	size = HEAPSize(heap);
	for (i = 0; i < size; ++i)
	{
		void *data = GetData(heap, i);

		if (is_match(data, to_remove))
		{
			RemoveAt(heap, i);
			return data;
		}
	}

	return NULL;
}
