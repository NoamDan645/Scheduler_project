/*************************************************************
* OL124  uid number
* 
* Author: 
******************************************************************/
#include <stdio.h> /* printf */
#include <unistd.h> /*sleep*/
#include "uid.h"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

void TestUid(void);

int main(void)
{
	TestUid();
	return 0;
}


void TestUid(void)
{
	uid_ty first; 
	uid_ty seconed; 
	uid_ty third; 

	first = createUid();
    seconed = createUid();
    third = createUid();

	TEST(" create + is same ", UIDIsSame(first, first) , 1); 

	 printf("first: counter = %lu \ntime = %ld\npid =%d\n", first.counter, first.timestamp, first.pid);
    printf("seconed: counter = %lu \ntime = %ld\npid =%d\n", seconed.counter, seconed.timestamp, seconed.pid);
    printf("third: counter = %lu \ntime = %ld\npid =%d\n", third.counter, third.timestamp, third.pid);
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
	
}
