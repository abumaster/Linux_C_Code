#include "apue.h"
#include "fcntl.h"

#define FIFO_NAME "/home/zgf/temp/my_fifo"
#define BUF_SIZE 40

int main()
{
	int pipe_fd;
	int res;
	char buffer[BUF_SIZE+1];
	int bytes;
	memset(buffer, '\0', sizeof(buffer));
	printf("Process %d open fifo\n", getpid());
	pipe_fd = open(FIFO_NAME, O_RDONLY);
	printf("process %d open fifo %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) {
		res = read(pipe_fd, buffer, BUF_SIZE);
		while (res>0) {
			bytes+=res;
			printf("消费者读出--->");
			puts(buffer);	
			res = read(pipe_fd,buffer,BUF_SIZE);
		}
		close(pipe_fd);
	}
	else {
		err_sys("open fifo error");
	}
	printf("Process %d finished.%d bytes read\n",getpid(), bytes);
	exit(0);
}
