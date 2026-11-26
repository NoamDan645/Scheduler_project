/*************************************************************
 * Task
 *
 * Author: Noam Hadad
 ******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "tasker.h"

struct task
{
	task_ptr_ty func;
	void *param;
	uid_ty uid;
	size_t interval;
	time_t next_call;
};

task_ty *TaskerCreate(task_ptr_ty func_task, void *param, size_t interval)
{
	task_ty *task = NULL;
	time_t now = time(NULL);

	assert(NULL != func_task);

	if ((time_t)-1 == now)
	{
		return NULL;
	}

	task = (task_ty *)malloc(sizeof(task_ty));
	if (NULL == task)
	{
		return NULL;
	}

	task->uid = createUid();
	if (UIDIsSame(task->uid, UID_INVALID))
	{
		free(task);
		return NULL;
	}

	task->func = func_task;
	task->param = param;
	task->interval = interval;
	task->next_call = now + (time_t)interval;

	return task;
}

void TaskerDestroy(task_ty *task)
{
	free(task);
}

int TaskerExecute(task_ty *task)
{
	assert(NULL != task);

	return task->func(task->param);
}

uid_ty TaskerGetTaskUID(const task_ty *task)
{
	assert(NULL != task);

	return task->uid;
}

int TaskerUIDIsMatch(const task_ty *task, uid_ty uid)
{
	assert(NULL != task);

	return UIDIsSame(task->uid, uid);
}

time_t TaskerGetNextCall(const task_ty *task)
{
	assert(NULL != task);

	return task->next_call;
}

void TaskUpdateTimeToRun(task_ty *task, time_t now)
{
	assert(NULL != task);

	task->next_call = now + (time_t)task->interval;
}

int TaskIsBefore(const void *task1, const void *task2)
{
	time_t t1 = 0;
	time_t t2 = 0;

	assert(NULL != task1);
	assert(NULL != task2);

	t1 = ((const task_ty *)task1)->next_call;
	t2 = ((const task_ty *)task2)->next_call;

	return (t1 < t2) - (t1 > t2);
}
