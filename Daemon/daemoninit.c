#include "apue.h"
#include <fcntl.h>
#include <syslog.h>
#include <sys/resource.h>
//守护进程的初始化

void init_daemon(void)
{
	int pid;
	int i;
	struct rlimit r1;

	if (pid = fork())
	exit(0);//parent process exit
	else if (pid < 0)
		exit(1);
	//子进程创建成功
	setsid();

	if (pid=fork())
	exit(0);
	else if (pid < 0)
		exit(1);
	//关闭文件
	if (r1.rlim_max == RLIM_INFINITY)
		r1.rlim_max=1024;
	for (i=0; i< r1.rlim_max; ++i)
		close(i);

	chdir("/home/zgf");
	
	umask(0);
	return ;
}

