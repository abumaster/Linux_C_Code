#include "apue.h"

int main(int argc, char *argv[])
{
	int status;
	
	if (argc < 2)
		err_quit("command-line argument required");
	if ((status = system(argv[1])) < 0)
		err_sys("system() error");
	if(WIFEXITED(status))
		printf("normal termination, exit status= %d\n",
			WEXITSTATUS(status));
	exit(0);
}
