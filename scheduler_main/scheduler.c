/*************************************************************
 * project Scheduler
 *
 * Author: Noam Hadad
 *
 * Description:  implement Scheduler
 *
 ******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* sleep */
#include <time.h>	/* time */
#include "pqueue.h" /* PQCreate, PQEnQueue, PQDeQueue... */
#include "scheduler.h"
#include "tasker.h"

#define SUCCESS 0
#define TIME_FAIL (time_t) - 1

struct scheduler
{
	pqueue_ty *tasks;
	task_ty *current_task;
	int remove_task;
	int stop_to_run;
};

typedef struct
{
	time_t time_to_act;
	time_t time_interval_sec;
	task_ptr_ty task_function;
	void *param;
	uid_ty uid;

} task_man_ty;
/* 
static int TimePriority(const void *a, const void *b)
{

	task_ty *task_a = (task_ty *)a;
	task_ty *task_b = (task_ty *)b;

	time_t a_time = task_a->interval;
	time_t b_time = task_b->time_to_act;

	return (b_time - a_time);
}

static int IsUidMatch(const void *task, const void *uid_to_find)
{
	task_ty *task_uid_extract = (task_ty *)task;
	uid_ty to_find = *(uid_ty *)uid_to_find;
	if (UIDIsSame(task_uid_extract->uid, to_find))
	{
		return 1;
	}
	return 0;
}
 */
scheduler_ty *SchedulerCreate()
{
	scheduler_ty *scheduler = NULL;

	scheduler = (scheduler_ty *)malloc(sizeof(scheduler_ty));
	if (NULL == scheduler)
	{
		return NULL;
	}

	scheduler->tasks = PQCreate(&TaskIsBefore);

	if (NULL == scheduler->tasks)
	{
		return NULL;
	}
	scheduler->current_task = NULL;
	scheduler->remove_task = 0;
	scheduler->stop_to_run = 0;

	return scheduler;
}

/* uid_ty SchedulerAdd(scheduler_ty *scheduler, size_t interval_in_sec, task_ptr_ty task_func, void *param)
{
	task_man_ty *new_task = NULL;

	assert(scheduler);
	assert(task_func);
	assert(param);

	new_task = malloc(sizeof(task_man_ty));
	if (NULL == new_task)
	{
		return UID_INVALID;
	}
	new_task->time_to_act = interval_in_sec;
	new_task->time_interval_sec = interval_in_sec;
	new_task->task_function = task_func;
	new_task->param = param;
	new_task->uid = GetUID();

	if (SUCCESS != PQEnQueue(scheduler->, new_task))
	{
		free(new_task);
		return UID_INVALID;
	}
	return new_task->uid;
} */
/* 
int SchedulerRun(scheduler_ty *scheduler)
{
	task_man_ty *cur_task = NULL;
	time_t current_time = 0;
	time_t start_run_time = 0;
	time_t to_sleep = 0;

	assert(scheduler);

	start_run_time = time(NULL);

	if (start_run_time == TIME_FAIL)
	{
		return 1;
	}

	current_time = start_run_time;
	while (1)
	{
		cur_task = (task_man_ty *)PQDeQueue(scheduler->pque);

		if (cur_task->time_to_act + start_run_time > current_time)
		{
			to_sleep = (cur_task->time_to_act + start_run_time) - current_time;
		}
		else
		{
			to_sleep = 0;
		}

		sleep(to_sleep);

		if (SUCCESS == cur_task->task_function(cur_task->param))
		{
			PQEnQueue(scheduler->pque, cur_task);
			return 1;
		}

		if (scheduler->stop_to_run)
		{
			if (SUCCESS != PQEnQueue(scheduler->pque, cur_task))
			{
				return 1;
			}
			break;
		}

		cur_task->time_to_act += cur_task->time_interval_sec;

		if (SUCCESS != PQEnQueue(scheduler->pque, cur_task))
		{
			return 1;
		}

		current_time = time(NULL);
		if (current_time == TIME_FAIL)
		{
			return 1;
		}
	}
	return 0;
}

void SchedulerRemove(scheduler_ty *scheduler, uid_ty uid)
{
	uid_ty *uid_to_find = NULL;
	task_man_ty *task_to_remove = NULL;
	assert(scheduler);
	assert(!UIDIsSame(UID_INVALID, uid));

	uid_to_find = &uid;
	task_to_remove = (task_man_ty *)PQErase(scheduler->pque, &IsUidMatch, uid_to_find);
	free(task_to_remove);
}

void SchedulerStop(scheduler_ty *scheduler)
{
	assert(scheduler);
	scheduler->stop_to_run = 1;
}

void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(scheduler);

	SchedulerClear(scheduler);
	PQDestroy(scheduler->pque);
	free(scheduler);
}

int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	return PQIsEmpty(scheduler->tasks);
}

size_t SchedulerSize(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler ;
	return PQSize(scheduler->tasks);
}

void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *task = NULL;
	assert(NULL != scheduler);

	scheduler->remove_task = 1;

	while (0 == SchedulerIsEmpty(scheduler))
	{
		task = (task_ty *)PQDeQueue(scheduler->tasks);
		free(task);
	}
} */