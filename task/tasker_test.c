#include <stdio.h>
#include <time.h>   /*time_t*/
#include <sys/types.h>    /*pid_t*/

/*#include "uid.h"*/
#include "tasker.h"


int func(void *param)
{
	printf("Task0: %d\n", *(int *)param);

	return (0);
}
int func1(void *param)
{
	printf("Task1: %d\n", *(int *)param);

	return (0);
}
int func2(void *param)
{
	printf("Task2: %d\n", *(int *)param);

	return (0);
}




task_ty* TestTaskerCreate()
{
	uid_ty uid = GetUID();
	
	int param = 10;
	
	size_t interval = 5;
	
	task_ty *task = NULL;

	task = TaskerCreate(uid, func, &param, interval);
	
	return task;
}


int main()
{
	task_ty *task = NULL;

	int success = -1;

	uid_ty uid = {0};

	task = TestTaskerCreate();

 	success = TaskerExecute(task);
	
	printf("success = %d\n",success);

	uid = TaskerGetTaskUID(task);


	return 0;
}

