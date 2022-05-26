#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXDATASIZE 128
#define PORT 3000
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd, new_fd, nbytes, sin_size;
	unsigned int port, minport, maxport;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr,clientaddr;
	
	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}

	if(argc==2){
		int on=1;
		setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		printf("reuse addr\n");
	}
	//填充地址
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
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

	minport=65535;
	maxport=0;
	printf("Listening......\n");
	for(;;){
		//4.接受客户端连接
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))==-1){
			printf("accept error\n");
			continue;
		}
		
		port=(unsigned int)ntohs(clientaddr.sin_port);
		if(port<minport || port>maxport)
		{		
		   if(port<minport)
		      minport=port;
		   else if(port>maxport)
		      maxport=port;
		   
		   printf("minport is: %d\t",minport);
		   printf("maxport is: %d\n",maxport);
		}		
		nbytes=read(new_fd,buf,MAXDATASIZE);
		write(new_fd,buf,strlen(buf));
		close(new_fd);
	}
	close(sockfd);
	
	return 0;
}
