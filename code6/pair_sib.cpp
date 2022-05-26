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
	int sockfd1[2],sockfd2[2];
	char psend1[]="hello";
	char psend2[]="welcome";
	char precv1[16];
	char precv2[16];
	pid_t pid;

	if(socketpair(AF_UNIX,SOCK_STREAM,0,sockfd1)<0 || socketpair(AF_UNIX,SOCK_STREAM,0,sockfd2)<0)
	{
		cout<<"socketpair error"<<endl;
		return 1;
	}	
	
	pid=fork();
	if(pid<0)
		exit(1);
	else if(pid==0){	//child B,use sockfd1-0	
		cout<<"child B..."<<endl;
		
		close(sockfd1[1]);
		recv(sockfd1[0],precv1,16,0);
		cout<<"child B received:"<<precv1<<endl;
		send(sockfd1[0],psend2,sizeof(psend2),0);
		exit(0);
	}

	pid=fork();
	if(pid<0)
		exit(1);
	else if(pid==0){	//child A,use sockfd2-0	
		cout<<"child A..."<<endl;
		close(sockfd2[1]);
		send(sockfd2[0],psend1,sizeof(psend1),0);
		recv(sockfd2[0],precv2,16,0);
		cout<<"child A received:"<<precv2<<endl;
		exit(0);
	}

	//父进程
	close(sockfd1[0]);
	close(sockfd2[0]);
	recv(sockfd2[1],precv1,16,0);
	send(sockfd1[1],precv1,sizeof(precv1),0);
	recv(sockfd1[1],precv2,16,0);
	send(sockfd2[1],precv2,sizeof(precv2),0);
		
	cout<<"finish."<<endl;
}	


