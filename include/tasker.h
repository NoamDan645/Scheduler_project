
#ifndef TASK_H
#define TASK_H

#include <stddef.h> /* size_t */
#include <time.h>
#include "uid.h" /* uid_ty */

/* typedef struct task task_ty;
 */
typedef int (*task_ptr_ty)(void *param);
typedef void (*task_destroy)(uid_ty uid, void *param);

typedef struct task
{
    void *param;
    uid_ty uid;
    task_ptr_ty func;
    size_t interval;
    time_t next_call;
    time_t time_to_run;
} task_ty;



task_ty *TaskerCreate(task_ptr_ty func_task, void *param, size_t interval);

void TaskerDestroy(task_ty *task);

time_t TaskerGetNextCall(task_ty *task);

int TaskerExecute(task_ty *task);

unsigned int TaskerDiffTime(task_ty *task1, task_ty *task2);

uid_ty TaskerGetTaskUID(task_ty *task);

int TaskerUIDIsMatch(task_ty *task, uid_ty uid);

time_t TaskSetActTime(task_ty *task, time_t time_of_act);

void TaskUpdateTimeToRun(task_ty *task);

int TaskIsBefore(const void *task1, const void *task2);

#endif
