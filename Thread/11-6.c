#include "apue.h"
 
int main(void)
{
	printf("The size of int* is: %d %d\n",sizeof(int*),sizeof(int));
	printf("The size of void* is: %d\n", sizeof(void*));
	printf("The size of char* is: %d\n", sizeof(char*));
	
	exit(0);
}
