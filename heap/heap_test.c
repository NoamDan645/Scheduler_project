#include "heap.h"
#include "../tests/test_utils.h"

/* max-heap on ints */
static int IntCmp(const void *a, const void *b)
{
	int x = *(const int *)a;
	int y = *(const int *)b;

	return (x > y) - (x < y);
}

static int IntIsMatch(const void *data, const void *param)
{
	return *(const int *)data == *(const int *)param;
}

int main(void)
{
	int values[] = {10, 6, 20, 65, 80, 5, 3, 100, 300, 201, 12, 2, 7, 7};
	size_t n = sizeof(values) / sizeof(values[0]);
	heap_ty *heap = HEAPCreate(IntCmp);
	int last = 0;
	int key = 0;
	size_t i = 0;

	CHECK(NULL != heap);
	CHECK(HEAPIsEmpty(heap));
	CHECK(NULL == HEAPPeek(heap));
	HEAPPop(heap); /* no-op on empty heap */

	for (i = 0; i < n; ++i)
	{
		CHECK(0 == HEAPPush(heap, &values[i]));
	}
	CHECK(n == HEAPSize(heap));
	CHECK(300 == *(int *)HEAPPeek(heap));

	key = 65;
	CHECK(&values[3] == HEAPRemove(heap, &key, IntIsMatch));
	key = 999;
	CHECK(NULL == HEAPRemove(heap, &key, IntIsMatch));
	CHECK(n - 1 == HEAPSize(heap));

	/* pops come out in non-increasing order */
	last = *(int *)HEAPPeek(heap);
	while (!HEAPIsEmpty(heap))
	{
		int top = *(int *)HEAPPeek(heap);

		CHECK(top <= last);
		CHECK(65 != top);
		last = top;
		HEAPPop(heap);
	}
	CHECK(2 == last);

	HEAPDestroy(heap);
	return TEST_RESULT("heap");
}
