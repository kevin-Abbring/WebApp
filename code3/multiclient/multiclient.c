#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define MAXDATASIZE 128
#define max(a,b) ((a)>(b)?(a):(b))

int main(int argc,char **argv)
{
	int sockfd1,sockfd2,nbytes;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr1,srvaddr2;
	int port1,port2;
	int multi=0;
	if(argc<3){
		printf("usage:./client port1 port2\n");
		exit(0);
	}
	port1=atoi(argv[1]);
	port2=atoi(argv[2]);
	if(argc==4)
		multi=1;
	//1.创建网络端点
	sockfd1=socket(AF_INET,SOCK_STREAM,0);
	sockfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd1==-1||sockfd2==-1){
		printf("create socket error\n");
		exit(1);
	}
	//指定服务器地址（本地socket地址采用默认值）
	bzero(&srvaddr1,sizeof(srvaddr1));
	srvaddr1.sin_family=AF_INET;
	srvaddr1.sin_port=htons(port1);
	
	if(inet_aton("127.0.0.1",&srvaddr1.sin_addr)==-1){
		printf("addr convert error\n");
		exit(1);
	}
	
	memcpy(&srvaddr2,&srvaddr1,sizeof(srvaddr1));
	srvaddr2.sin_port=htons(port2);
	//2.连接服务器
	if(connect(sockfd1,(struct sockaddr *)&srvaddr1,sizeof(struct sockaddr))==-1
		||connect(sockfd2,(struct sockaddr *)&srvaddr2,sizeof(struct sockaddr))==-1){
		printf("connect error\n");
		exit(1);
	}
	
	//4.接收响应
	struct timeval starttime,endtime;
	
	gettimeofday(&starttime,NULL);
	printf("start time:%ld\n",starttime.tv_sec);
	if(!multi){
		
		if((nbytes=read(sockfd1,buf,MAXDATASIZE))==-1){
			printf("read error\n");
			exit(1);
		}
		buf[nbytes]='\0';
		gettimeofday(&endtime,NULL);
		printf("(%ld) server1 respons:%s\n",endtime.tv_sec,buf);
		if((nbytes=read(sockfd2,buf,MAXDATASIZE))==-1){
			printf("read error\n");
			exit(1);
		}
		buf[nbytes]='\0';
		gettimeofday(&endtime,NULL);
		printf("(%ld) server2 respons:%s\n",endtime.tv_sec,buf);
	}
	else{//多路复用
		int fd1_finished=0;
		int fd2_finished=0;
		while(!fd1_finished||!fd2_finished){
			fd_set rdset;
			FD_ZERO(&rdset);
			if(!fd1_finished)
				FD_SET(sockfd1,&rdset);
			if(!fd2_finished)
				FD_SET(sockfd2,&rdset);
			struct timeval tv;
			tv.tv_sec=0;
			tv.tv_usec=100;
			int n=select(max(sockfd1,sockfd2)+1,&rdset,NULL,NULL,&tv);
			if(n<=0)
				continue;
			else{
				if(!fd1_finished && FD_ISSET(sockfd1,&rdset)){
					if((nbytes=read(sockfd1,buf,MAXDATASIZE))==-1){
						printf("read error\n");
						exit(1);
					}
					buf[nbytes]='\0';
					gettimeofday(&endtime,NULL);
					printf("(%ld) server1 respons:%s\n",endtime.tv_sec,buf);
					fd1_finished=1;
				}
				if(!fd2_finished && FD_ISSET(sockfd2,&rdset)){
					if((nbytes=read(sockfd2,buf,MAXDATASIZE))==-1){
						printf("read error\n");
						exit(1);
					}
					buf[nbytes]='\0';
					gettimeofday(&endtime,NULL);
					printf("(%ld) server2 respons:%s\n",endtime.tv_sec,buf);
					fd2_finished=1;
				}
			}
		}
	}
	//关闭socket
	close(sockfd1);
	close(sockfd2);
	return 0;
}
