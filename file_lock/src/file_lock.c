/*
 ============================================================================
 Name        : file_lock.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#include "lock_set.h"


int main(void) {
	int fd;
	fd = open("hello", O_RDWR | O_CREAT, 0644);
	if(fd < 0)
	{
		printf("open file error\n");
		exit(1);
	}

	lock_set(fd, F_WRLCK);
	write(fd, "filelock", strlen("filelock"));
	getchar();
	lock_set(fd, F_UNLCK);
	getchar();
	close(fd);
	exit(0);
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
