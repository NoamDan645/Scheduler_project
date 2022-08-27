/*************************************************************
* project Scheduler
* 
* scheduler.h
* scheduler.c
* scheduler_test.c
* 
*Version 1.3 
******************************************************************/

#ifndef OL124_SCHEDULER_H
#define OL124_SCHEDULER_H

#include <stddef.h> 

#include "uid.h" /* uid_ty */
#include "tasker.h"

/* task_prt_ty return 0 for success, or 1 for failiure */
typedef struct scheduler scheduler_ty;

typedef int (*func_ty)(void *param);

/***********************************************************************************
*--SchedulerCreate-- Create scheduler - return pointer to scheduler. 
*if fail return NULL
**************************************************************************************/
scheduler_ty *SchedulerCreate();

/*************************************************************************************
* --SchedulerAdd-- Add task to the scheduler return uid to this task. 
*if fail return UID_INVALID
*
**************************************************************************************/
uid_ty SchedulerAdd(scheduler_ty *scheduler, size_t interval_in_sec, task_ptr_ty task_func, void* param);

/*************************************************************************************
*--SchedulerRun-- Run task. return 0 for success, 1 for failiure
**************************************************************************************/
int SchedulerRun(scheduler_ty *scheduler);

/*************************************************************************************
*--SchedulerStop-- Stop task.
**************************************************************************************/
void SchedulerStop(scheduler_ty *scheduler);

/*************************************************************************************
*--SchedulerRemove-- Remove task with uid from scheduler
**************************************************************************************/
void SchedulerRemove(scheduler_ty *scheduler, uid_ty uid);

/*************************************************************************************
*--SchedulerDestroy-- Delete scheduler 
*************************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler);

/*************************************************************************************
* --SchedulerIsEmpty-- returns 1 in case is empty or 0 otherwise
**************************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler);

/*************************************************************************************
* --SchedulerSize-- returns the size of the Scheduler
**************************************************************************************/
size_t SchedulerSize(const scheduler_ty *scheduler);

/*************************************************************************************
* --SchedulerClear-- remove all tasks in scheduler.
**************************************************************************************/
void SchedulerClear(scheduler_ty *scheduler); 


#endif /*SCHEDULER_H */
