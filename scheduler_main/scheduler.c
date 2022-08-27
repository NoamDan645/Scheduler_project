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
#include <time.h> /* time */
#include "pqueue.h" /* PQCreate, PQEnQueue, PQDeQueue... */
#include "scheduler.h"

#define SUCCESS 0
#define TIME_FAIL (time_t)-1

struct scheduler
{
	pqueue_ty *pque;
	int stop_to_run;
};

typedef struct
{
	time_t time_to_act;
	time_t time_interval_sec;
	task_ptr_ty task_function;
	void *param;
	uid_ty uid;
	
}task_man_ty;

/* ------------- inner functions ---------- */
/* compare function that prioritize smaller time*/
static int TimePriority(const void* a, const void* b)
{
	time_t a_time = 0;
	time_t b_time = 0;
	task_man_ty *task_a = (task_man_ty *)a;
	task_man_ty *task_b = (task_man_ty *)b;
	
	a_time = task_a->time_to_act;
	b_time = task_b->time_to_act;

	/* smaller is prioritize */
	return (b_time - a_time);
}

/* is_match to find the uid of the wanted task */
static int IsUidMatch(const void *task, const void *uid_to_find)
{
	task_man_ty *task_uid_extract = (task_man_ty *)task;
	uid_ty to_find = *(uid_ty *)uid_to_find;
	if (UIDIsSame(task_uid_extract->uid, to_find))
	{
		return 1;
	}
	return 0;
}

/***********************************************************************************
* --SchedulerCreate-- Create scheduler - return pointer to scheduler 
**************************************************************************************/

scheduler_ty *SchedulerCreate()
{
	scheduler_ty *sched = NULL;

	sched = malloc(sizeof(scheduler_ty));
	if (NULL == sched)
	{
		return NULL;
	}
		
	sched->pque = PQCreate(&TimePriority);
	if (NULL == sched->pque)
	{
		return NULL;
	}
	sched->stop_to_run = 0;

	return sched;
}

/* ************************************************************************************
* --SchedulerAdd-- Add task to the scheduler return uid to this task. 
* if fail return UID_INVALID
*
**************************************************************************************/

uid_ty SchedulerAdd(scheduler_ty *scheduler, size_t interval_in_sec, task_ptr_ty task_func, void* param)
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

	if(SUCCESS != PQEnQueue(scheduler->pque,new_task))
	{
		free(new_task);
		return UID_INVALID;
	}
	return new_task->uid;
}

/*************************************************************************************
*--SchedulerRun-- Run task. return 0 for success, 1 for failiure
**************************************************************************************/
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
	{	/* get task to do now and get it out of pqueue */
		cur_task = (task_man_ty *)PQDeQueue(scheduler->pque);

		if (cur_task->time_to_act + start_run_time > current_time)
		{
			to_sleep = (cur_task->time_to_act + start_run_time) - current_time;
		}
		else
		{
			to_sleep = 0;
		}	

		/* wait as much as needed */
		sleep(to_sleep);

		/* do the task */
		if(SUCCESS == cur_task->task_function(cur_task->param))
		{
			PQEnQueue(scheduler->pque, cur_task);
			return 1;
		}

		/* check flag for break*/
		if (scheduler->stop_to_run)
		{
			if(SUCCESS != PQEnQueue(scheduler->pque, cur_task))
			{
				return 1;
			}
			break;	
		}

		/* update time to do cur task for next time this task will be executed */
		cur_task->time_to_act += cur_task->time_interval_sec;

		if(SUCCESS != PQEnQueue(scheduler->pque, cur_task))
		{
			return 1;
		}
		/* get updated time */
		current_time = time(NULL);
		if (current_time == TIME_FAIL)
		{
			return 1;
		} 
	}
	return 0;
}


/*************************************************************************************
*--SchedulerRemove-- Remove task with uid from scheduler
**************************************************************************************/
void SchedulerRemove(scheduler_ty *scheduler, uid_ty uid)
{
	uid_ty *uid_to_find = NULL;
	task_man_ty *task_to_remove = NULL;
	assert(scheduler);
	assert(!UIDIsSame(UID_INVALID,uid));

	uid_to_find = &uid;	
	task_to_remove = (task_man_ty *)PQErase(scheduler->pque, &IsUidMatch, uid_to_find);
	free(task_to_remove);
}

/*************************************************************************************
*--SchedulerStop-- Stop task.
**************************************************************************************/
void SchedulerStop(scheduler_ty *scheduler)
{
	assert(scheduler);
	scheduler->stop_to_run = 1;
}

/*************************************************************************************
*--SchedulerDestroy-- Delete scheduler 
*************************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(scheduler);

	SchedulerClear(scheduler);
	PQDestroy(scheduler->pque);
	free(scheduler);
}


/*************************************************************************************
* --SchedulerIsEmpty-- returns 1 in case is empty or 0 otherwise
**************************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(scheduler);
	return PQIsEmpty(scheduler->pque);
}

/*************************************************************************************
* --SchedulerSize-- returns the size of the Scheduler
**************************************************************************************/
size_t SchedulerSize(const scheduler_ty *scheduler)
{
	assert(scheduler);
	return PQSize(scheduler->pque);
}

/*************************************************************************************
* --SchedulerClear-- remove all tasks in scheduler.
**************************************************************************************/
void SchedulerClear(scheduler_ty *scheduler)
{
	assert(scheduler);
	while(!SchedulerIsEmpty(scheduler))
	{
		free(PQDeQueue(scheduler->pque));
	}
}