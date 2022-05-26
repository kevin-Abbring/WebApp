#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define  SERVER_PORT 8086
#define  BACKLOG	5

void serv_selectbigger(int sockfd)
{
  int i,nbytes;
  int buf_recv[1024];
  int buf_send[1024];

  
  //nbytes=read_all(sockfd,buf_recv,256*sizeof(int));
  nbytes=read(sockfd,(char*)buf_recv,256*sizeof(int));
  printf("The length is:%d \n",nbytes);	
  if(nbytes<0 || nbytes==0)
  {
	fprintf(stderr,"Read error");
 	exit(1);
  }

  printf("The received data is\n");
  for(i=0;i<256;i++)					//字节顺序
  {
	buf_recv[i]=ntohs(buf_recv[i]);
	printf("%d ",buf_recv[i]);	

  }
  printf("\n\n\n");

  int j=0;
  for(i=0;i<256;i++)
  {
  	if(buf_recv[i]>100)
	{
		j++;
		buf_send[j]= buf_recv[i];
	}  
  }
	
  buf_send[0]=j;
  int avg=0;
  for(i=0;i<j;i++)
  {
	avg+= buf_send[i+1];
  }

  if(j>0)
  	avg=avg/j;
  else
  	avg=0;

  buf_send[j+1]=avg;

  printf("The result is \n");
  for(i=0;i<j+2;i++)					//字节顺序
  {
	printf("%d ",buf_send[i]);	
	buf_send[i]=htons(buf_send[i]);
  }
  printf("\n\n\n");	

  //nbytes=write_all(sockfd, buf_send, (j+2)*sizeof(int));
  nbytes=write(sockfd, (char*)buf_send, (j+2)*sizeof(int));
  if(nbytes<0 || nbytes==0)
  {
	fprintf(stderr,"Write error");
	exit(1);
  }
}


int main()
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

  for(;;)
  {
	connfd=accept(listenfd,NULL,NULL);
    	if(connfd<0)
	{
	  fprintf(stderr,"Accept error");
	  exit(1);
	}

	serv_selectbigger(connfd);
    	close(connfd);
  }

  close(listenfd);
}
