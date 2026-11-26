#include "tasker.h"
#include "../tests/test_utils.h"

static int AddOne(void *param)
{
	++*(int *)param;
	return 0;
}

int main(void)
{
	int counter = 0;
	time_t now = time(NULL);
	task_ty *soon = TaskerCreate(AddOne, &counter, 1);
	task_ty *later = TaskerCreate(AddOne, &counter, 10);

	CHECK(NULL != soon && NULL != later);
	CHECK(TaskerGetNextCall(soon) >= now + 1);
	CHECK(TaskerGetNextCall(later) >= now + 10);

	CHECK(0 < TaskIsBefore(soon, later));
	CHECK(0 > TaskIsBefore(later, soon));
	CHECK(0 == TaskIsBefore(soon, soon));

	CHECK(0 == TaskerExecute(soon));
	CHECK(1 == counter);

	CHECK(TaskerUIDIsMatch(soon, TaskerGetTaskUID(soon)));
	CHECK(!TaskerUIDIsMatch(soon, TaskerGetTaskUID(later)));

	TaskUpdateTimeToRun(soon, now + 100);
	CHECK(now + 101 == TaskerGetNextCall(soon));
	CHECK(0 > TaskIsBefore(soon, later));

	TaskerDestroy(soon);
	TaskerDestroy(later);
	return TEST_RESULT("tasker");
}
