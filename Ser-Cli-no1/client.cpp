#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#define PORT 6000

int main(int argc, char **argv)
{
	int client_socket;
	struct sockaddr_in serv_addr;
	char buf[1024];
	int recv_len;
	if (argc!=2) {
		cout<<"请求参数错误  ";
		cout<<"usage: app argv"<<endl;
		exit(1);
	}
	
	// 创建客户端套接字
	if ((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		cout<<"创建套接字失败!"<<endl;
		exit(1);
	}
	// server 端的套接字参数设置
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("42.96.177.162");
	bzero(&(serv_addr.sin_zero),8);

	// 连接到server
	if ((connect(client_socket,(struct sockaddr*)&serv_addr,
		sizeof(struct sockaddr))) == -1)
  	{
		cout<<"client连接server失败!"<<endl;
		exit(1);
	}
	cout<<"client发送数据: "<<argv[1]<<endl;
	//接受数据
	strcpy(argv[1], buf);
	if (send(client_socket,buf, strlen(buf), 0) == -1)
		cout<<"发送错误!"<<endl;
	cout<<"client 接收数据: "<<endl;
	while (1) {
	if ((recv_len=recv(client_socket,buf,sizeof(buf),0))==-1)
	{
		cout<<"接收错误!"<<endl;
		exit(1);
	}
	buf[recv_len]='\0';
	if (strcmp(buf,"quit")==0||strcmp(buf,"exit")==0)
	{
		cout<<"recv finsh..."<<endl;
		exit(0);
	}
	cout<<"接收到: "<<buf<<endl;
	}
	close(client_socket);
}

