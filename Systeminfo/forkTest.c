#include "apue.h"

int glob=6;
char buf[] = "a write to stdout\n";

int main()
{
	int var;
	pid_t pid;
	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	printf("before fork\n");

	if ((pid = fork()) <0) {
		err_sys("fork error\n");
	} else if (pid==0) {//child 
		glob++;
		var++;
	} else {//parent
		sleep(2);
	}
	printf("pid = %d, glob = %d, var = %d\n",getpid(),glob, var);
	exit(0);
}
