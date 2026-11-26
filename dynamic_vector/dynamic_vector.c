/*************************************************************
 * Dynamic vector
 *
 * Author: Noam Hadad
 *
 * A resizable array of fixed-size elements. Grows x2 when full and
 * shrinks by half when it is less than a quarter full (never below
 * its initial capacity).
 ******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free, realloc */
#include <string.h> /* memcpy */

#include "dynamic_vector.h"

#define GROWTH_FACTOR 2
#define SHRINK_THRESHOLD 4 /* shrink when size < capacity / 4 */
#define SHRINK_FACTOR 2

struct dynamic_vector
{
	void *data;
	size_t size;
	size_t capacity;
	size_t min_capacity;
	size_t size_of_element;
};

static int VectorIsFull(const dynamic_vector_ty *vector)
{
	return vector->size == vector->capacity;
}

dynamic_vector_ty *VectorCreate(size_t capacity, size_t size_of_element)
{
	dynamic_vector_ty *vector = NULL;

	assert(0 < size_of_element);

	if (0 == capacity)
	{
		capacity = 1;
	}

	vector = (dynamic_vector_ty *)malloc(sizeof(dynamic_vector_ty));
	if (NULL == vector)
	{
		return NULL;
	}

	vector->data = malloc(capacity * size_of_element);
	if (NULL == vector->data)
	{
		free(vector);
		return NULL;
	}

	vector->size = 0;
	vector->capacity = capacity;
	vector->min_capacity = capacity;
	vector->size_of_element = size_of_element;

	return vector;
}

void VectorDestroy(dynamic_vector_ty *vector)
{
	if (NULL == vector)
	{
		return;
	}

	free(vector->data);
	free(vector);
}

dynamic_vector_ty *VectorReserve(dynamic_vector_ty *vector, size_t new_capacity)
{
	void *new_data = NULL;

	assert(NULL != vector);

	if (new_capacity < vector->size || 0 == new_capacity)
	{
		return NULL;
	}

	new_data = realloc(vector->data, vector->size_of_element * new_capacity);
	if (NULL == new_data)
	{
		return NULL;
	}

	vector->data = new_data;
	vector->capacity = new_capacity;

	return vector;
}

int VectorPushBack(dynamic_vector_ty *vector, void *element)
{
	assert(NULL != vector);
	assert(NULL != element);

	if (VectorIsFull(vector) &&
		NULL == VectorReserve(vector, vector->capacity * GROWTH_FACTOR))
	{
		return 1;
	}

	memcpy((char *)vector->data + vector->size * vector->size_of_element,
		   element, vector->size_of_element);
	++vector->size;

	return 0;
}

void VectorPopBack(dynamic_vector_ty *vector)
{
	size_t new_capacity = 0;

	assert(NULL != vector);

	if (VectorIsEmpty(vector))
	{
		return;
	}

	--vector->size;

	new_capacity = vector->capacity / SHRINK_FACTOR;
	if (vector->size < vector->capacity / SHRINK_THRESHOLD &&
		new_capacity >= vector->min_capacity)
	{
		/* shrinking is an optimisation: on failure keep the old buffer */
		VectorReserve(vector, new_capacity);
	}
}

void *VectorGetAccessToElement(const dynamic_vector_ty *vector, size_t index)
{
	assert(NULL != vector);

	if (index >= vector->size)
	{
		return NULL;
	}

	return (char *)vector->data + index * vector->size_of_element;
}

int VectorIsEmpty(const dynamic_vector_ty *vector)
{
	assert(NULL != vector);

	return 0 == vector->size;
}

size_t VectorSize(const dynamic_vector_ty *vector)
{
	assert(NULL != vector);

	return vector->size;
}

size_t VectorCapacity(const dynamic_vector_ty *vector)
{
	assert(NULL != vector);

	return vector->capacity;
}
