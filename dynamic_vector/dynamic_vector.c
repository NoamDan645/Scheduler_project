
#include <stdlib.h> /* malloc, free, realloc */
#include <string.h> /* memcpy */
#include "dynamic_vector.h"


#define ADDED_SIZE 2
#define LIMIT  0.25
#define LOWER 0.5


struct dynamic_vector
{
    void *data;
    size_t size;
    size_t capacity;
    size_t size_of_element;
};

/*  Auxiliary functions */
static int VectorIsFull(dynamic_vector_ty *vector)
{
	return vector->size == vector->capacity;
}

/*************************************************************************************
* ---VectorCreate---returns the *ptr to an object <dynamic_vector_ty *> type in case of success
*  or NULL in case of Failure
**************************************************************************************/
dynamic_vector_ty *VectorCreate(size_t capacity , size_t size_of_element)
{	
	dynamic_vector_ty *vector = malloc(sizeof(dynamic_vector_ty));
	
	if(NULL == vector)
	{
		return NULL;
	}	
	vector->data = malloc(capacity * size_of_element);
	
	if(NULL == vector->data)
	{
		free(vector);
		return NULL;
	}
	
	vector->size =0;
	
	vector->capacity = capacity;
	
	vector->size_of_element = size_of_element;
	
	return vector;
}

/*************************************************************************************
* ---VectorDestroy--- releases the dynamic_vector_ty *ptr and to all its allocated memory
**************************************************************************************/
void VectorDestroy(dynamic_vector_ty *vector)
{
	free(vector->data);
	free(vector);
}

/*************************************************************************************
* ---VectorReserve--- allocates new capacity to the vector,
* returns <dynamic_vector_ty *ptr> or NULL in case of Failure
**************************************************************************************/
dynamic_vector_ty *VectorReserve(dynamic_vector_ty *vector, size_t new_capacity)
{
	dynamic_vector_ty *new_vector = realloc(vector->data,vector->size_of_element * new_capacity);

	if (NULL == new_vector)
	{
		return NULL;
	}
	vector->data = new_vector;
	
	vector->capacity = new_capacity;
	
	return vector;	
}
/*************************************************************************************
* ---VectorPushBack--- makes PUSH to end of the vector, in case of FULLVECTOR 
* allocates new memory size and copy to new size beginning from "head"
**************************************************************************************/
int VectorPushBack(dynamic_vector_ty *vector, void *element)
{	
	if(VectorIsFull(vector))
	{
		dynamic_vector_ty *test= VectorReserve(vector,(vector->capacity * ADDED_SIZE));
		
		if( NULL == test)
		{
			return 1;
		}
	}
	memcpy((char*)vector->data + vector->size * vector->size_of_element, element, vector->size_of_element);
	
	vector->size++;
	
	return 0;
}


/*************************************************************************************
* ---VectorPopBack--- "deletes" the LAST element in the DYNAMIC_VECTOR 
**************************************************************************************/
void VectorPopBack(dynamic_vector_ty *vector)
{
	if (!VectorIsEmpty(vector))
	{
		vector->size--;	
	}
	if (vector->size < (vector->capacity * LIMIT)) /* capacity x 0.25 */
	{
		VectorReserve(vector,vector->capacity * LOWER);
	}
}

/*************************************************************************************
* ---GetAccessToElement--- returns <void *ptr> to element[index] and ,
* in case of out of range returns NULL
**************************************************************************************/
void *VectorGetAccessToElement(const dynamic_vector_ty *vector, size_t index)
{
	return (char*)vector->data + index * vector->size_of_element;
}


/*************************************************************************************
* ---VectorIsEmpty--- if the vector is EMPTY returns 1, if not returns 0, 
**************************************************************************************/
int VectorIsEmpty(const dynamic_vector_ty *vector)
{
	return (vector->size == 0);
}
/*************************************************************************************
* ---VectorSize--- returns the size of the vector 
**************************************************************************************/
size_t VectorSize(const dynamic_vector_ty *vector)
{
	return vector->size;
}

/*************************************************************************************
* ---VectorCapacity--- returns the capacity of the vector 
**************************************************************************************/
size_t VectorCapacity(const dynamic_vector_ty *vector)
{
		return vector->capacity;
}


