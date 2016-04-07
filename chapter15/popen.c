#include "apue.h"
#include <sys/wait.h>
//popen用法，
int main(void)
{
	FILE *fp;
	char line[MAXLINE];
	//管道读，fp绑定到cmd的标准输出
	if ((fp=popen("cat test", "r"))==NULL)
		err_sys("popen error");
	while (fgets(line, MAXLINE, fp) != NULL) {
		printf("%s",line);
	}
	pclose(fp);
	exit(0);
}

