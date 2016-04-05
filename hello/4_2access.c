#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc !=2)
	    printf("error usage: ./a.out <pathname>");
	printf("this is :%s\n", argv[0]);
	if (access(argv[1], R_OK) < 0)//cannot access
	    err_ret("access error for %s",argv[1]);
	else
	    printf("access OK\n");

	if (open(argv[1], O_RDONLY)<0)
	    err_ret("open error for %s", argv[1]);
	else
	    printf("open for reading ok\n");
	exit(0);
}
