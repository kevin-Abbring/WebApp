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
	int sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	//服务器调用bind绑定UNIX域socket和指定的地址
	struct sockaddr_un addr;
	bzero(&addr,sizeof(addr));
	unlink(UNIX_SOCKET);
	addr.sun_family=AF_UNIX;
	sprintf(addr.sun_path,"%s",UNIX_SOCKET);
	bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	//服务器调用listen转化为侦听socket
	listen(sockfd,5);
	//服务器调用accept接收客户端连接
	while(1)
	{
		int new_fd=accept(sockfd,NULL,NULL);
		if(new_fd==-1)
		{
			cout<<"accept error"<<endl;
			continue;
		}
		int n;
		do
		{
			char buf[512];
			n=recv(new_fd,buf,512,0);
			if(n>0)
			{
				buf[n]=0;
				cout<<"recv:"<<buf<<endl;
				n=send(new_fd,buf,n,0);
			}
		}while(n>0);
		close(new_fd);
	}
	close(sockfd);
	return 0;
}
