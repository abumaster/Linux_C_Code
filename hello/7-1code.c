#include "apue.h"
int main(void)
{
	if (creat("./hello.txt",  S_IRWXU) < 0)
	{
	 printf("crate file error!\n");
	 exit(0);
	}
	else
	{
	 printf("success!\n");
	}
	exit(0);
}
