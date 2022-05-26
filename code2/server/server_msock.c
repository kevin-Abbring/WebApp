#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXDATASIZE 128
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd,new_fd,nbytes,sin_size;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr;
	int i,lastsockfd=-1;
	int minport,n,sizeSND,sizeRCV;

	if(argc!=3 && argc!=5)
	{
		printf("You should input 3 or 5 params: ");
		printf("func, startPort, number, SND size, RCV size.\n");
		exit(1);
	}
	
	minport=atoi(argv[1]);
	n=atoi(argv[2]);
	if(argc==5)
	{
		sizeSND=atoi(argv[3]);
		sizeRCV=atoi(argv[4]);
	}

	for(i=0;i<n;i++)
	{	
		//1.创建网络端点
		sockfd=socket(AF_INET,SOCK_STREAM,0);
		if(sockfd==-1){
			printf("Failed to create %d socket.The last sockfd is %d.\n",i,lastsockfd);
			exit(1);
		}
		lastsockfd=sockfd;

		if(argc==5){	// get & set SO_SNDBUF,SO_RCVBUF
			int size;
			socklen_t size2=sizeof(size);
			if((getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&size,&size2))<0)
			{
				printf("getsockopt failed\n");
				exit(1);
			}
			//printf("SND buff is %d\n",size);
			if((getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,&size2))<0)
			{
				printf("getsockopt failed\n");
				exit(1);
			}
			//printf("RCV buff is %d\n",size);

			if((setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sizeSND,sizeof(sizeSND)))<0 
				|| (setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&sizeRCV,sizeof(sizeRCV)))<0)
			{
				printf("setsockopt failed.\n");
				exit(1);
			}
//			printf("New SND and RCV buff are %d and %d.\n",sizeSND,sizeRCV);
//			exit(0);
		}
		
		//填充地址
		bzero(&srvaddr,sizeof(srvaddr));
		srvaddr.sin_family=AF_INET;
		srvaddr.sin_port=htons(minport+i);
		srvaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
		//2.绑定服务器地址和端口
		if(bind(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1){
			printf("bind error\n");
			exit(1);
		}
		//3. 监听端口
		if(listen(sockfd,BACKLOG)==-1){
			printf("listen error\n");
			exit(1);
		}
	}

	printf("Finished.The last sockfd is %d.\n",sockfd);
	sleep(60);
	return 0;
}
