#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXDATASIZE 128
#define PORT 3000

int addr_conv(char *address,struct in_addr *inaddr);

int main(int argc,char **argv){
	int sockfd,nbytes,i,j;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr;
	if(argc!=2){
		printf("usage:./client hostname|ip\n");
		exit(0);
	}
	
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
	if(addr_conv(argv[1],&srvaddr.sin_addr)==-1)
	{
	   perror(strerror(errno));
	   exit(1);
	}

	for(j=0;j<100;j++)
	{	
	   for(i=0;i<10000;i++)
	   {	
	      sockfd=socket(AF_INET,SOCK_STREAM,0);
	      if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	      }
	
	      if(connect(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1){
		 printf("connect error\n");
		 exit(1);
	      }
	
	      sprintf(buf,"hello");
	      write(sockfd,buf,strlen(buf));
	      if((nbytes=read(sockfd,buf,MAXDATASIZE))==-1){
		 printf("read error\n");
		 exit(1);
	      }
	      
	      close(sockfd);
	   }
	    	
	   printf("srv respons 10k times:%d\n",j);
	}

	return 0;
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
