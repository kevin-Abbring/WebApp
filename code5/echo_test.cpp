#include <time.h>
#include "comm_func.h"
#include <iostream>

#define 	MAX_RECV_SIZE 4096
#define 	MAX_SEND_SIZE 1024

using namespace std;

int main(int argc,char **argv)
{
	int 		sockfd,nbytes;
	char 	recv_buf[MAX_RECV_SIZE];
	char		send_buf[MAX_SEND_SIZE];
	struct 	sockaddr_in srvaddr;
	short		port=80;
	char		host[128];
	long int	n1,n2;
	
	switch(argc)
	{
		case 1:
			sprintf(host,"127.0.0.1");
			break;
		case 2:
			sprintf(host,"%s",argv[1]);
			break;
		case 3:
			sprintf(host,"%s",argv[1]);
			port=atoi(argv[2]);
			break;
		default:
			printf("argc error\n");
			return 1;
	}
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(port);	
	inet_aton(host,&srvaddr.sin_addr);
	/*
	if(!addr_conv(host,&srvaddr.sin_addr))
	{
		cout<<"addr convert fail"<<endl;
		return 1;
	}
	*/	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		printf("socket error\n");
		exit(1);
	}
	if(connect(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1)
	{
		printf("connect error\n");
		exit(1);
	}
	srandom(clock());	//变换随机数种子
	n1=random()%1000;
	n2=random()%1000;
	sprintf(send_buf,"%d %d\n",(int)n1,(int)n2);
	cout<<"send:"<<send_buf<<endl;
	write(sockfd,send_buf,strlen(send_buf));
	if((nbytes=read(sockfd,recv_buf,MAX_RECV_SIZE))==-1)
	{
		cout<<"read error"<<endl;
		exit(1);
	}
	
	recv_buf[nbytes]=0;
	cout<<"recv:"<<recv_buf<<endl;
	close(sockfd);
	return 0;
}
