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
	int n;
	unsigned int cport, minport, maxport;

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

	int on=1;
	//setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

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

	cout<<"Udp server is ready..."<<endl;
	minport=65535;
	maxport=0;

	char buf[32];
	sockaddr_in client_addr;
	socklen_t addr_len;
	
	for(;;)
	{
		//接收客户端数据包
		n=recvfrom(sockfd,buf,16,0,(struct sockaddr *)&client_addr,&addr_len);
		if(n>=0)
		{
			cport=(unsigned int)ntohs(client_addr.sin_port);
			if(cport<minport || cport>maxport)
			{		
		   		if(cport<minport)
		      			minport=cport;
		   		else if(cport>maxport)
		      			maxport=cport;
		   
		   		cout<<"minport is: "<< minport<<"\t"<<"maxport is: "<<maxport<<endl;
			}				

			sprintf(buf,"abcde");
			sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&client_addr,sizeof(client_addr));
		}
	}
	close(sockfd);
	return 0;
}
