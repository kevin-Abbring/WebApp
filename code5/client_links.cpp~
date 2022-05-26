#include <time.h>
#include "comm_func.h"
#include <iostream>

#define 	MAX_RECV_SIZE 4096
#define 	MAX_SEND_SIZE 1024

using namespace std;

int main(int argc,char **argv)
{
	int 		sockfd,nbytes;
	struct 	sockaddr_in srvaddr;
	short	port=80;
	char	host[128];
	int m;
	int	n[2];
	
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
	if(!addr_conv(host,&srvaddr.sin_addr))
	{
		cout<<"addr convert fail"<<endl;
		return 1;
	}
		
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
	n[0]=random()%1000;
	n[1]=random()%1000;
	cout<<"send:"<<n[0]<<",   "<<n[1]<<endl;
	
	n[0]=htonl(n[0]);
	n[1]=htonl(n[1]);
	write(sockfd,(char*)n,sizeof(int)*2);
	if((nbytes=read(sockfd,(char*)&m,MAX_RECV_SIZE))!=sizeof(int))
	{
		cout<<"read error"<<endl;
		exit(1);
	}
	
	m=ntohl(m);
	cout<<"recv:"<<m<<endl;
	close(sockfd);
	return 0;
}

