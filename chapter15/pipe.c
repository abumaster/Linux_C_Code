#include "apue.h"

int main(void)
{
	int fd[2];
	int n;
	char line[MAXLINE];	
	pid_t pid;

	//创建管道
	if (pipe(fd) < 0)
		err_sys("pipe create error");
	//创建子进程
	if ((pid = fork()) < 0)
		err_sys("fork child error");
	else if (pid > 0) { //parent
		//关闭读端
		close(fd[0]);
		char ss[MAXLINE];
		printf("请输入一些字符\n");
		n=read(STDIN_FILENO, ss, MAXLINE);//) > 0)
		write(fd[1], ss, n);
	} else { //child
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
		
