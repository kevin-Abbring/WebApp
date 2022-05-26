#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/un.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h> 

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

using namespace std;

#define UNIX_SOCKET "/tmp/unix_socket"

int main(int argc,char **argv)
{
	//客户端创建UNIX域socket(同服务器)
	int sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	//客户端调用connect连接服务器
	struct sockaddr_un addr;
	char	 path[104]=UNIX_SOCKET;
	int len;
	bzero(&addr,sizeof(addr));
	addr.sun_family=AF_UNIX;
	sprintf(addr.sun_path,"%s",UNIX_SOCKET);
	len=strlen(addr.sun_path)+sizeof(addr.sun_family);
	if(connect(sockfd,(struct sockaddr *)&addr,len)==-1)
	{
		cout<<"connect error"<<endl;
		return 1;
	}
	do
	{
		char buf[512];
		int n;
		cout<<">";
		fgets(buf,512,stdin);
		if(send(sockfd,buf,strlen(buf),0)==-1)
		{
			cout<<"send error"<<endl;
			break;
		}
		if((n=recv(sockfd,buf,512,0))<=0)
		{
			cout<<"recv error"<<endl;
			break;
		}
		else
		{
			buf[n]=0;
			cout<<"recv:"<<buf<<endl;
		}
	}while(1);
	close(sockfd);
	return 0;
}
