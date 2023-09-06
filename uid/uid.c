/*************************************************************
 * uid create
 *
 * Author:Noam Hadad
 ******************************************************************/

#include "uid.h"
#include <unistd.h> /*getpid*/

const uid_ty UID_INVALID = {0, 0, 0};

/*Return UID number or 0 for failure */
uid_ty createUid(void)
{
	static int flag = 0;
	static size_t counter = 0;
	uid_ty uid = {0};
	__sync_fetch_and_add(&counter, 1);
	uid.timestamp = time(NULL);
	uid.counter = counter;
	uid.pid = getpid();
	return uid;
}

/*return 1 if two UID are same and 0 otherwise*/
int UIDIsSame(uid_ty uid1, uid_ty uid2)
{
	return ((uid1.counter == uid2.counter) &&
			(uid1.pid == uid2.pid));
}

uid_t getInvalidUid()
{
	uid_t invalid_uid ={0};
	return invalid_uid;
}


