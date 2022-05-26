#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define  SERVER_PORT 8086
#define  BACKLOG	 5

void serv_respon(int sockfd)
{
  int i;
  int nbytes;
  char buf_recv[1024];
  char buf_send[1024];

  //nbytes=read_all(sockfd,buf_recv,256);
  nbytes=read(sockfd,buf_recv,256);
  if(nbytes==0)
  	return;
  else if(nbytes<0)
  {
  	fprintf(stderr,"Write error");
 	exit(1);
  }

  char* pc_recv=buf_recv+255;
  char* pc_send=buf_send;

  printf("The data will be return...\n");
  for(i=0;i<256;i++)
  {
  	*pc_send= *pc_recv;
	printf("%d  ",*pc_send);
  
  	pc_send++;
  	pc_recv--;
  }
  printf("\n");	
  
  //nbytes=write_all(sockfd,buf_send,256);
  nbytes=write(sockfd,buf_send,256);
  if(nbytes<0)
  {
  	fprintf(stderr,"Write error");
  	exit(1);
  }
}

int main(int argc,char*argv[])
{
  int listenfd,connfd;
  struct sockaddr_in servaddr;

  listenfd=socket(AF_INET,SOCK_STREAM,0);
  if(listenfd<0)
  {
	fprintf(stderr,"Socket error");
	exit(1);
  }
  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(SERVER_PORT);
  if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	fprintf(stderr,"Bind error");
	exit(1);
  }

  if(listen(listenfd,BACKLOG)<0)
  {
	fprintf(stderr,"Listen error");
	exit(1);
  }

  printf("listenfd is %d\n",listenfd);
  printf("Listening...");
  for(;;)
  {
	connfd=accept(listenfd,NULL,NULL);
	if(connfd<0)
	{
		fprintf(stderr,"Accept error");
		exit(1);
	}

  	printf("A SYN requirement is accepted.\n");
	printf("connfd is %d\n",connfd);

	serv_respon(connfd);
  	printf("One service finished.\n");

	close(connfd);
  }

  close(listenfd);
}
