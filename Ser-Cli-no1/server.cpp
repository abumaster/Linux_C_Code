#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
using namespace std;

#define PORT 6000 // 通信端口
#define MAX_REQ 5

int main()
{
	int listen_socket, client_socket;
	struct sockaddr_in local_addr;
	struct sockaddr_in client_addr;
	int recv_len;

	char buf[1024];
	char recv_buf[1024];
	
	//创建套接字
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0))\
		==-1) {
		cout<<"创建server套接字失败!"<<endl;
		exit(1);
	}
	//设置地址参数结构
	local_addr.sin_family = AF_INET;//tcp/ip
	local_addr.sin_port = htons(PORT);
	local_addr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(local_addr.sin_zero),8);
	//绑定套接字
	if (bind(listen_socket, (struct sockaddr*)&local_addr,\
		sizeof(struct sockaddr))==-1) {
		cout<<"server 套接字绑定失败!"<<endl;
		exit(1);
	} else {
		cout<<"绑定成功"<<endl;
	}
	//监听
	//创建请求队列
	if (listen(listen_socket,MAX_REQ)==-1) {
		cout<<"监听失败!"<<endl;
		exit(1);
	} else {
		cout<<"server 开始监听..."<<endl;
	}
	int len = sizeof(struct sockaddr_in);
	//accept
	//服务器睡眠等待客户连接请求
	while (1) {
		if ((client_socket=accept(listen_socket,
			(struct sockaddr*)&client_addr,
			(socklen_t *)&(len)))==-1) {
			cout<<"server 等待请求错误"<<endl;
			exit(1);
		}
		else {
			cout<<"server 正在等待请求"<<endl;
		}
		//收到请求
		cout<<"收到请求，来自IP: "
			<<inet_ntoa(client_addr.sin_addr)
			<<" 端口号: "
			<<ntohs(client_addr.sin_port)<<endl;
		cout<<"准备发送数据: "<<endl;
		strcpy(buf, "");
		while (1) {
		cin>>buf;
		int sendlen=strlen(buf);
		if (send(client_socket,buf, sendlen, 0)==-1)
			cout<<"发送错误!"<<endl;
		if (strcmp(buf,"quit")==0||strcmp(buf,"exit")==0)
		{
			cout<<"发送成功!"<<endl;
			break;
			//exit(0);
		}
		}
		//一次连接结束后服务退出
		cout<<"正在退出..."<<endl;
		sleep(2);
		break;
	}
	close(listen_socket);//关闭套接字
	//cout<<"退出..."<<endl;
	exit(0);
}
