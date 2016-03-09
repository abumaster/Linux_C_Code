#include "apue.h"
int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		printf("fork error!\n");
		exit(1);
	}
	else if (pid ==0)
	{
		printf("child process is printing!\n");
	}
	else
	{
		printf("Parent process is printing!\n");
	}
	exit(0);
}

