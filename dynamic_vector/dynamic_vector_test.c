/*************************************************************
*
* Description: test for dynamic vector
*
******************************************************************/

#include <stdio.h> /* printf */
#include "dynamic_vector.h"

#define RESET   "\033[0m"        /* Reset colour */
#define RED     "\033[31m"       /* Red */
#define GREEN   "\033[32m"      /* Green */
#define White   "\033[37m"	    /* White */

#define CHECK(function, val, variable, input) val == variable ? printf(GREEN "%s worked succesfully for %s\n",function, input) : printf(RED "%s failed  for %s\n",function, input)

void TestCreateDestroy (void)
{	
	size_t cur_size;
	size_t cur_capacity;
	int a = 3;
	dynamic_vector_ty *vd_ptr = VectorCreate(5 , 4);
	int * peek_a = 	NULL;

	cur_size = VectorSize(vd_ptr);
	CHECK("VectorSize", 0,cur_size, "zero size at initailization");

	CHECK("VectorIsEmpty", 1,VectorIsEmpty(vd_ptr),"vector is empty at initailization");
	
	cur_capacity = VectorCapacity(vd_ptr);
	CHECK("VectorCapacity", 5, cur_capacity,"vector capacity as set in create at initailization");

	VectorPushBack(vd_ptr, &a);
	cur_size = VectorSize(vd_ptr);
	CHECK("VectorSize", 1,cur_size, "size +1 after push");

	peek_a = VectorGetAccessToElement(vd_ptr, 0);
	CHECK("VectorGetAccessToElement", 3,*peek_a, "get access after 1 push back");

	VectorDestroy(vd_ptr);
}

void TestPushPop (void)
{
	short * peek = 	NULL;
	short * peek2 = NULL;
	short a = 1;
	short b = 2;
	short c = 3; 
	dynamic_vector_ty *vd_ptr = VectorCreate(3 , 2);


	VectorPushBack(vd_ptr, &a);
	VectorPushBack(vd_ptr, &b);
	VectorPushBack(vd_ptr, &c);

	CHECK("VectorIsEmpty", 0,VectorIsEmpty(vd_ptr),"vector is not empty after push back");

	peek = VectorGetAccessToElement(vd_ptr, 2);
	CHECK("VectorSize", 3,VectorSize(vd_ptr), "size 3 - after 3 push back ");
	CHECK("VectorGetAccessToElement", 3,*peek, "get access after 3 push back");

	VectorPopBack(vd_ptr);
	peek = VectorGetAccessToElement(vd_ptr, 1);
	CHECK("VectorSize", 2,VectorSize(vd_ptr), "size 2 - after 3 push back and 1 pop back ");
	CHECK("VectorGetAccessToElement", 2,*peek, "get access after 3 push back and 1 pop back");
	
	VectorPopBack(vd_ptr);
	peek = VectorGetAccessToElement(vd_ptr, 0);
	CHECK("VectorSize", 1,VectorSize(vd_ptr), "size 1 - after 3 push back and 2 pop back ");
	CHECK("VectorGetAccessToElement", 1,*peek, "get access after 3 push back and 2 pop back");

	*peek = (short)12; 
	peek2 = VectorGetAccessToElement(vd_ptr, 0);
	CHECK("VectorGetAccessToElement", 12,*peek2, "get access and set different value");
	

	VectorPopBack(vd_ptr);
	CHECK("VectorIsEmpty", 1,VectorIsEmpty(vd_ptr),"vector is empty after all pop back");

	VectorDestroy(vd_ptr);	
}

void TestReseve (void)
{
	dynamic_vector_ty *vd_ptr = VectorCreate(6 , 4);
	CHECK("VectorCapacity", 6, VectorCapacity(vd_ptr),"vector capacity as set in create at initailization");

	vd_ptr =  VectorReserve(vd_ptr, 3);
	CHECK("VectorCapacity", 3, VectorCapacity(vd_ptr),"vector capacity as set in reserve - 3");

	vd_ptr =  VectorReserve(vd_ptr, 18);
	CHECK("VectorCapacity", 18, VectorCapacity(vd_ptr),"vector capacity as set in reserve - 18");

	CHECK("VectorIsEmpty", 1,VectorIsEmpty(vd_ptr),"vector is empty at initailization");

	VectorDestroy(vd_ptr);
}

void TestPolicy (void)
{
	char *peek = NULL;	
	dynamic_vector_ty *vd_ptr = VectorCreate(4 , 1);
	char a = 'a';
	char b = 'b';
	char c = 'c';
	char d = 'd'; 
	char e = 'e';

	VectorPushBack(vd_ptr, &a);
	VectorPushBack(vd_ptr, &b);
	VectorPushBack(vd_ptr, &c);
	VectorPushBack(vd_ptr, &d);

	CHECK("VectorCapacity", 4, VectorCapacity(vd_ptr),"vector capacity working lazy");
	
	VectorPushBack(vd_ptr, &e);
	CHECK("VectorCapacity", 8, VectorCapacity(vd_ptr),"vector capacity double the capacity");
	CHECK("VectorSize", 5,VectorSize(vd_ptr), "size 5 - after 5 push back ");
	peek = VectorGetAccessToElement(vd_ptr, 3);
	CHECK("VectorGetAccessToElement", 'd',*peek, "the last push value as accepected");

	vd_ptr =  VectorReserve(vd_ptr, 17 );
	CHECK("VectorCapacity", 17, VectorCapacity(vd_ptr),"vector capacity as set in reserve - 17");
	VectorPopBack(vd_ptr);	
	
	CHECK("VectorCapacity", 8, VectorCapacity(vd_ptr),"vector capacity shrinked in half");	

	VectorDestroy(vd_ptr);	
}

int main(void)
{
	printf (White" ----------CreateDestroy Test--------------\n");
	TestCreateDestroy();
	printf (White" ----------PushPop Test--------------\n");
	TestPushPop();
	printf (White" ----------Reseve Test--------------\n");
	TestReseve();
	printf (White" ----------Realloc Policy Test--------------\n");
	TestPolicy();

	return 0;
}




