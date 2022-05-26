#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

int time_out;

int addr_conv(char *address,struct in_addr *inaddr);
void sigalrm_handler(int signo);

int main(int argc,char **argv)
{
	int i,j,n,sockfd;
        struct sigaction act;
	char buf[128];

	if(argc<3)
	{
		cout<<"argument invalid"<<endl;
		return 1;
	}
	short port=atoi(argv[2]);

	act.sa_handler=sigalrm_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGALRM,&act,NULL);

	sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	if(addr_conv(argv[1],&addr.sin_addr)==-1)
	{
	   cout<<"conv error"<<endl;
	   return 2;	
	}
	
	for(j=0;j<100;j++)
	{
	   for(i=0;i<10000;i++)
	   {
	
	      sockfd=socket(AF_INET,SOCK_DGRAM,0);
	      if(sockfd==-1)
	      {
		 cout<<"create socket error"<<endl;
		 return 1;
	      }
		
	      time_out = 0;  
	      
	      sprintf(buf,"hello");
	      n=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
	      alarm(1);
	      n=recvfrom(sockfd,buf,16,0,NULL,NULL);
	      alarm(0);
	      if(n<0 && time_out!=1)
	      {
		 cout<<"recv error"<<buf<<endl;
	         return 3;
	      }
	      close(sockfd);

	   }
	   
	   cout<<"srv respons 10k times: "<<j<<endl;
	}
	
	return 0;
}

void sigalrm_handler(int signo)       /*信号触发函数*/
{
	time_out = 1;
}

int addr_conv(char *address,struct in_addr *inaddr){
	struct hostent *he;
	if(inet_aton(address,inaddr)==1){
		printf("call inet_aton sucess.\n");
		return 0;
	}
	printf("call inet_aton fail.\n");
	he=gethostbyname(address);
	if(he!=NULL){
		printf("call gethostbyname sucess.\n");
		*inaddr=*((struct in_addr *)(he->h_addr_list[0]));
		return 0;
	}
	return -1;
}
