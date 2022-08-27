/*************************************************************************************
* Dynamic_Vector Project
* realloc policy:
* - size > 100: 
*               if (new capacity size <= 0.9*capacity)
*                   reserve =  1.3 *capacity
*               if (size >= 0.9*capacity)
* 
*   
*************************************************************************************/
#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <stddef.h>

typedef struct dynamic_vector dynamic_vector_ty;

/*************************************************************************************
* ---VectorCreate---returns the *ptr to an object <dynamic_vector_ty *> type in case of success
*  or NULL in case of Failure
**************************************************************************************/
dynamic_vector_ty *VectorCreate(size_t capacity , size_t size_of_element); 

/*************************************************************************************
* ---VectorDestroy--- releases the dynamic_vector_ty *ptr and to all its allocated memory
**************************************************************************************/
void VectorDestroy(dynamic_vector_ty *vector);

/*************************************************************************************
* ---VectorReserve--- allocates new capacity to the vector,
* returns <dynamic_vector_ty *ptr> or NULL in case of Failure
**************************************************************************************/
dynamic_vector_ty *VectorReserve(dynamic_vector_ty *vector, size_t new_capacity);

/*************************************************************************************
* ---VectorPushBack--- makes PUSH to end of the vector, in case of FULLVECTOR 
* allocates new memory size and copy to new size beginning from "head"
**************************************************************************************/
int VectorPushBack(dynamic_vector_ty *vector, void *element);

/*************************************************************************************
* ---VectorPopBack--- "deletes" the LAST element in the DYNAMIC_VECTOR 
**************************************************************************************/
void VectorPopBack(dynamic_vector_ty *vector);

/*************************************************************************************
* ---GetAccessToElement--- returns <void *ptr> to element[index] and ,
* in case of out of range returns NULL
**************************************************************************************/
void *VectorGetAccessToElement(const dynamic_vector_ty *vector, size_t index);

/*************************************************************************************
* ---VectorIsEmpty--- if the vector is EMPTY returns 1, if not returns 0, 
**************************************************************************************/
int VectorIsEmpty(const dynamic_vector_ty *vector);

/*************************************************************************************
* ---VectorSize--- returns the size of the vector 
**************************************************************************************/
size_t VectorSize(const dynamic_vector_ty *vector);

/*************************************************************************************
* ---VectorCapacity--- returns the capacity of the vector 
**************************************************************************************/
size_t VectorCapacity(const dynamic_vector_ty *vector);


#endif /*DYNAMIC_VECTOR_H*/








