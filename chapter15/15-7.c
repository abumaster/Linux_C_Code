#include "apue.h"
#include <sys/wait.h>

int main(void)
{
	char line[MAXLINE];
	FILE *fpin;
	//打开读管道，
	if ((fpin = popen("myuclc", "r")) == NULL)
		err_sys("popen error");
	for ( ; ; ) {
		fputs("prompt> ", stdout);
		fflush(stdout);
		//重管道中读
		if (fgets(line, MAXLINE, fpin) == NULL)
			break;
		if (fputs(line, stdout) == EOF)
			err_sys("fputs error");
	}
	pclose(fpin);
	putchar('\n');
	exit(0);
}
