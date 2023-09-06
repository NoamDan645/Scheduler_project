#include <stdio.h>
#include <time.h>	   /*time_t*/
#include <sys/types.h> /*pid_t*/
#include "tasker.h"

/********************************************************/
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"
#define TEST(name, actual, expected) \
	printf("%s: %s\n\n", name, actual == expected ? GREEN "Pass" WHITE : RED "Fail" WHITE)

/*********************************************************/
int sample_task(void *param)
{
	printf("Running sample task with param: %d\n", *(int *)param);
	return 0;
}
void print_time(time_t curtime)
{
	curtime += 50000000;
	time(&curtime);
	printf("%s", ctime(&curtime));
}
void print_task(task_ty *task)
{
	int nameOfTask = 0;

	printf("param : %d\n", *(int *)task->param);
	printf("pid : %d counter : %lu timestamp : %lu \n", task->uid.pid, task->uid.counter, task->uid.timestamp);
	printf("inteval : %ld\n", task->interval);
	printf("time_to_run : %ld\n", task->time_to_run);

	printf("time_to_run : current Time + interval : ");
	print_time(task->time_to_run);

	printf("\n\n");
}

void test_TaskerCreate()
{
	size_t interval = 2;
	size_t param = 20;
	task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	task_ty *task3 = NULL;
	task_ty *task4 = NULL;

	task1 = TaskerCreate(sample_task, (&param), interval);
	print_task(task1);
	TaskerExecute(task1);
	TaskUpdateTimeToRun(task1);


	param = 10;
	interval = 4;
	task2 = TaskerCreate(sample_task, (&param), interval++);
	print_task(task2);
	TaskerExecute(task2);
	TaskUpdateTimeToRun(task2);

	param = 5;
	interval = 10;
	task3 = TaskerCreate(sample_task, (&param), interval);
	print_task(task3);
	TaskerExecute(task3);
	TaskUpdateTimeToRun(task3);


	param = 50;
	interval = 3;
	task4 = TaskerCreate(sample_task, (&param), interval);
	print_task(task4);
	TaskerExecute(task4);
	TaskUpdateTimeToRun(task4);


	printf("task is befor %d\n",TaskIsBefore(task1,task2));

	/**********************************************************/

	/***********************************************************/

	TaskerDestroy(task1);
	TaskerDestroy(task2);
	TaskerDestroy(task3);
	TaskerDestroy(task4);
}

int main()
{

	printf(CYAN "\tTest \n\n" WHITE);
	test_TaskerCreate();
	/* task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	task_ty *task3 = NULL;
	task_ty *task4 = NULL;

	int param_task_1 = 1;
	int param_task_2 = 2;
	int param_task_3 = 3;
	int param_task_4 = 4; */

	/*time_t time_to_run = 0;
	size_t interval = 3;
	int success = -1;

	task1 = TaskerCreate(func1, &param_task_1, 5);
	task2 = TaskerCreate(func2, &param_task_2, 10);
	task3 = TaskerCreate(func3, &param_task_3, 2);
	task4 = TaskerCreate(func4, &param_task_4, 7);

	TaskerExecute(task1);
	TaskerExecute(task2);
	TaskerExecute(task3);
	TaskerExecute(task4);

	TaskerDestroy(task1);
	TaskerDestroy(task2);
	TaskerDestroy(task3);
	TaskerDestroy(task4);
 */
	/* success = TaskerExecuteparam_task_4(task);

	printf("success = %d\n",success);

	uid = TaskerGetTaskUID(task);
 */

	return 0;
}
