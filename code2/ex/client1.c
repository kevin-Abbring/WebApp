#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#define  SERVER_PORT 8086

void cli_requ(int sockfd)
{
  char buf[1024];
  int i,n,nbytes;
   
  printf("The data will be sent...\n");
  for(i=0;i<256;i++)
  {
  	buf[i]=random(256);
  	printf("%d  ",buf[i]);
  }
  printf("\n");

  //nbytes=write_all(sockfd,buf,256); 
  nbytes=write(sockfd,buf,256); 
  if(nbytes<0)
  {
	fprintf(stderr,"Write error");
	exit(1);
  }

  //nbytes=read_all(sockfd,buf,512);
  nbytes=read(sockfd,buf,512);
  if(nbytenbytes=write(sockfd,buf,256); s<0 || nbytes==0)
  {
	fprintf(stderr,"Read error");
	exit(1);
  }
  
  sleep(8);
  printf("The received data is...\n");
  for(i=0;i<nbytes;i++)
    	printf("%d  ",buf[i]);
  
  printf("\n");
}

int main(int argc,char*argv[])
{
  int sockfd;
  struct sockaddr_in servaddr;

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
  {
	fprintf(stderr,"Socket error");
	exit(1);
  }
  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(SERVER_PORT);
  if(inet_aton(argv,&servaddr.sin_addr)==-1)
  {
	fprintf(stderr,"Inet_aton error");
	exit(1);
  }

  printf("Connecting...\n");
  if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	fprintf(stderr,"Connect error");
	exit(1);
  }
 
  printf("Connected.\n");
  sleep(5);
  cli_requ(sockfd);
  close(sockfd);
}

