#include "apue.h"
//#include <sys/wait.h>
int main()
{
	printf("using the wait\n");	
	pid_t pid;
	int status;
	if ((pid=fork())<0)
		err_sys("error fork");
	else if (pid==0)
		exit(7);
	if (wait(&status)!=pid)
		err_sys("wait error");

	exit(0);
}
