#include <stdlib.h> 
#include <assert.h> 
#include <time.h>   

#include "tasker.h"
#include "uid.h"

/*
typedef struct task
{
	uid_ty  uid;

	task_ptr_ty func;
	void *param;
	size_t interval;
	time_t next_call;

}task_ty;*/

task_ty *TaskerCreate(uid_ty uid, task_ptr_ty func, void *param, size_t interval)
{
	task_ty *task = (task_ty*)malloc(sizeof(task_ty));

	if (NULL == task)
	{
		return (NULL);
	}

	task->uid = uid;
	task->func = func;
	task->param = param;
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
	assert(NULL != task);
	return task->next_call;
}

int TaskerExecute(task_ty *task)
{
	assert(NULL != task);
	return (task->func(task->param));
}

uid_ty TaskerGetTaskUID(task_ty *task)
{	
	assert(NULL != task);
	return task->uid;
}
unsigned int TaskerDiffTime(task_ty *task1, task_ty *task2)
{
	return (difftime(task1->next_call, task2->next_call));
}

int TaskerUIDIsMatch(task_ty *task, uid_ty uid)
{
	return (UIDIsSame(task->uid, uid));
}









