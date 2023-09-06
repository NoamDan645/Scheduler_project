#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include "tasker.h"
#include "uid.h"

/* struct task
{
	void *param;
	uid_ty uid;
	task_ptr_ty func;
	size_t interval;
	time_t next_call;
	time_t time_to_run;
};
 */
task_ty *TaskerCreate(task_ptr_ty func_task, void *param, size_t interval)
{
	task_ty *task = NULL;
	assert(param);

	if (NULL == (task = (task_ty *)malloc(sizeof(task_ty))))
		return NULL;

	task->uid = createUid();
	task->func = func_task;
	task->param = param;
	task->time_to_run = time(NULL) + interval;
	task->interval = interval;

	return task;
}

void TaskerDestroy(task_ty *task)
{
	if (NULL != task)
	{
		free(task);
		task = NULL;
	}
}

time_t TaskerGetNextCall(task_ty *task)
{
	assert(task);
	return task->next_call;
}

int TaskerExecute(task_ty *task)
{
	assert(task);

	return (task->func(task->param));
}

uid_ty TaskerGetTaskUID(task_ty *task)
{
	assert(task);
	return task->uid;
}
unsigned int TaskerDiffTime(task_ty *task1, task_ty *task2)
{
	assert(task1);
	assert(task2);

	return (difftime(task1->next_call, task2->next_call));
}

int TaskerUIDIsMatch(task_ty *task, uid_ty uid)
{
	assert(task);

	return (UIDIsSame(task->uid, uid));
}

void TaskUpdateTimeToRun(task_ty *task)
{
	assert(task);

	task->time_to_run = time(NULL) + task->interval;
}

int TaskIsBefore(const void *task1, const void *task2)
{
	assert(task1);
	assert(task2);
	
	return (((task_ty *)task1)->time_to_run - ((task_ty *)task2)->time_to_run) > 0 ? 1 : -1;
}
