#include <iostream>
#include <unistd.h>

//#include "server301.h"
#include "server302.h"

int main(int argc, char **argv) {
  
    int listenfd,connfd;
    struct sockaddr_in servaddr;

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0)
    {
	  std::cout <<"Socket error"<<std::endl;
	  return 1;
    }
  
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERVER_PORT);
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
	  std::cout <<"Bind error"<<std::endl;
	  return 1;
    }
  
    if(listen(listenfd,BACKLOG)<0)
    {
	   std::cout <<"Listen error"<<std::endl;
	  return 1;
    }

     std::cout <<"Listenning...."<<std::endl;
    for(;;)
    {
	  connfd=accept(listenfd,NULL,NULL);
	  if(connfd<0)
	  {
		std::cout <<"Accep error"<<std::endl;
		return 1;
    	  }

	  serv_response(connfd);
	  std::cout <<"One service is finished."<<std::endl;
	  
	  close(connfd);
    }

    close(listenfd);
    return 0;
}