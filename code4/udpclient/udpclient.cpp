#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc,char **argv)
{
	short port;
	sockaddr_in addr;
	
	if(argc==3)
	{
		port=atoi(argv[1]);
		inet_aton((char*)argv[2],&addr.sin_addr);
	}
	else if(argc==2)
	{
		port=atoi(argv[1]);
		addr.sin_addr.s_addr=htonl(INADDR_ANY);
	}
	else
	{
		cout<<"argument invalid"<<endl;
		return 1;
	}
	
		
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		cout<<"create socket error"<<endl;
		return 1;
	}

	struct timeval rto;
	rto.tv_sec=2;
	rto.tv_usec=0;
	if(setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&rto,sizeof(rto))==-1)//设定2秒超时
		return 1;

	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	if(argc==3&&strcmp(argv[2],"-c")==0)
	{
		//记录服务器地址
		connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	}
	for(int i=0;i<100;i++)
	{
		char buf[16];
		sprintf(buf,"%d hello",getpid());
		cout<<"send:"<<buf<<endl;
		int n;
		if(argc==3&&strcmp(argv[2],"-c")==0)
		{
			//发送时不需要服务器地址
			n=sendto(sockfd,buf,strlen(buf),0,NULL,0);
		}
		else
		{
			//发送时需要服务器地址
			n=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
		}
		
		n=recvfrom(sockfd,buf,16,0,NULL,NULL);
		if(n>=0)
		{
			buf[n]=0;
			cout<<"recv:"<<buf<<endl;
		}
		sleep(1);
	}
	close(sockfd);
	return 0;
}
