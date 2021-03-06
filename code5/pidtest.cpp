#include "comm_func.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

using namespace std;

int prg_server(short port);

int main(int argc,char **argv)
{
	
	if(argc<2)
	{
		cout<<"argument invalid"<<endl;
		return 1;
	}
	short port=atoi(argv[1]);
	
	if(argc==3 && strcmp(argv[2],"-d")==0)
	{
		if(daemon_init()<0)
		{
			cout<<"dameon_init error"<<endl;
			return 1;
		}
	}

	system("gnome-terminal -x bash");
	sleep(300);
	//return prg_server(port);
}

int prg_server(short port)
{
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
	
cout<<"ip "<<ntohl(INADDR_ANY)<<"  port"<<ntohs(addr.sin_port)<<endl;
	if(bind(sockfd,(struct sockaddr *)&addr,sizeof(addr))==-1)
	{
		cout<<"bind error"<<endl;
		return 1;
	}
	for(;;)
	{
		char 		buf[32];
		sockaddr_in 	client_addr;
		socklen_t		addr_len=sizeof(sockaddr_in);
		int n=recvfrom(sockfd,buf,32,0,(struct sockaddr *)&client_addr,&addr_len);
		cout<<"recv "<<n<<" bytes"<<endl;
		
		if(n>=0)
		{
			buf[n]=0;
			cout<<"recv:"<<buf<<endl;
			cout<<"client addr len:"<<(int)addr_len<<endl;
			cout<<"client addr.ip:"<<inet_ntoa(client_addr.sin_addr)<<endl;
			cout<<"client addr.port:"<<ntohs(client_addr.sin_port)<<endl;
			struct timeval tv;
			gettimeofday(&tv,NULL);
			sprintf(buf,"%d %d",(int)tv.tv_sec,(int)tv.tv_usec);
			cout<<"send:"<<buf<<endl;
			cout<<"send len:"<<strlen(buf)<<endl;
			if(sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&client_addr,sizeof(client_addr))==-1)
				cout<<"send error:"<<strerror(errno)<<endl;
				
		}
	}
	close(sockfd);
	return 0;
}
