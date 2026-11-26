#include "dynamic_vector.h"
#include "../tests/test_utils.h"

int main(void)
{
	dynamic_vector_ty *v = VectorCreate(2, sizeof(int));
	int i = 0;

	CHECK(NULL != v);
	CHECK(VectorIsEmpty(v));
	CHECK(2 == VectorCapacity(v));

	for (i = 0; i < 100; ++i)
	{
		CHECK(0 == VectorPushBack(v, &i));
	}
	CHECK(100 == VectorSize(v));
	CHECK(VectorCapacity(v) >= 100);

	for (i = 0; i < 100; ++i)
	{
		CHECK(i == *(int *)VectorGetAccessToElement(v, (size_t)i));
	}
	CHECK(NULL == VectorGetAccessToElement(v, 100));

	for (i = 0; i < 100; ++i)
	{
		VectorPopBack(v);
	}
	CHECK(VectorIsEmpty(v));
	CHECK(VectorCapacity(v) >= 2); /* never shrinks below the start */
	VectorPopBack(v);              /* popping an empty vector is a no-op */
	CHECK(0 == VectorSize(v));

	CHECK(0 == VectorPushBack(v, &i));
	CHECK(100 == *(int *)VectorGetAccessToElement(v, 0));

	VectorDestroy(v);
	return TEST_RESULT("dynamic_vector");
}
