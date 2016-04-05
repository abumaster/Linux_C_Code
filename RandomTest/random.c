#include "apue.h"
int main()
{
	int x1,x2,x3;
	int i;
	for ( i=0; i<1000; i++) {
	x1=rand()/10000000;
	x2=rand()/10000000;
	x3=rand()/10000000;
	printf("%d %d %d\n", x1,x2,x3);
	}
	exit(0);
}
