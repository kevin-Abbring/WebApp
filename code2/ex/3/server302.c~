#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#define  SERVER_PORT 8082
#define  BACKLOG	5

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

  switch(buf_recv[0])	//函数代号，get_the_Avg
  {
    case 2:
	
	if(nNum<2 || nNum-2!=buf_recv[1])
	{
		printf("Data error\n");
		break;
	}

	nNum=get_the_Avg(nNum-2,&buf_recv[2]);
	buf_send[0]=nNum;
	buf_send[0]=htonl(buf_send[0]);
		
	//nbytes=write_all(sockfd,（char*）buf_send,nNum*sizeof(int));
	nbytes=write(sockfd,(char*)buf_send,sizeof(int));
	if(nbytes<=0)
		fprintf(stderr,"Write error\n");

	break;
	
    default:	//函数代号，其它
	printf("No this function\n");
	break;  
  }
}

int get_the_Avg(int nNum,int* pnData)
{
  int i,nAvg,nAvg1;
  int* pn;

  pn=pnData;
  nAvg=0;
  nAvg1=0;	
  for(i=0;i<nNum;i++)
  {
	nAvg1+=*pn;
	pn++;
  }
  
  if(nNum>0)
  {
	nAvg1=nAvg1*2/nNum;
  	nAvg=nAvg1/2;
	nAvg1=nAvg1%2;
	if(nAvg1>0)
		nAvg++;
  }
  
  return nAvg;
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

