#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void cli_requ(int sockfd)
{
  char buf[256];
  int i,n,nbytes;
  
  srand((int)time(NULL));
  cout<<"The data will be sent..."<<endl;
  for(i=0;i<16;i++)
  {
  	buf[i]=48+random()%42;
  	cout<<buf[i]<<" ";
  }
  cout<<endl;

  nbytes=write(sockfd,buf,16); 
  if(nbytes<0)
  {
	cout<<"Write error"<<endl;
	exit(1);
  }
  
  cout<<"Delay (s) ? ";
  cin>>n;
  cout<<"sleeping "<<n<<" seconds...";
  cout<<endl;
  sleep(n);
  
  nbytes=read(sockfd,buf,128);
  if(nbytes<=0)
 {
	cout<<"Read error"<<endl;
	exit(1);
  }
  
  cout<<"The received data is..."<<endl;
  for(i=0;i<nbytes;i++)
    	cout<<buf[i]<<" ";
  
  cout<<endl;
}

int main(int argc,char*argv[])
{
  int sockfd;
  struct sockaddr_in servaddr;
  short port;

  if(argc!=3){
	cout<<"usage: ./client1 ip port."<<endl;
	exit(0);
  }
  port=atoi(argv[2]);
  
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
  {
	cout<<"Socket error"<<endl;
	exit(1);
  }
  else
	cout<<"My socket fd is: "<<sockfd<<endl;

  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(port);
  if(inet_aton(argv[1],&servaddr.sin_addr)==-1)
  {
	cout<<"Inet_aton error"<<endl;
	exit(1);
  }

  cout<<"Connecting..."<<endl;
  if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	cout<<"Connect error"<<endl;
	exit(1);
  }
 
  cout<<"Connected."<<endl;
  cli_requ(sockfd);
  close(sockfd);
}

