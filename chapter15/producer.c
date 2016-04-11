#include "apue.h"
#include <fcntl.h>

#define FIFO_NAME "/home/zgf/temp/my_fifo"
#define BUF_SIZE 40
#define LEN 36*10
int main()
{
	/*char buffer[BUF_SIZE+1]="abcdefghigklmnopqrstuvwxyz\n";
	int res=write(STDOUT_FILENO, buffer, strlen(buffer));
	printf("字节数: %d\n", res);
	printf("字符数: %d\n", strlen(buffer));
	exit(0);*/
	int pipe_id;
	int res;
	int bytes = 0;
	char buffer[BUF_SIZE+1]="abcdefghijklmnopqrstuvwxyz";
	
	if (access(FIFO_NAME,F_OK)==-1) {
		res = mkfifo(FIFO_NAME,0777);
		if (res!=0) {
			err_sys("can't create fifo");
		}
	}//create
	printf("Process %d open fifo \n", getpid());
	pipe_id = open(FIFO_NAME, O_WRONLY);
	printf("Process %d --> FILE ID %d\n", getpid(), pipe_id);
	if (pipe_id != -1) {
		char test_char='0';
		while (bytes<LEN) {
			test_char++;
			int len = strlen(buffer);
			buffer[len]=test_char;
			buffer[len+1]='\0';
			//写到管道中
			res = write(pipe_id,buffer,BUF_SIZE);
			if (res==-1)
				err_sys("write to fifo error");
			printf("生产者写入:---->");
			puts(buffer);
			bytes+=res;
		}
		close(pipe_id);
		}
	else {
		err_sys("pipe open error");
	}
	printf("Process %d finish..\n", getpid());
	
	exit(0);
}

