/*************************************************************
 * UID
 *
 * Author: Noam Hadad
 *
 * A unique id made of the process id, a creation timestamp and an
 * atomically incremented counter.
 ******************************************************************/

#include <unistd.h> /* getpid */

#include "uid.h"

const uid_ty UID_INVALID = {0, 0, 0};

uid_ty createUid(void)
{
	static size_t counter = 0;
	uid_ty uid = {0, 0, 0};

	uid.counter = __sync_add_and_fetch(&counter, 1);
	uid.timestamp = time(NULL);
	uid.pid = getpid();

	if ((time_t)-1 == uid.timestamp)
	{
		return UID_INVALID;
	}

	return uid;
}

int UIDIsSame(uid_ty uid1, uid_ty uid2)
{
	return uid1.counter == uid2.counter &&
		   uid1.pid == uid2.pid &&
		   uid1.timestamp == uid2.timestamp;
}
