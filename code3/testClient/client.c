#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXDATASIZE 128

int addr_conv(char *address,struct in_addr *inaddr);

int main(int argc,char **argv){
	int sockfd,nbytes;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr;
	int port;

	if(argc!=3){
		printf("usage:./client hostname|ip port\n");
		exit(0);
	}
	port=atoi(argv[2]);

	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}
	//指定服务器地址（本地socket地址采用默认值）
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(port);
	/*
	if(inet_aton("127.0.0.1",&srvaddr.sin_addr)==-1){
		printf("addr convert error\n");
		exit(1);
	}
	*/
	if(addr_conv(argv[1],&srvaddr.sin_addr)==-1){
		perror(strerror(errno));
	}
	//2.连接服务器
	if(connect(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1){
		printf("connect error\n");
		exit(1);
	}
	//3.发送请求
	sprintf(buf,"hello");
	write(sockfd,buf,strlen(buf));
	//4.接收响应
	if((nbytes=read(sockfd,buf,MAXDATASIZE))==-1){
		printf("read error\n");
		exit(1);
	}
	buf[nbytes]='\0';
	printf("srv respons:%s\n",buf);
	//关闭socket
	close(sockfd);
	return 0;
}

int addr_conv(char *address,struct in_addr *inaddr){
	struct hostent *he;
	if(inet_aton(address,inaddr)==1){
		printf("call inet_aton sucess.\n");
		return 0;
	}
	printf("call inet_aton fail.\n");
	he=gethostbyname(address);
	if(he!=NULL){
		printf("call gethostbyname sucess.\n");
		*inaddr=*((struct in_addr *)(he->h_addr_list[0]));
		return 0;
	}
	return -1;
}
