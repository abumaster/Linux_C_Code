/*
    网络编程，获取系统时间
*/
#include "unp.h"
int main(int argc, char **atgv)
{
    int sockfd, n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;
    
    if (argc != 2)
        err_quit("usage : a.out IP");
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)
        err_quit("socket error");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13);
    if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
        err_quit("int_pton error");
    if (connect(sockfd, (SA*),&servaddr, sizeof(servaddr))<0)
        err_sys("connect error");
    while ((n=read(sockfd,recvline,MAXLINE))>0) {
        recvline[n]=0;
        if (fputs(recvline,stdout)==EOF)
            err_sys("fputs error");
     }
     if (n<0)
        err_sys("read error");
     exit(0);
}