#include <sys/socket.h>
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

int main(int argc,char **argv)
{
	int sockfd[2];
	char buf[32];
	if(socketpair(AF_UNIX,SOCK_STREAM,0,sockfd)<0)
	{
		cout<<"socketpair error"<<endl;
		return 1;
	}
	pid_t pid=fork();
	if(pid>0)
	{
		close(sockfd[0]);
		send(sockfd[1],"a",1,0);
		recv(sockfd[1],buf,1,0);
		cout<<"a->"<<buf<<endl;
	}
	else if(pid==0)
	{
		close(sockfd[1]);
		recv(sockfd[0],buf,1,0);
		buf[0]=toupper(buf[0]);
		send(sockfd[0],buf,1,0);
		exit(0);
	}
	else
		cout<<"fork error"<<endl;
	return 0;
}
