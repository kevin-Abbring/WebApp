#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXDATASIZE 128
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd,new_fd,sin_size;
	int port,delay;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr,clientaddr;
	
	if(argc!=3){
		printf("usage:./echoserver port delay\n");
		return 1;
	}
	port=atoi(argv[1]);
	delay=atoi(argv[2]);
	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can't create socket\n");
		exit(1);
	}
	//填充地址
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(port);
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
	for(;;){
		//4.接受客户端连接
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))==-1){
			printf("accept error\n");
			continue;
		}
		printf("client addr:%s %d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		//延时
		sleep(delay);
		//6.回送响应
		sprintf(buf,"welcome!");
		write(new_fd,buf,strlen(buf));
		//关闭socket
		close(new_fd);
	}
	close(sockfd);
	
	return 0;
}
