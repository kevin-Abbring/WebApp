#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define  BACKLOG	 5

void serv_respon(int sockfd)
{
  int i;
  int nbytes;
  char buf_recv[256];
  char buf_send[256];

  nbytes=read(sockfd,buf_recv,256);
  if(nbytes==0)
  	return;
  else if(nbytes<0)
  {
  	cout<<"Read error"<<endl;
 	return;
  }

  char* pc_recv=buf_recv+15;
  char* pc_send=buf_send;

  cout<<"The data will be return..."<<endl;
  for(i=0;i<16;i++)
  {
  	*pc_send= *pc_recv;
	cout<<*pc_send<<" ";
  
  	pc_send++;
  	pc_recv--;
  }
  printf("\n");	
  
  nbytes=write(sockfd,buf_send,16);
  if(nbytes<0)
  {
  	cout<<"Write error"<<endl;
  	return;
  }
}

int main(int argc,char*argv[])
{
  int listenfd,connfd;
  struct sockaddr_in servaddr;
  short port;

  if(argc!=2){
	cout<<"usage: ./server1 port."<<endl;
	exit(0);
  }
  port=atoi(argv[1]);

  listenfd=socket(AF_INET,SOCK_STREAM,0);
  if(listenfd<0)
  {
	cout<<"Socket error"<<endl;
	exit(1);
  }

  cout<<"Server port is "<<port<<endl;
  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(port);
  if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	cout<<"Bind error"<<endl;
	exit(1);
  }

  if(listen(listenfd,BACKLOG)<0)
  {
	cout<<"Listen error"<<endl;
	exit(1);
  }

  cout<<"listenfd is "<<listenfd<<endl;
  cout<<"Listening..."<<endl;
  for(;;)
  {
	connfd=accept(listenfd,NULL,NULL);
	if(connfd<0)
	{
		cout<<"Accept error"<<endl;
		exit(1);
	}

  	cout<<"A SYN requirement is accepted."<<endl;
	cout<<"connfd is "<<connfd;

	serv_respon(connfd);
  	cout<<"One service finished."<<endl;

	close(connfd);
  }

  close(listenfd);
}
