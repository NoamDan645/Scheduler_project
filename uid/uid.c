/*************************************************************
* OL124  uid number
* 
* Author: 
******************************************************************/

#include "uid.h"
#include <unistd.h> /*getpid*/


const uid_ty UID_INVALID = {0,0,0};

/* -- inner function --*/
static void UpdateUID(uid_ty *_uid);


/*Return UID number or 0 for failure */
uid_ty GetUID(void)
{

	static int flag = 0;
	static unsigned long general_counter = 0;
	uid_ty out = {0,0,0};

	if (!flag)
	{
		flag = 1;
		out.counter = general_counter;
		UpdateUID(&out);
		return out;
	}

	++general_counter;
	out.counter = general_counter;
	UpdateUID(&out);
	return out;
}

/*return 1 if two UID are same and 0 otherwise*/
int UIDIsSame(uid_ty uid1, uid_ty uid2)
{
	return ((uid1.counter == uid2.counter) && \
		   (uid1.timestamp == uid2.timestamp) &&\
		   (uid1.pid == uid2.pid));
}


/* -- inner function implamentation --*/
static void UpdateUID(uid_ty *_uid)
{
	_uid->pid = getpid();	
	_uid->timestamp = time(NULL);
	if(_uid->timestamp == (time_t)-1)
	{
		_uid->counter = 0;
		_uid->timestamp = 0;
		_uid->pid = 0;	
	}
}



