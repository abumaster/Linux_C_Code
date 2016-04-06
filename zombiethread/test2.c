#include "apue.h"


//通过设置信号，来预防僵尸进程的出现

int main()
{
	int status;
	int i;
	
	//set signal
	signal(SIGCHLD, SIG_IGN);

	for (i=0; i<5; i++) {
		if (!fork()) {
		printf("child %d : pid=%d\n",i+1,getpid());
		exit(0);
		}
	}
	printf("use ps -e look \n");
	sleep(10);
	exit(0);
}
