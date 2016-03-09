#include "apue.h"
#include "fcntl.h"
#define NEWFILE (O_WRONLY|O_CREAT|O_TRUNC)
#define SIZE 80		
int my_write(int fd, const char  *buf, int count)
{
	int i,n;
	int write_offset=0;
	char write_buf[count];
	for (i=0; i<count; ++i)
	{
	 write_buf[write_offset++] = *buf++;
	 if (write_offset == SIZE)
	 {
	  write_offset = 0;
	  n = write(fd, write_buf, sizeof(write_buf));
	  if (n!=SIZE)
 	   return -1;
	 }
	}
	return -1;

}

int main(void)
{
	int outfile;
	char filename[] = {"test.dat"};
	char buffer[SIZE];
	if(outfile = open(filename, NEWFILE, 0640) == -1)
	{
	printf("erroe open file error@\n");
	exit(255);
	}
	scanf("%s",buffer);
	
	//gets(buffer);
	if(my_write(outfile,buffer,SIZE) == -1)
	{
	printf("write error\n");
	exit(255);
	}
	close(outfile);
	
	return 0;
	
}
