/*************************************************************
*
   uid number
* 
* uid.h
* uid.c
* uid_test.c
******************************************************************/

#ifndef UUID_NUMBER_H
#define UUID_NUMBER_H

#include <time.h>   /*time_t*/
#include <sys/types.h>    /*pid_t*/

typedef struct
{
    unsigned long counter;
    time_t timestamp;
    pid_t pid;
} uid_ty;

extern const uid_ty UID_INVALID; /*to compare with UID*/

/*Return UID number, on failure return UID_INVALID */
uid_ty GetUID(void);

/*return 1 if two UUID are same and 0 otherwise*/
int UIDIsSame(uid_ty uid1, uid_ty uid2);

/* Return 0 if UID number is valid and 1 if not valid */
/*int GetUID(uid_ty *_uid);*/

#endif 

