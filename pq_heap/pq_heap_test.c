#include "pqueue.h"
#include "../tests/test_utils.h"

/* smaller number = higher priority */
static int MinFirst(const void *a, const void *b)
{
	int x = *(const int *)a;
	int y = *(const int *)b;

	return (x < y) - (x > y);
}

static int IsEven(const void *data, const void *param)
{
	(void)param;
	return 0 == *(const int *)data % 2;
}

int main(void)
{
	int values[] = {11, 3, 15, 7, 17, 56, 2, 22, 66};
	size_t n = sizeof(values) / sizeof(values[0]);
	pqueue_ty *pq = PQCreate(MinFirst);
	int last = 0;
	size_t i = 0;

	CHECK(NULL != pq);
	CHECK(PQIsEmpty(pq));
	CHECK(NULL == PQPeek(pq));
	CHECK(NULL == PQDeQueue(pq));

	for (i = 0; i < n; ++i)
	{
		CHECK(0 == PQEnQueue(pq, &values[i]));
	}
	CHECK(n == PQSize(pq));
	CHECK(2 == *(const int *)PQPeek(pq));

	/* erase every even number */
	while (NULL != PQErase(pq, IsEven, NULL))
	{
	}
	CHECK(5 == PQSize(pq));

	last = 0;
	while (!PQIsEmpty(pq))
	{
		int value = *(int *)PQDeQueue(pq);

		CHECK(value >= last);
		CHECK(1 == value % 2);
		last = value;
	}
	CHECK(17 == last);

	PQDestroy(pq);
	return TEST_RESULT("pq_heap");
}
