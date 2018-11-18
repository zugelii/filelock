/*
 * lock_set.c
 *
 *  Created on: 2018年11月18日
 *      Author: leo
 */
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<lock_set.h>
int  lock_set(int fd, int type)
{
	struct flock old_lock, lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_type = type;
	lock.l_pid = -1;

	fcntl(fd, F_GETLK, &lock);
	if(lock.l_type != F_UNLCK)
	{
		if(lock.l_type == F_RDLCK)
		{
			printf("read lock already set by process:%d\n", lock.l_pid);
		}
		else if(lock.l_type == F_WRLCK)
		{
			printf("write lock already set by process: %d\n", lock.l_pid);
		}
	}
		lock.l_type = type;

		if((fcntl(fd, F_SETLKW, &lock)) < 0)
		{
				printf(("lock failed:type:%d\n", lock.l_type));
				return 1;
		}
		printf("process :%d get lock\n", getpid());
		switch(lock.l_type)
		{
		case F_RDLCK:
			printf("read lock set by %d\n", getpid());
		break;
		case F_WRLCK:
			printf("write lock set by %d\n", getpid());
		break;
		case F_UNLCK:
		{
			printf("release lock by %d\n", getpid());
			return 1;
		}
		break;
		default:
			printf("go to default\n");
			break;
		}

	return 0;
}
