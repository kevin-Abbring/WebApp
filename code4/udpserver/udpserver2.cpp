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
#include <sys/time.h>

using namespace std;

int main(int argc,char **argv)
{
	char* pch;	
	
	if(argc!=2)
	{
		cout<<"argument invalid"<<endl;
		return 1;
	}
	short port=atoi(argv[1]);
	
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		cout<<"create socket error"<<endl;
		return 1;
	}
	sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	//绑定服务器地址
	if(bind(sockfd,(struct sockaddr *)&addr,sizeof(addr))==-1)
	{
		cout<<"bind error"<<endl;
		return 1;
	}

	for(;;)
	{
		char 		buf[32];
		sockaddr_in 	client_addr;
		socklen_t		addr_len=sizeof(struct sockaddr);	//如果不加sizeof,有些编译器会把收到的地址置0
		//接收客户端数据包
		int n=recvfrom(sockfd,buf,16,0,(struct sockaddr *)&client_addr,&addr_len);
		if(n>=0)
		{
			buf[n]=0;
			pch=inet_ntoa(client_addr.sin_addr);
			cout<<"recv:"<<buf<<" from:"<<pch<<endl;
			struct timeval tv;
			gettimeofday(&tv,NULL);
			sprintf(buf,"%d %d",(int)tv.tv_sec,(int)tv.tv_usec);
			//利用recvfron中得到的地址回送数据包
			sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&client_addr,sizeof(client_addr));
		}
	}
	close(sockfd);
	return 0;
}
