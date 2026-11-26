/*************************************************************
 * Task
 *
 * A function to call every `interval` seconds, with its parameter,
 * a unique id and the time of its next run.
 ******************************************************************/

#ifndef TASK_H
#define TASK_H

#include <stddef.h> /* size_t */
#include <time.h>   /* time_t */

#include "uid.h" /* uid_ty */

/* Return 0 to keep the task scheduled, or non-zero to remove it. */
typedef int (*task_ptr_ty)(void *param);

typedef struct task task_ty;

/* Returns NULL on allocation failure. The first run is `interval`
 * seconds from now. */
task_ty *TaskerCreate(task_ptr_ty func_task, void *param, size_t interval);
void TaskerDestroy(task_ty *task);

/* Runs the task function and returns its result. */
int TaskerExecute(task_ty *task);

uid_ty TaskerGetTaskUID(const task_ty *task);
int TaskerUIDIsMatch(const task_ty *task, uid_ty uid);

time_t TaskerGetNextCall(const task_ty *task);
/* Schedules the next run `interval` seconds after `now`. */
void TaskUpdateTimeToRun(task_ty *task, time_t now);

/* Priority compare for the scheduler queue: positive if task1 should
 * run before task2, negative if after, 0 if at the same time. */
int TaskIsBefore(const void *task1, const void *task2);

#endif /* TASK_H */
