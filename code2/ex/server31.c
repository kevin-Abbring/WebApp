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

#define  SERVER_PORT 8083
#define  BACKLOG	5

//------------------------------------------------------
int get_the_Data(int nBegin,int nEnd,int* pnData)
{
  int i,j,nNum;
  int b,bOnce;

  nNum=0;
  if(nBegin<=0 || nEnd<=0 || nEnd<nBegin)
  	nNum=-1;
  else
  {
	nNum=0;  	
	for(i=nBegin;i<nEnd;i++)
  	{
		b=1;
  		for(j=2;j<i;j++)
  		{
			if(i%j==0)
   			{
				b=0; 
				break;
			}
		}
	
		if(b)
		{
			*pnData=i;
			pnData++;
			nNum++;
		}
	}
  }

  
  return nNum;
}

//--------------------------------------------------------------
void serv_response(int sockfd)
{
  int i,nbytes;
  int buf_recv[1024];
  int buf_send[1024];

  nbytes=read(sockfd,(char*)buf_recv,1024*sizeof(int));
  if(nbytes<=0 || nbytes%sizeof(int)!=0)
	return;
 	
  int nNum= nbytes/sizeof(int);
  int* pn=buf_recv;

  for(i=0;i<nNum;i++)	
  {
	*pn=ntohl(*pn);
	pn++;
  }

  switch(buf_recv[0])	//函数代号，get_the_Data
  {
    case 1:
	nNum=get_the_Data(buf_recv[1], buf_recv[2], &buf_send[1]);
	int nNum2;		
	if(nNum<=0)
		nNum2=1;
	else
		nNum2=nNum+1; 

	buf_send[0]=nNum;
	for(i=0;i<nNum2;i++)
		buf_send[i]=htonl(buf_send[i]);
		
//nbytes=write_all(sockfd,（char*）buf_send,nNum*sizeof(int));
	nbytes=write(sockfd,(char*)buf_send,nNum2*sizeof(int));
	if(nbytes<=0)
		fprintf(stderr,"Write error\n");

	break;
	
    default:	//函数代号，其它
	printf("No this function\n");
	break;  
  }
}


//--------------------------------------------------------
int main()
{
  int listenfd,connfd;
  struct sockaddr_in servaddr;

  listenfd=socket(AF_INET,SOCK_STREAM,0);
  if(listenfd<0)
  {
	fprintf(stderr,"Socket error\n");
	exit(1);
  }
  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(SERVER_PORT);
  if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	fprintf(stderr,"Bind error\n");  
	exit(1);
  }
  
  if(listen(listenfd,BACKLOG)<0)
  {
	fprintf(stderr,"Listen error\n");
	exit(1);
  }

  printf("Listenning....\n");
  for(;;)
  {
	connfd=accept(listenfd,NULL,NULL);
    	if(connfd<0)
	{
	  fprintf(stderr,"Accept error\n");
	  exit(1);
	}

	serv_response(connfd);
	printf("One service is finished.\n");
    	close(connfd);
  }

  close(listenfd);
}

