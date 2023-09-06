
#include <stdio.h>
#include <assert.h>
#include <stddef.h> 
#include "scheduler.h"


typedef struct{
	scheduler_ty *scheduler;
	uid_ty uid;
}remove_iter_ty;

int Action_1(void *param);
int Action_stop(void *param);
int Action_remove(void *param);

/* void Consumer(scheduler_ty *scheduler)
{
 	assert(scheduler);
	SchedulerRun(scheduler);	
} */
int main()
{
	scheduler_ty *scheduler = SchedulerCreate();
	uid_ty uid_1 = {0,0,0}, uid_2 = {0,0,0}, uid_3 = {0,0,0}, uid_4 = {0,0,0}, uid_5 = {0,0,0};
	remove_iter_ty iter = {NULL,{0,0,0}};
	printf("test");
	assert(scheduler); 	
 
 	uid_1 = SchedulerAdd(scheduler, 1, Action_1, "---------------------> action 1"); 
	 uid_2 = SchedulerAdd(scheduler, 2, Action_1, "---------------------> action 2");
	uid_3 = SchedulerAdd(scheduler, 4, Action_1, "---------------------> action 3");
	uid_4 = SchedulerAdd(scheduler, 10, Action_stop, scheduler);  

/* 	iter.scheduler = scheduler;
	iter.uid = uid_3;
	uid_5 = SchedulerAdd(scheduler, 12, Action_remove, &iter); */

	/* printf("size of remove_iter_ty = %lu\n", sizeof(remove_iter_ty));
	Consumer(scheduler);

	SchedulerDestroy(scheduler); */

	return 0;
}

 
int Action_1(void *param)
{
	printf ("%s\n", (char *)param);
	return 0;
}
/*
int Action_stop(void *param)
{
    static size_t count = 0;
    if(1 >= ++count)
    {
        SchedulerStop((scheduler_ty *)param);
    }
	return 0;
}

int Action_remove(void *param)
{Action_1
	remove_iter_ty iter = *(remove_iter_ty *)param;	
	
	SchedulerRemove(iter.scheduler, iter.uid);
	
	return 0;
} */
