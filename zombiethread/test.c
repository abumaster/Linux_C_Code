#include "apue.h"
#include <sys/wait.h>
//僵尸进程
int main()
{
	int status;
	if (!fork()) {
		printf("child pid=%d\n",getpid());
		exit(0);// exit child
	}
	printf("use ps -e look zombie process\n");
	sleep(10);
	printf("let parent process wait prcess the zombie\n");
	if (waitpid(-1, &status, 0)!=-1)
		printf("child exit pid=%d\n", status);
	else {
		printf("wait error\n");
		exit(1);
	}
	sleep(10);
	exit(0);
}
