/*************************************************************
* OL124  uid number
* 
* Author: 
******************************************************************/
#include <stdio.h> /* printf */
#include <unistd.h> /*sleep*/
#include "uid.h"

#define RESET   "\033[0m"        /* Reset colour */
#define RED     "\033[31m"       /* Red */
#define GREEN   "\033[32m"      /* Green */


void TestUid(void)
{
	uid_ty id1; 
	uid_ty id2;
	
	id1 = GetUID();
	if (!UIDIsSame(id1, UID_INVALID))
	{
		printf (GREEN "Valid UID created for id1:\n");
		printf (" UID counter is: %lu\n",id1.counter);
		printf (" UID timestamp is: %ld\n",id1.timestamp);
		printf (" UID pid is: %d\n",id1.pid);
	}	
	else
	{
		printf (RED "InValid UID created for id1:\n");
	}

	sleep(2);
 
	id2 = GetUID();
	if (!UIDIsSame(id2, UID_INVALID))
	{
		printf (GREEN "Valid UID created for id2:\n");
		printf (" UID counter is: %lu\n",id2.counter);
		printf (" UID timestamp is: %ld\n",id2.timestamp);
		printf (" UID pid is: %d\n",id2.pid);
	}	
	else
	{
		printf (RED "InValid UID created for id2:\n");
	}

	if (!UIDIsSame(id1,id2))
	{
		printf (GREEN "id1 and id2 are not the same\n");
	}
	else
	{
		printf (RED "id1 and id2 ARE the same!!!\n");
	}

	printf(RESET);
}

int main(void)
{
	TestUid();

	return 0;
}

