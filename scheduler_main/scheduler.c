/*************************************************************
 * Scheduler
 *
 * Author: Noam Hadad
 *
 * Runs tasks at fixed intervals. Tasks wait in a priority queue
 * (binary heap) ordered by their next run time.
 ******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <time.h>   /* time */
#include <unistd.h> /* sleep */

#include "pqueue.h"
#include "scheduler.h"
#include "tasker.h"

struct scheduler
{
	pqueue_ty *tasks;
	task_ty *current_task;  /* task being executed, NULL otherwise */
	int remove_current;     /* the current task asked to be removed */
	int stop;
};

static int IsUidMatch(const void *task, const void *uid)
{
	return TaskerUIDIsMatch((const task_ty *)task, *(const uid_ty *)uid);
}

/* Sleeps until `when`. Restarts after an early wake-up from a signal. */
static int SleepUntil(time_t when)
{
	time_t now = time(NULL);

	if ((time_t)-1 == now)
	{
		return 1;
	}

	while (now < when)
	{
		sleep((unsigned int)(when - now));

		now = time(NULL);
		if ((time_t)-1 == now)
		{
			return 1;
		}
	}

	return 0;
}

scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *scheduler = (scheduler_ty *)malloc(sizeof(scheduler_ty));

	if (NULL == scheduler)
	{
		return NULL;
	}

	scheduler->tasks = PQCreate(TaskIsBefore);
	if (NULL == scheduler->tasks)
	{
		free(scheduler);
		return NULL;
	}

	scheduler->current_task = NULL;
	scheduler->remove_current = 0;
	scheduler->stop = 0;

	return scheduler;
}

uid_ty SchedulerAdd(scheduler_ty *scheduler, size_t interval_in_sec,
					task_ptr_ty task_func, void *param)
{
	task_ty *task = NULL;

	assert(NULL != scheduler);
	assert(NULL != task_func);

	task = TaskerCreate(task_func, param, interval_in_sec);
	if (NULL == task)
	{
		return UID_INVALID;
	}

	if (0 != PQEnQueue(scheduler->tasks, task))
	{
		TaskerDestroy(task);
		return UID_INVALID;
	}

	return TaskerGetTaskUID(task);
}

int SchedulerRun(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);

	scheduler->stop = 0;

	while (!scheduler->stop && !PQIsEmpty(scheduler->tasks))
	{
		task_ty *task = (task_ty *)PQPeek(scheduler->tasks);
		int result = 0;

		if (0 != SleepUntil(TaskerGetNextCall(task)))
		{
			return 1;
		}

		PQDeQueue(scheduler->tasks);
		scheduler->current_task = task;
		scheduler->remove_current = 0;

		result = TaskerExecute(task);

		scheduler->current_task = NULL;

		if (0 != result || scheduler->remove_current)
		{
			TaskerDestroy(task);
			continue;
		}

		TaskUpdateTimeToRun(task, time(NULL));
		if (0 != PQEnQueue(scheduler->tasks, task))
		{
			TaskerDestroy(task);
			return 1;
		}
	}

	return 0;
}

void SchedulerStop(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);

	scheduler->stop = 1;
}

void SchedulerRemove(scheduler_ty *scheduler, uid_ty uid)
{
	task_ty *task = NULL;

	assert(NULL != scheduler);

	/* a task that removes itself is not in the queue while it runs */
	if (NULL != scheduler->current_task &&
		TaskerUIDIsMatch(scheduler->current_task, uid))
	{
		scheduler->remove_current = 1;
		return;
	}

	task = (task_ty *)PQErase(scheduler->tasks, IsUidMatch, &uid);
	TaskerDestroy(task);
}

void SchedulerClear(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);

	while (!PQIsEmpty(scheduler->tasks))
	{
		TaskerDestroy((task_ty *)PQDeQueue(scheduler->tasks));
	}

	if (NULL != scheduler->current_task)
	{
		scheduler->remove_current = 1;
	}
}

void SchedulerDestroy(scheduler_ty *scheduler)
{
	if (NULL == scheduler)
	{
		return;
	}

	SchedulerClear(scheduler);
	PQDestroy(scheduler->tasks);
	free(scheduler);
}

int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);

	return PQIsEmpty(scheduler->tasks);
}

size_t SchedulerSize(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);

	return PQSize(scheduler->tasks);
}
