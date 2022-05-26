//#include "server301.h"
#include "server302.h"

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

