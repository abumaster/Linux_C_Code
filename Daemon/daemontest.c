#include <stdio.h>
#include <time.h>

void init_daemon(void);

void main()
{
	FILE *fp;
	time_t t;
	init_daemon();
	while (1) {
		sleep(60);
		if ((fp = fopen("test.log","a"))>=0)
		{
		t=time(0);
		fprintf(fp,"i am here at %s\n",asctime(localtime(&t)));
		fclose(fp);
		}
	}
//	exit(0);
}
